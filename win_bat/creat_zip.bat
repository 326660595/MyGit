@echo off

set source_folder=C:\code\MyGit\win_bat\NovaX_C.hex
set destination_zip=C:\code\MyGit\win_bat\NovaX_C.zip

powershell -Command "Compress-Archive -Path '%source_folder%' -DestinationPath '%destination_zip%'"

echo Zip compression completed.
