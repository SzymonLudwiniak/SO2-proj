cmake_minimum_required(VERSION 3.20)
project(SO2-proj)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-pthread)

add_executable(
        SO2-proj
        src/main.cpp
        src/CargoTrain.cpp
        src/Driver.cpp
        src/PassengerTrain.cpp
        src/Station.cpp
        src/Train.cpp

        include/CargoTrain.h
        include/Driver.h
        include/PassengerTrain.h
        include/RouteElement.h
        include/Station.h
        include/Train.h
        include/enums/SemaphoreEnum.h
)

