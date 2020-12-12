cmake_minimum_required(VERSION 3.10)

project(
    App             # Name of our application
    VERSION 1.0     # Version of our software
    LANGUAGES CXX)  # Language that we are using

set(CMAKE_CXX_STANDARD 11)

include_directories("/usr/include/")
include_directories("./include/")

link_directories("/usr/local/lib/")


add_executable(Client ./src/main.cpp ./src/Miner.cpp ./src/sha256.cpp)
add_executable(Server ./src/ServerMain.cpp ./src/Blockchain.cpp ./src/Block.cpp )

target_link_libraries(Client sfml-system sfml-network)
target_link_libraries(Server sfml-system sfml-network)
