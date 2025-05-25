@echo off
ECHO ----------------------------------------
echo Creating Estuary Build Folder
IF EXIST BUILD rmdir BUILD /S /Q
md BUILD

Echo .svn>exclude.txt
Echo .git>exclude.txt
Echo Thumbs.db>>exclude.txt
Echo Desktop.ini>>exclude.txt
Echo dsstdfx.bin>>exclude.txt
Echo exclude.txt>>exclude.txt

ECHO ----------------------------------------
ECHO Creating XPR File...
START /B /WAIT ..\..\Tools\XBMCTex\dist\XBMCTex -input media -output media -noprotect

ECHO ----------------------------------------
ECHO Copying XPR File...
xcopy "media\Textures.xpr" "BUILD\skin.estuary\media\" /Q /I /Y

ECHO ----------------------------------------
ECHO Cleaning Up...
del "media\Textures.xpr"

ECHO ----------------------------------------
ECHO XPR Texture Files Created...
ECHO Building Skin Directory...
xcopy "extras" "BUILD\skin.estuary\extras" /E /Q /I /Y /EXCLUDE:exclude.txt
xcopy "fonts" "BUILD\skin.estuary\fonts" /E /Q /I /Y /EXCLUDE:exclude.txt
xcopy "playlists" "BUILD\skin.estuary\playlists" /E /Q /I /Y /EXCLUDE:exclude.txt
xcopy "resources" "BUILD\skin.estuary\resources" /E /Q /I /Y /EXCLUDE:exclude.txt
xcopy "xml\*.*" "BUILD\skin.estuary\xml\" /Q /I /Y /EXCLUDE:exclude.txt
xcopy "colors\*.*" "BUILD\skin.estuary\colors\" /Q /I /Y /EXCLUDE:exclude.txt
xcopy "language" "BUILD\skin.estuary\language" /E /Q /I /Y /EXCLUDE:exclude.txt

del exclude.txt

copy *.xml "BUILD\skin.estuary\"
copy *.txt "BUILD\skin.estuary\"
