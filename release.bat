call make-launcher.bat
call make-dungeoneer.bat
call make-debug.bat
del dungeoneer.zip
"C:\Program Files\7-Zip\7z" a -tzip dungeoneer-0.1.3.zip dungeoneer.dll dungeoneer.exe debug-mod.dll