cmake_minimum_required(VERSION 3.28)
project(vsTGW LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
# Add vsTGW executable from /src directory
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/game.cpp
    ${SRC_DIR}/player.cpp
    ${SRC_DIR}/bullet.cpp
    ${SRC_DIR}/boss.cpp
    ${SRC_DIR}/bossAttack.cpp
    ${SRC_DIR}/soundManager.cpp
    ${SRC_DIR}/stateManager.cpp
)
add_executable(vsTGW ${SOURCES})

target_link_libraries(vsTGW PRIVATE sfml-graphics sfml-audio)
target_compile_features(vsTGW PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET vsTGW
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:vsTGW>
        VERBATIM)
endif()
