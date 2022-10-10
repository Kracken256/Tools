#!/bin/bash

echo "Building..."
g++ src/status.cpp -o status -std=c++20  -static-libstdc++ -static
strip status

