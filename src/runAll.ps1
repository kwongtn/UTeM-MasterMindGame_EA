cd "./x64/Compile/"
Get-ChildItem -File | Foreach {
    &$_.FullName
}
cd ../..