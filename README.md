# SFML project setuper

**"As a programer you can't complain that you code was stollen. Why? Because it's not your code, you stole it from someone." - UAPROGRAMER 2025**

This program allows you to quickly setup project for working in SFML. SFML project setuper was made for usage in unix like systems (mainly linux).

## Overview
This project reads setup file and creates SFML project in the same directory.

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)

## Usage
You need to enter directory you want to create your project in and create setup.txt file there (you are not required to create setup.txt, see lower). Then you run sfml-stpr (SFML setuper) and it creates your project based on your setup.

### Arguments 
- "-f" (project will be created even without setup file)

### Setup.txt
Your setup.txt should look something like this:

```setup.txt
name = <Project Name>
version = <SFML version you are using>
libs = <SFML libs you are using>
cxxs = <C++ standart you are using>
cxxsr = <Is C++ standart required (True||False)>
link = <SFML libs to link (just add "sfml-" to every lib in libs)>
```

The order of variables doesn't matter. This project uses interpreter that will read setup file and save every variable. This means that you can create any variable with any value and it won't realy matter.
But the interpreter isn't smart enough to see errors in your values and program will create project anyway even if your values is wrong.
If you create project without setup file this will be the equivalent to setup.txt that program will use by default:

```setup.txt
name = Project1
version = 2.5.1
libs = window system graphics audio network
cxxs = 11
cxxsr = True
link = sfml-system sfml-window sfml-graphics sfml-audio sfml-network
```

If you want to know if character is allowed in setup file or you getting "[ ERROR ] Bad character." this is function for you to folow:

```C++
bool is_character_allowed(char c) {
    return (isalnum(c) || c = '_' || c = '.' || c = '-');
}
```

Enjoy!

## Installation
This is guide to installing sfml-stpr.

### Linux
This is only system that is supported right now.

#### Requirements
- <C++ compiler> (g++ is used by default but you can change it in Makefile)
- make 
- zip (not mandatory)
- sudo (not mandatory if you use root user || might be installed by default) 
- cp (installed by default)
- rm (installed by default)
- cmake (will be need to compile project itself)

#### Process
Enter folder with this project wia terminal. Run "make install-linux". Enter your user's password. Done.
