
# About

Dungeoneer adds function hooks to the Unreal Engine based Minecraft Dungeons for Windows.

## Launcher

Finds the running Minecraft Dungeons process and injects the `dungeoneer.dll` in to the process' memory so it can read and write to.

## Dungeoneer DLL

Hooks a few basic Unreal Engine functions, unlocks the in-game console with cheats using `unrealspy/` and creates a UI which enables loading of additional `-mod.dll` files found in the current directory.

## Mods

### speedrun

Overrides Minecraft Dungeons LoadLevel function and replaces the random seed used for randomly generating a level with a set seed so the same level can be run.

### strid-mod

Displays damage per second done by the player's abilities.

# Build

`make-dungeoneer.bat`

Compiles the `dungeoneer.dll` which unlocks the console and enables all the cheat commands.

`make-launcher.bat`

Compiles `dungeoneer.exe` which injects `dungeoneer.dll` into Minecraft Dungeons.
