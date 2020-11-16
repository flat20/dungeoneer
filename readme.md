
# About

Refactoring in progress. I wouldn't attempt building it right now until the makefile branch
is merged in. But before that there's the 4.24 branch, which makes this work for version
4.24 of the UE SDK. That needs to be merged in as well.

# Build

`make-dungeoneer.bat`

Compiles the `dungeoneer.dll` which unlocks the console and enables all the cheat commands.

`make-launcher.bat`

Compiles `dungeoneer.exe` which injects `dungeoneer.dll` into Minecraft Dungeons.
