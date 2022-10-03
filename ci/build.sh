#!/bin/bash
# bash build.sh <version>

# git fetch --unshallow
# 
# MAJOR=1
# MINOR=0
# COUNT=$(git rev-list --count HEAD)
# DATE=$(date +"%Y-%m-%d %H:%M:%S")

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

echo "Version info"
for file in include/smlib2/version.inc
do
    sed -i "s%<Major>.<Minor>.<GitCommit>%$MAJOR.$MINOR.$COUNT%g" $file > output.txt
    sed -i "s%<Date>%$DATE%g" $file > output.txt
    rm output.txt
done

cp test.sp addons/sourcemod/scripting/test.sp
cp -rf include/* addons/sourcemod/scripting/include

addons/sourcemod/scripting/spcomp -E -v2 -O2 addons/sourcemod/scripting/test.sp -o"addons/sourcemod/scripting/test.smx"
if [ ! -f "addons/sourcemod/scripting/test.smx" ]; then
    echo "Build: test.smx failed. Check error output"
    exit 1
fi
