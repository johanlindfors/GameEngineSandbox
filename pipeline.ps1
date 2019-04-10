[CmdletBinding()]
Param(
    [Parameter(Mandatory = $False)]
    [string]$toolchainFile,

    [Parameter(Mandatory = $False)]
    [switch]$generate,

    [Parameter(Mandatory = $False)]
    [switch]$update,

    [Parameter(Mandatory = $False)]
    [switch]$compile,

    [Parameter(Mandatory = $False)]
    [switch]$build,

    [Parameter(Mandatory = $False)]
    [switch]$win32,

    [Parameter(Mandatory = $False)]
    [switch]$uwp
)

$Cmake = "cmake.exe"
$BuildDirectory = ""
$PlatformParameters = ""
$Generator = "Visual Studio 15 2017"

If($win32) {
    $BuildDirectory = "build/win32"
    if(-NOT $toolchainFile -AND -NOT $compile) {
        Write-Output "Win32 need to have the toolchainFile parameter pointing to the vcpkg file"
        exit
    }
    $PlatformParameters = "-DCMAKE_TOOLCHAIN_FILE='$toolchainFile'"
} ElseIf($uwp) {
    $BuildDirectory = "build/uwp"
    $PlatformParameters = @("-DCMAKE_SYSTEM_NAME='WindowsStore'", "-DCMAKE_SYSTEM_VERSION='10.0'")
}

if($generate -OR $build) {
    & $Cmake @("-E", "remove_directory", $BuildDirectory)
    & $Cmake @("-E", "make_directory", $BuildDirectory)
}
if($generate -OR $build -OR $update) {
    $GenerateParameters = @("-E", "chdir", $BuildDirectory, "cmake", "-G", $Generator)
    $GenerateParameters += $PlatformParameters
    $GenerateParameters += ("-A", "x64", "../..")
    & $Cmake $GenerateParameters
}
if($compile -OR $build) {
    & $Cmake @("--build", $BuildDirectory)
}