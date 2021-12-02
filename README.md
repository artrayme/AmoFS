# AmoFS
## Overview
This project presents the simplest implementation of a single-level file system with linked blocks.

## Implementation
The Filesystem was written with stl-containers. For the list of files in filesystem std::set was used.
To implement a linked list of blocks inside the file, std::list was used.
Each block contains information in std::vector.

## How to build and run
On linux you can do the following
```
cmake -B build
cd build
make
./AmoFS
```