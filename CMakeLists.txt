cmake_minimum_required(VERSION 3.26)
project(orderbookds)

set(CMAKE_CXX_STANDARD 14)

add_executable(orderbookds main.cpp
        order.h
        orderbook.cpp
        orderbook.h
        marketdepth.h
        Message.cpp
        Message.h
)
