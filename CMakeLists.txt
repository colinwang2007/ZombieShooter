cmake_minimum_required(VERSION 3.14)
project(ZombieShooter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Zombie.h Player.h Zombie.cpp Player.cpp ZombieArena.h CreateBackground.cpp TextureHolder.cpp TextureHolder.h createHorde.cpp Bullet.h Bullet.cpp main.cpp Pickup.cpp Pickup.h pathBase.h)
add_executable(HelloSFML ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(HelloSFML sfml-system sfml-window sfml-graphics sfml-audio sfml-network)