#include "test.hh"


int main()
{
    SQTree* tree = sqtr_create();
    sqtr_set(tree, "test", "aGJri");
    sqtr_set(tree, "bamboo", "ryGdK");
    sqtr_set(tree, "bobba", "loXLu");
    sqtr_set(tree, "lvaus", "mQdQb");
    sqtr_set(tree, "aha", "TxyMD");
    sqtr_free(tree);
    /*printf("%s\n", sqtr_get(tree, "test"));
    printf("%s\n", sqtr_get(tree, "bamboo"));
    printf("%s\n", sqtr_get(tree, "bobba"));
    printf("%s\n", sqtr_get(tree, "lvaus"));
    printf("%s\n", sqtr_get(tree, "aha"));
    sqtr_set(tree, "bamboo", "bruh");
    printf("%s\n", sqtr_get(tree, "test"));
    printf("%s\n", sqtr_get(tree, "bamboo"));
    printf("%s\n", sqtr_get(tree, "bobba"));
    printf("%s\n", sqtr_get(tree, "lvaus"));
    printf("%s\n", sqtr_get(tree, "aha"));
    sqtr_print(tree);
    sqtr_delete(tree, "test");
    sqtr_print(tree);
        printf("%s\n", sqtr_get(tree, "bamboo"));
    printf("%s\n", sqtr_get(tree, "bobba"));
    printf("%s\n", sqtr_get(tree, "lvaus"));
    printf("%s\n", sqtr_get(tree, "aha"));*/
    //sqtr_delete(tree, "bamboo");

    //sstr_print(sjs_toString(tree));

    /* open file used for testing */
    SQTree*json = sjs_loadFile("test.json");
    sjs_insertPair(json, "bruh", sjs_createValueString("lol"));
    
    /*sjs_arr_appendElement("test.json", "[123, 1234, 3, 1, 2,12 ,4,4 ]", 29);
    return -1;
    FILE* file = fopen("test.json", "r");
    struct stat st;
    fstat(file->_fileno, &st);
    char*buff = (char*)__builtin_alloca(10000);
    read(file->_fileno, buff, st.st_size);
    buff[st.st_size] = 0;

    SVector* parsedj = sjs_arr_parseString(buff);
    //svect_remove(parsedj, 0);
    /check if array was parsed correctly/
    char* parsed_array = sjs_arr_toCString(parsedj);
    printf("%s\n", parsed_array);
    //printf("%*s\n", 2,parsed_array);

    //printf("%d\n", sjs_getValue(sjs_arr_getValue(parsedj, 1)._jsonData, "age")._);
    
    / freeup data /
    //sjs_arr_delete(parsedj);


    / close test file /
    fclose(file);*/
}
// 1m14.519s