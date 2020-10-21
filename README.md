# pang

*A*lternative version of *pong* ~ pang: This is a small project aimed to improve my software skills, that is, to learn modern cpp techniques, design patterns and cmake.

It was originally inspired by the following [tutorial](https://www.gamefromscratch.com/page/Game-From-Scratch-CPP-Edition-Part-1.aspx) but follows different software design decisions.


## Prerequisites
The current configuration was tested run on linux, mainly using 
[vscode](https://code.visualstudio.com/docs/cpp/config-linux).

You can also build it in cmake (see below).

It depends on the basic build toolchain and sfml:
```
sudo apt install build-essential
sudo apt install libsfml-dev libsfml-doc
```

## Running pang
There are three ways you can run pang:

Open the folder in vscode and choose one of the following options:
* start the *gdb pang* debugging configuration in vscode
* run it via *CMake Tools* extension in vscode

Or you can run it directly via terminal:

Configure:
```
cmake -S . -B build
```
Build:
```
cmake --build build
```
Run:
```
./build/apps/pang
```


---
[markdown reference](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)

