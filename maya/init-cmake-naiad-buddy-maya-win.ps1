cd $env:HOME
remove-item $env:HOME/naiad-buddy-maya.git/build -force -recurse
new-item $env:HOME/naiad-buddy-maya.git/build -force -type directory

$env:cmakecmd = "cmake -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=$env:NAIAD_PATH `"-DMAYA_INSTALL_PATH=$env:MAYA_PATH`" -DMAYA_VERSION=2011 $env:HOME/naiad-buddy-maya.git -G `"Visual Studio 10 Win64`""

cd $env:HOME/naiad-buddy-maya.git/build
$env:cmakecmd
Invoke-Expression -Command $env:cmakecmd
