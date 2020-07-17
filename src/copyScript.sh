#!/bin/bash
now="$(date +'%s')"

echo $now

cp "./x64/Release/Mastermind-EvoComp.exe" "./x64/Compile/Mastermind-EvoComp-${now}.exe"