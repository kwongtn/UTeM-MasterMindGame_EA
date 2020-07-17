cd "./x64/Compile/"
Get-ChildItem -File | Foreach {
    Get-FileHash  $_.name
}
cd ../..