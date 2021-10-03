cmake_minimum_required(VERSION 3.20)
project(minishell_project C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(minishell_project
        minishell.c)
