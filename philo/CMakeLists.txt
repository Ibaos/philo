cmake_minimum_required(VERSION 3.27)
project(philo C)

set(CMAKE_C_STANDARD 11)

add_executable(philo sources/main.c
        includes/philo.h
        includes/error_messages.h)
