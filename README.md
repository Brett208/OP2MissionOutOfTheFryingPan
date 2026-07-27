# OP2 Mission Out of the Frying Pan, Into the Fire

An Outpost 2 cooperative 4 player multiplayer mission.



## Debugging

In order to attach Outpost 2 to the mission dll, you will need to modify the debug settings of the project.

To access these settings, right-click the OutOfTheFryingPan project, and select "Properties."  Then, make sure that the field on the top-left of the menu is set to "All Configurations."

Then, configure the debugging properties as follows:

- Command: <Path to Outpost2.exe (NOT opuLauncher)>

- Command Arguments: /OPU

- Working Directory: <Path to Outpost 2 root directory>

- Attach: No

- Debugger Type: Auto

Leave everything else as-is.
