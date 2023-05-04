#!/bin/bash
echo "Installng BetterJson library."

# Create installation directories
mkdir -p /usr/local/include/bjson
mkdir -p /usr/local/lib

# Copy header files
cp -r include/*.h /usr/local/include/bjson
cp -r include/*.h /usr/local/include/bjson

# Compile library
gcc -w -shared -fPIC -o build/libbjson.so Utils/Convert.c Utils/SString.c Storage/SQTree.c Storage/SVector.c Parser/SJsonParser.c Parser/ValueCreator.c Parser/SJsonParserA.c
# Copy library file
cp build/libbjson.so /usr/local/lib
cp build/libbjson.so /usr/lib

# Set environment variables
echo "export BJSON_HOME=/usr/local" >> ~/.bashrc
echo "export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:\$BJSON_HOME/lib" >> ~/.bashrc

# Refresh environment variables
source ~/.bashrc

echo "Installation complete."
