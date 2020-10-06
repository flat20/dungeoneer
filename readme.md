
# Build

`make-inject.bat`

Compiles the .exe which injects dungeoneer.dll into Minecraft Dungeons.

`make-dungeoneer.bat`

Compiles the dungeoneer.dll which can load mod dll files.

`make-simple.bat`

Compiles simple-mod.dll, the simplests of mods.

# TODO 

`inject.exe` should be renamed to `dungeoneer.exe` and become the launcher which can start up Dungeons
and then automatically inject `dungeoneer.dll` inside of it.

* ~~Find property by path: ModCalc/RelevantAttributesToCapture/GameplayTags~~ Done
* ~~Format numbers~~ Done
* ~~Sorting~~ Done
* ~~Percentage~~ Done
* ~~Recursive property iteration~~ Done
* ~~GetFloatPropertyValue template~~ Done
* UFontFace?
* Rect row for each entry
* Icon for each row
* Split up code
* IsClass(struct) in order to get the container should be a function we can re-use.
* Memory leaks

# Dump

* x64dbg with Scylla
* Click IAT AutoSearch
* Click Dump to write the exe to a place on your hard drive.
* Open IDA Pro. Click "OK" for any warnings. Wait for 6 hours for it to analyze it.
