call make-launcher.bat
call make-dungeoneer.bat
call make-debug.bat
del dungeoneer.zip
"C:\Program Files\7-Zip\7z" a -tzip dungeoneer.zip dungeoneer.dll dungeoneer.exe debug-mod.dll