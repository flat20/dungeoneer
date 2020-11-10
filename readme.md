
# About


# Build

`make-launcher.bat`

Compiles the dungeoneer.exe which injects dungeoneer.dll into Minecraft Dungeons.

`make-dungeoneer.bat`

Compiles the dungeoneer.dll which can load mod dll files.

`make-simple.bat`

Compiles simple-mod.dll, the simplests of mods. This dll can be loaded at runtime with Dungeoneer.

# TODO

* Mods shouldn't know about diet-ue at all, and not have to link to them.
* Nicer/simpler getting of function pointers.
* GetPrivateStaticClass() #defines but look up default class in gobjects.