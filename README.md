# vs-TGW
## Introduction

## Build and run
```bash
# -G : according to which you use
cmake -B build -G "MinGW Makefiles"
cmake --build build
.\build\bin\vsTGW.exe
```
or run in bin folder, this way should copy data into `build/bin`
```bash
cd build/bin
.\vsTGW.exe
```

## More Information
This project uses [CMake SFML Project Template](https://github.com/SFML/cmake-sfml-project/tree/sfml2) from [SFML official website](https://www.sfml-dev.org/tutorials/2.6/)