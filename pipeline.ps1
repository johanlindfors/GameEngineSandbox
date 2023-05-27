[CmdletBinding()]
Param(
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
    [switch]$uwp,

    [Parameter(Mandatory = $False)]
    [switch]$release
)

$Cmake = "cmake.exe"
$BuildDirectory = ""
$PlatformParameters = ""
$Generator = "Visual Studio 17 2022"
$BuildType = ""
$BuildConfiguration = "Debug"

If($win32) {
    $BuildDirectory = "build/win32"
} ElseIf($uwp) {
    $BuildDirectory = "build/uwp"
    $PlatformParameters = @("-DCMAKE_SYSTEM_NAME='WindowsStore'", "-DCMAKE_SYSTEM_VERSION='10.0.22000.0'")
}

If($release) {
    If($win32) {
        $BuildType = "-DCMAKE_CONFIGURATION_TYPES=Release"
        $BuildConfiguration = "Release"
    } ElseIf($uwp) {
        $BuildType = "-DCMAKE_CONFIGURATION_TYPES=RelWithDebInfo"
        $BuildConfiguration = "RelWithDebInfo"
    }
} Else {
    $BuildType = "-DCMAKE_BUILD_TYPE=Debug"
    $BuildDirectory += "-debug"
}

if($generate -OR $build) {
    & $Cmake @("-E", "remove_directory", $BuildDirectory)
    & $Cmake @("-E", "make_directory", $BuildDirectory)
}
if($generate -OR $build -OR $update) {
    $GenerateParameters = @("-E", "chdir", $BuildDirectory, "cmake", "-G", $Generator)
    $GenerateParameters += $PlatformParameters
    $GenerateParameters += $BuildType
    $GenerateParameters += ("-A", "x64", "../..")
    & $Cmake $GenerateParameters

    if($uwp) {
        $InjectCommand = $BuildDirectory + "/inject.py"
        & python @($InjectCommand)
    }
}
if($compile -OR $build) {
    & $Cmake @("--build", $BuildDirectory, "--config", $BuildConfiguration)
}
