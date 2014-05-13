#! /bin/sh

g++ -std=c++11 ../unit_test.cpp -I ../../../cppcomponents -I ../../../cppcomponents_concurrency/ -I ../../../cppcomponents_asio_runtime/ - -pthread -ldl -o unit_test