* [Compiling on Linux](#compiling-on-linux)
  * [Debian](#debian)
  * [Arch Linux](#arch-linux)
* [Compiling on MacOS](#compiling-on-macos)

# Compiling on Linux

If your package manager doesn't have Cmake, have a look at
[this question](https://askubuntu.com/questions/355565/how-to-install-latest-cmake-version-in-linux-ubuntu-from-command-line/865294#865294).

## Debian

### Dependencies

To compile this program you need to install the following dependencies:

```
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install cmake
sudo apt-get install libsfml-dev (outdated)
```

### Building SFML
```
Clone repo: https://github.com/SFML/SFML
Install missing lib: sudo apt-get install libopenal-dev
In SFML/: cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D BUILD_SHARED_LIBS=TRUE .
make -j4
sudo make install
```


### Compiling the project

Now go to the project directory and enter the following command:

```
cmake .
make
```

### Run the program

Now you can run this program with this command:

```
./solar_system
```

## Arch Linux

### Dependencies

To compile this program you need to install the following dependencies:

```
sudo pacman -Syy
sudo pacman -S gcc
sudo pacman -S make
sudo pacman -S cmake
sudo pacman -S sfml
```

### Compiling the project

Now go to the project directory and enter the following command:

```
cmake .
make
```

### Run the program

Now you can run this program with this command:

```
./solar_system
```

# Compiling on MacOS

### Dependencies

To compile this program you need to install the XCode Command Line Tools, the SFML frameworks, and CMake.

#### XCode Command Line Tools

To install the XCode Command Line Tools you need to:

1. Open Xcode.
2. Go to menu Xcode -> Preferences -> Downloads -> Components.
3. Select Command Line Tools and follow instructions.

In newer versions of XCode you won't find the Command Line Tools. In such case you can run the command `xcode-select --install` in Terminal and follow the instructions.

#### SFML

To install the SFML framework and its dependencies in your system you need to follow these instructions:

1. Go to the [SFML downloads page](https://www.sfml-dev.org/download.php) and download the latest stable binaries.
2. Extract the libraries.
3. Copy the contents of the directory `Frameworks` into `/Library/Frameworks`.
4. Copy the contents of the directory `extlibs` into `/Library/Frameworks`.

#### CMake

To install CMake into your system you need to follow these instructions:

1. Go to the [CMake download page](https://cmake.org/download/) and download the lastest release.
2. Open the image file.
3. Move the CMake app into the `/Applications` directory.

### Compiling the project

Simply go to the project directory and run:

```
/Applications/CMake.app/Contents/bin/cmake .
make
```

### Run the program

Now you can run this program with this command:

```
./solar_system
```
