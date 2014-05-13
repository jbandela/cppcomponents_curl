#! /bin/sh
# In this we assume that libssl.a and libcrypto.a and libboost_regex.a are in the current directory and are built with -fPIC. for openssl you can use ./config -fPIC and for boost you can use ./b2 cxxflags='-fPIC'

g++ -std=c++11 ../../implementation/cppcomponents_curl.cpp -I ../../../cppcomponents -I ../../implementation/external_dependencies  -fvisibility=hidden -lcurl -lssl -lcrypto -Wl,--no-undefined -ldl  -fPIC -shared -pthread -o cppcomponents_curl_dll.so 
