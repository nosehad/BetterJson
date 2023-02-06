#include "test.h"

void main()
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

    sstr_print(sjs_toString(tree));

    int file = fopen("test.json", "r")->_fileno;
    struct stat st;
    fstat(file, &st);
    char buff[st.st_size+1];
    read(fopen("test.json", "r")->_fileno, &buff, st.st_size);

    SQTree* parsedj = sjs_parseString(&buff);

    printf("%d\n", *((char*)sqtr_get(parsedj, "bamboo")));

    sstr_print(sjs_toString(parsedj));
}