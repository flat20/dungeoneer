
# About

You will probably have to update the offsets if you're not on the standalone 64-bit Windows version of Minecraft Dungeons.

# Build

`make-inject.bat`

Compiles the .exe which injects dungeoneer.dll into Minecraft Dungeons.

`make-dungeoneer.bat`

Compiles the dungeoneer.dll which can load mod dll files.

`make-simple.bat`

Compiles simple-mod.dll, the simplests of mods. This dll can be loaded at runtime with Dungeoneer.

# Dump

* x64dbg with Scylla
* Click IAT AutoSearch
* Click Dump to write the exe to a place on your hard drive.
* Open IDA Pro. Click "OK" for any warnings. Wait for for it to analyze it.
* Search for the opcode binary search strings which can be found in `inject/main.cpp` or in some of the random `docs/` files.
* Get the offset from the function to the start of the .exe and set it in `unrealspy/unrealspy.cpp`.

# TODO

`inject.exe` should be renamed to `dungeoneer.exe` and become the launcher which can start up Dungeons
and then automatically inject `dungeoneer.dll` inside of it.
