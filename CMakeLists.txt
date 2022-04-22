cmake_minimum_required(VERSION 3.19)
project(optimisation)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR ./libs/SDL2/include)
set(SDL2_LIB_DIR ./libs/SDL2/lib/x64)

set(SDL2TTF_INCLUDE_DIR ./libs/SDL2_TTF/include)
set(SDL2TTF_LIB_DIR ./libs/SDL2_TTF/lib/x64)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR} ${SDL2TTF_LIB_DIR})
add_executable(optimisation main.cpp Reader.h Tournee.h Recuit.h Solution.h Voisins.h VoisinEchange.h TypeVoisin.h VoisinInsertion.h Interface.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_ttf)
