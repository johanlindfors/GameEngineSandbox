[CmdletBinding()]
Param(
    [Parameter(Mandatory = $True)]
    [string]$toolchainFile
)

$Cmake = "cmake.exe"

& $Cmake @("-E", "remove_directory", "build/win32")
& $Cmake @("-E", "make_directory", "build/win32")
& $Cmake @("-E", "chdir", "build/win32", "cmake", "-G", "Visual Studio 15 2017", "-DCMAKE_TOOLCHAIN_FILE='$toolchainFile'", "-A", "x64", "../..")
