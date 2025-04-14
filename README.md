# vs-TGW
## Introduction
This is a simple shoot game.  
Current version 0.1.1
## Play the game
Download the game package:
   - **Standard** (`vsTGW_v0.1.0.zip`): Default difficulty setting
   - **Easy** (`vsTGW_v0.1.1_easy.zip`): Simplified difficulty mode
  
Operation　　　　　　| Button  
:-------------------|:---  
start the game      | <kbd>Enter</kbd>  
move player　　　　　| <kbd>W</kbd> <kbd>A</kbd> <kbd>S</kbd> <kbd>D</kbd>  
shoot               | <kbd>J</kbd>  
exit the game       | <kbd>Esc</kbd>


## Build and run
### Requirement
- Cmake minimum version 3.28
- C++ compile which supports c++ 17
- Git
### Build project
Clone or download the project, under `\vs-TGW>` folder, in termial:
```bash
cmake -B build      # may need to add -G according to the cmake you use
# For example: cmake -B build -G "MinGW Makefiles", if you are using MinGW
cmake --build build
.\build\bin\vsTGW.exe   # run the game
```

## More Information
This project uses [CMake SFML Project Template](https://github.com/SFML/cmake-sfml-project/tree/sfml2) from [SFML official website](https://www.sfml-dev.org/tutorials/2.6/)