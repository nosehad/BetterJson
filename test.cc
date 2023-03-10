#include "test.hh"


int main()
{
    SQTree* tree = sqtr_create();
    sqtr_set(tree, "test", "aGJri");
    sqtr_set(tree, "bamboo", "ryGdK");
    sqtr_set(tree, "bobba", "loXLu");
    sqtr_set(tree, "lvaus", "mQdQb");
    sqtr_set(tree, "aha", "TxyMD");
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

    int file = fopen("test.json", "r")->_fileno;
    struct stat st;
    fstat(file, &st);
    char*buff = (char*)__builtin_alloca(10000);
    read(fopen("test.json", "r")->_fileno, buff, st.st_size);
    buff[st.st_size] = 0;
    printf("%s\n", buff);

    SVector* parsedj = sjs_arr_parseString(buff);
    //svect_set(parsedj, 1, "sdasd");
    printf("%s\n", svect_get(parsedj, 1 ));
    sstr_print(sjs_arr_toString(parsedj,2));
}
// 1m14.519s