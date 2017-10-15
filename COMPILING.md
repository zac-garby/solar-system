* [Compiling on Linux](#compling-on-linux)
  * [Debian](#debian)
  * [Arch Linux](#arch-linux)

# Compiling on Linux

## Debian

### dependencies

To compile this program you need to install the following dependencies:

```
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install cmake
sudo apt-get install libsfml-dev
```

### compiling the project

Now go to the project directory and enter the following command:

```
cmake .
make
```

### run the program

Now you can run this program with this command:

```
./solar_system
```

## Arch Linux

### dependencies

To compile this program you need to install the following dependencies:

```
sudo pacman -Syy
sudo pacman -S gcc
sudo pacman -S make
sudo pacman -S cmake
sudo pacman -S sfml
```

### compiling the project

Now go to the project directory and enter the following command:

```
cmake .
make
```

### run the program

Now you can run this program with this command:

```
./solar_system
```
