#!/bin/bash
# bash build.sh <version>

# IMPORTANT: 
# Zombie Escape MUST ONLY RUNS ON LINUX SERVER

git fetch --unshallow

# 
MAJOR=1
MINOR=0
COUNT=$(git rev-list --count HEAD)
DATE=$(date +"%Y-%M-%D %H:%m:%S")

echo "Building"

echo "Build for SourceMod Library 2."
echo "Version: $MAJOR.$MINOR.$COUNT"
echo "Build date: $DATE"

echo ""
echo "Setting up environment"
echo ""

echo "Download SourceMod, version: $1"
if [ "$1" = "1.10" ]; then
    wget "https://sm.alliedmods.net/smdrop/1.10/sourcemod-1.10.0-git6502-linux.tar.gz" -q -O sourcemod.tar.gz
else
    echo "Download specify version's latest"
    wget "http://www.sourcemod.net/latest.php?version=$1&os=linux" -q -O sourcemod.tar.gz
fi
echo ""

echo "Unpacking"
tar -xzf sourcemod.tar.gz
echo ""

echo "Retrieving dependencies"
echo ""

# SMLib2
echo "SourceMod Library 2"

# PTaH
echo "PTaH"
wget "https://github.com/komashchenko/PTaH/raw/master/PTaH.inc" -q -O include/PTaH.inc
echo ""

# DHook
echo "DHook"
wget "https://raw.githubusercontent.com/peace-maker/DHooks2/dynhooks/sourcemod_files/scripting/include/dhooks.inc" -q -O include/dhooks.inc
echo ""

echo "Version info"
for file in include/const.inc
do
    sed -i "s%<Major>.<Minor>.<GitCommit>%$MAJOR.$MINOR.$COUNT%g" $file > output.txt
    sed -i "s%<Date>%$DATE%g" $file > output.txt
    rm output.txt
done

cp test.sp addons/sourcemod/scripting/test.sp
cp -rf include/* addons/sourcemod/scripting/include

addons/sourcemod/scripting/spcomp -E -v2 -O2 addons/sourcemod/scripting/test.sp -o"build/addons/sourcemod/plugins/test.smx"
if [ ! -f "build/addons/sourcemod/plugins/test.smx" ]; then
    echo "Build: test.smx failed. Check error output"
    exit 1
fi