# Mixxx Build Documentation

## Download Mixxx source code

First, open a terminal and use Git to download the mixxx source code:

    git clone https://github.com/mixxxdj/mixxx.git

Then, enter the mixxx code repository:

    cd mixxx

## Install build tools

### Debian, Ubuntu, and derived distributions

On Debian, Ubuntu, and derived Linux distributions, there is a script
in the mixxx repository that will install the required packages:

    tools/debian_buildenv.sh

### Fedora

If you do not already have the [RPM Fusion](https://rpmfusion.org) free repository installed:

    sudo dnf install https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm

The RPM Fusion nonfree repository is not required.

Then:

    sudo dnf builddep mixxx
    sudo dnf install gcc-c++ ccache ninja-build qt5-qtdeclarative-devel qt5-qtquickcontrols qt5-qtquickcontrols2

### macOS

First, install the XCode C++ toolchain:

    xcode-select --install

Then install more development tools from [Homebrew](https://brew.sh):

    brew install cmake ccache ninja nasm automake nuget

Do *not* install Mixxx's dependencies from Homebrew; only install the build tools
listed above. CMake will automatically download Mixxx's dependencies with vcpkg.

CMake *must* be installed from Homebrew and not another source. This is because
vcpkg requires using the same CMake version as used on GitHub Actions for the vcpkg
binary cache to hit, otherwise vcpkg will rebuild all libraries locally which will
take hours. A [fix](https://github.com/microsoft/vcpkg-tool) for this issue is pending
upstream.

Mixxx does not support ARM macOS builds yet, but the build system will build x86-64
executables from ARM macOS which run fine on ARM macOS. We will not be able to
build Mixxx for ARM macOS until we switch to Qt6.

### Windows

Using the [Visual Studio installer](https://visualstudio.microsoft.com/downloads/),
install `Build Tools for Visual Studio 2019` to build from the command line.
Alternatively, install the full Visual Studio 2019 IDE with the option
`Desktop development with C++` (this is distinct from Visual Studio Code). If you
have Windows set to a language other than English, you will also need to
[install the English language pack for Visual Studio](https://docs.microsoft.com/en-us/visualstudio/install/modify-visual-studio?view=vs-2019#modify-language-packs)
(this is [required by vcpkg](https://github.com/microsoft/vcpkg/issues/2295)).

CMake will automatically use vcpkg to download Mixxx's dependencies.

We highly recommend to install sccache as well to speed up rebuilds. sccache requires
[installing a Rust toolchain](https://www.rust-lang.org/learn/get-started), then:

    cargo install --git https://github.com/mozilla/sccache.git --rev 3f318a8675e4c3de4f5e8ab2d086189f2ae5f5cf

## Setup NuGet source for vcpkg

For macOS and Windows, it is highly recommended to create a GitHub account and
[create a personal access token](https://github.com/settings/tokens) (PAT)
with `read:packages` permission before building Mixxx to access the builds of
Mixxx's dependencies from GitHub Packages (otherwise vcpkg will build them all
locally which will take hours). Then, setup NuGet with your PAT:

    nuget sources add -Name mixxx-github-packages -Source https://nuget.pkg.github.com/mixxxdj/index.json -Username mixxxdj -Password YOUR_PAT_GOES_HERE

CMake will automatically bootstrap vcpkg and use vcpkg to download Mixxx's
dependencies from GitHub Packages into the CMake build directory.

## Build Mixxx

On Windows, compiling must be done from a `x64 Native Tools Command Prompt for
VS 2019` shell. Opening a regular cmd or PowerShell prompt will not work.

First, configure CMake (`-G Ninja` is required on Windows and recommended on
Linux and macOS):

    cmake -G Ninja -S . -B build

This will create a directory called `build` where the build artifacts will be.
On Windows and macOS, vcpkg will automatically download Mixxx's dependencies
during the first CMake configure step, which will take a few minutes. vcpkg
downloads the libraries into the `vcpkg_installed` directory inside the CMake
build directory.

To build Mixxx:

    cmake --build build

Configuring CMake only needs to be done once, or when changing a CMake option.
After the initial configuration, when you edit the source code, you only need
to run the build step.

If you want to switch between different CMake configurations frequently, you
can use separate build directories by replacing `build` in the steps above
with another directory.

## Run Mixxx

    build/mixxx

On Linux, if you use Wayland, to get the waveforms to show, you need to run:

    build/mixxx -platform xcb

On Linux, if you use an ALSA device for Mixxx but otherwise use PulseAudio:

    pasuspender build/mixxx

This is not necessary with PipeWire. PipeWire releases the ALSA device
so Mixxx can use it if no applications are using it through PipeWire, or
alternatively you can use PipeWire through the JACK API by selecting the JACK
backend in Mixxx's Sound Hardware preferences.

## Command line options

For information about command line options:

    build/mixxx --help

## Install Mixxx

Installing Mixxx is not required to run it. Instead, we recommend running
Mixxx from the CMake build directory as described above. Nevertheless, if
you want to install Mixxx to the default /usr/local prefix,

    sudo cmake --install build

If you want to install Mixxx elsewhere, you can specify
`-D CMAKE_INSTALL_PREFIX=/some/path` to the CMake configure step.

If you want to uninstall Mixxx built without a package manager, you need
to keep the CMake build directory and run:

    xargs rm < build/install_manifest.txt

## Running tests

    cd build
    ctest

## macOS packaging

To create DMG app bundle installers for macOS, configure CMake with the `MACOS_BUNDLE` option:

    cmake -G Ninja -D MACOS_BUNDLE=ON -S . -B build

To create a signed package:

    cmake -G Ninja -D MACOS_BUNDLE=ON -D APPLE_CODESIGN_IDENTITY=<your signing identity> -S . -B build

After building Mixxx:

    cd build
    cpack -G DragNDrop

## Windows packaging

To create an .msi installer, you need to install the [WiX toolset](https://wixtoolset.org/releases/).
After building Mixxx:

    cd build
    cpack -G WIX
