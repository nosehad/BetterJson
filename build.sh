#!/bin/bash

mkdir -p ./build

mkdir -p ./build
mkdir -p ./build/include 

cp -r include ./build/include

gcc -shared -fPIC -o ./build/libbjson.so Utils/Convert.c Utils/SString.c Storage/SQTree.c Storage/SVector.c Parser/SJsonParser.c Parser/ValueCreator.c Parser/SJsonParserA.c