cmake_minimum_required(VERSION 3.5)

# Set the project name
project (carpid)

# Add an executable
add_executable(carpid src/main.cpp)
target_compile_options(carpid PRIVATE -Wall -Werror -Wextra)
target_link_libraries(carpid wiringPi pthread)
