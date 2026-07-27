# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

"Out of the Frying Pan, Into the Fire" is a cooperative multiplayer mission (Space Race, up to 5 human players + 1 AI) for **Outpost 2**, a 1997 RTS. The mission compiles to a Windows DLL (`mf4oofp.dll`) that the Outpost 2 game engine loads at runtime and calls into via exported functions. There is no standalone executable and no automated test suite — correctness is verified by loading the mission in the actual game.

## Build

Open `OutOfTheFryingPan.sln` in Visual Studio (v142 toolset) and build the `Debug|Win32` or `Release|Win32` configuration. The solution includes the mission project plus the `OP2MissionSDK` submodule's `HFL`, `OP2Helper`, and `Outpost2DLL` projects as project references — build the solution, not just the mission `.vcxproj`, on a clean checkout.

- The `OP2MissionSDK` directory is a git submodule (itself containing nested submodules `HFL`, `OP2Helper`, `Outpost2DLL`). Run `git submodule update --init --recursive` after cloning.
- Post-build, the DLL is copied into the game install directory if the `Outpost2Path` environment variable is set (see the `PostBuildEvent` in `OutOfTheFryingPan.vcxproj`). Without it, the copy step is skipped silently.
- There is no CLI build/test/lint command — this is a Visual Studio–only C++ project (MSBuild via the IDE).
- To test a change, build, let it copy to the game folder (or copy manually), then launch the mission in Outpost 2 and play through the relevant scenario.

## Architecture

### Entry points and mission lifecycle
The game engine calls into exported functions declared with the `Export` macro (from `RequiredExports.h` in Outpost2DLL). Key ones in `LevelMain.cpp`:
- `InitProc()` — one-time setup on level start (not called on save-game load): disaster helper, morale, music, night-cycle lock (to stabilize Blight spread), player alliances, volcano/player/AI init, victory conditions, Blight/attack timers.
- `AIProc()` — called every game tick; drives `CheckMorale()` and `UpdateWeakAIBase()`.
- `SpawnBlight`, `WeakBaseAttackTrigger`, `CreateDisaster`, `NWVolcanoErupts`/`SWVolcanoErupts`/`SEVolcanoErupts` — trigger callbacks wired up via `CreateTimeTrigger`/`CreateCountTrigger`.
- `DllMain.cpp` calls `HFLInit()`/`HFLCleanup()` — HFL (Hacker's Function Library, a memory-hacking extension library) must be initialized here rather than in `InitProc`, since `InitProc` doesn't re-run when a saved game loads.

### Player count scaling
The mission supports 2–5 human players; the AI is always the last player slot. `HumanPlayerCount()` (`AIPlayer.cpp`) returns `TethysGame::NoPlayers() - 1` and is used throughout to scale base size and difficulty:
- `PlayerInitialization.cpp` picks `humanPlayerCount` random starting locations from a fixed pool of 5 and builds each player's starting base/units.
- `NorthAIBase.cpp` / `SouthAIBase.cpp` conditionally add extra vehicle factories/spaceports (`if (HumanPlayerCount() >= N)`) so the strong AI bases grow with more players.
- Defensive tank counts scale via a `GetDefensiveTankCount()` switch (2/3/other players → 3/5/8 tanks) duplicated in both `WeakAIBase.cpp` and `StrongBasesShared.cpp`.

### AI base layout (three independent AI bases, one shared AI player)
| Base | Location | Notes |
|------|----------|-------|
| Weak base (`WeakAIBase.cpp/.h`) | western map, ~(76,132) | Builds itself, owns a `BaseOffensiveFightGroupManager` that spawns one offensive fight group per extra vehicle factory (scales with player count) and a single `DefensiveFightGroup` guarding its rect. Attacks are gated by `AllowWeakAIBaseAttack()`, fired from a time trigger. |
| North strong base (`NorthAIBase.cpp/.h`) | eastern map, ~(244,122) | Perimeter + in-base guard post clusters; defensive vehicle factories feed `SetupDefensiveFightGroups` (shared helper). |
| South strong base (`SouthAIBase.cpp/.h`) | eastern map, ~(242,162) | Same pattern as North. |

`AIBaseBuilder.cpp` is legacy/dead code superseded by the three base-specific files above — don't extend it.

### Fight group class hierarchy
- `FightGroupOverlay` (`FightGroupOverlay.h/.cpp`) — base class wrapping a game `FightGroup` + `BuildingGroup`; tracks a guarded `MAP_RECT`, tank target counts, and tank creation (`AddTank`, `SetLynxCount`/`SetPantherCount`/etc.).
- `DefensiveFightGroup` — extends it to spawn pre-placed tanks and guard a rect (used by all three bases).
- `OffensiveFightGroup` — extends it to build up units then attack human buildings (`AttackBuilding`) or do general attacks (`BasicAttack`); tasked/updated via `UpdateTaskedFightGroups()`.
- `BaseOffensiveFightGroupManager` (`BaseOffensiveFightGroupManager.h/.cpp`) — owns a collection of `OffensiveFightGroup`s for one AI base, one per vehicle factory added via `AddFightGroup`; `Update()` ticks each group and triggers `Attack()` once a group is full and attacks are enabled.

### Reusable systems
- `DisasterHelper.cpp/.h` — configurable random-disaster system (meteor/earthquake/storm/vortex), driven by a time trigger calling `CreateRandomDisaster()`; respects "safe rects" around player bases and an expiration timer.
- `VolcanoHelper.cpp/.h` — sets up the three volcanoes (NW/SW/SE) with lava flow and timed eruption triggers.
- `AIHelper.cpp/.h` — low-level shared building/mining helpers (`CreateAIBuilding`, `CreateGuardPostCluster`, `SetupBuildingGroup`, `CreateCommonMineGroup3Bar`, `CreateRareMineGroup3Bar`, `SetupMiningGroup`) used by all three AI bases.
- `AIBaseShared.cpp/.h` — Plymouth-specific guard post cluster helpers and the shared AI player index (`SetAIIndex`/`GetAIIndex` in `AIPlayer.cpp/.h`).

### Coordinate offsets
Map locations throughout the codebase are written as raw coordinates plus `X_`/`Y_` offset constants (e.g. `LOCATION(76 + X_, 132 + Y_)`) — these correct for the map's real origin offset; always include them when adding new hardcoded locations, matching the surrounding code.

### Win condition
Space Race: victory conditions in `AddVictoryConditions()` require evacuating the Children's Module, Evacuation Module, Food Cargo, Rare Metals Cargo, and Common Metals Cargo to spacecraft (`LevelMain.cpp`).
