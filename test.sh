mkdir -p build

# check if GCC is installed
if command -v gcc >/dev/null 2>&1; then
    g++ test.cc Utils/Convert.c Utils/SString.c Storage/SQTree.c Storage/SVector.c Parser/SJsonParser.c Parser/SJsonParserA.c -w -g -o build/betterjson &&  valgrind --track-origins=yes --leak-check=full ./build/betterjson
else
    echo -e "\033[1m\033[31mError\033[0m: The GNU Compiler Colection GCC isn't installed on your system."
    echo -e "Run \033[47mapt install -y gcc\033[0m to install it."
    exit 1
fi