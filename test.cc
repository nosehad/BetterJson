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
    FILE* file = fopen("test.json", "r");
    struct stat st;
    fstat(file->_fileno, &st);
    char*buff = (char*)__builtin_alloca(10000);
    read(file->_fileno, buff, st.st_size);
    buff[st.st_size] = 0;

    SVector* parsedj = sjs_arr_parseString(buff);
    /* check if array was parsed correctly */
    SString* parsed_array = sjs_arr_toString(parsedj,2);
    sstr_print(parsed_array);

    printf("%s\n", sjs_arr_getValue(parsedj, 0)._string);
    
    /* freeup data */
    sstr_delete(parsed_array);
    sjs_arr_delete(parsedj);


    /* close test file */
    fclose(file);
}
// 1m14.519s