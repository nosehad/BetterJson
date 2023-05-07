#include <stdio.h>
#include <stdlib.h>

#include "include/SJsonParser.h"  /* basic json parser */
#include "include/SJsonParserA.h" /* json parser for arrays */

void main()
{
    /* load example.json */
    JsonData *json = sjs_loadFile("example.json");
    /* set name to "Hans Wurst" */
    sjs_setPair(json, "name", sjs_createValueString("Hans Wurst"));
    /* set age property to  15.5 */
    sjs_setPair(json, "age", sjs_createValueDouble(15.5));
    /* add male property and set it to true */
    sjs_setPair(json, "male", sjs_createValueBool(1));

    /* load pet array */
    JsonArrayData *json_array = sjs_getValue(json, "pets")._jsonArray;
    /* get second item of pet array */
    printf("First pet: %s\n", sjs_arr_getValue(json_array, 1)._string);
    /* free array */
    sjs_arr_delete(json_array);

    /* write changes to file */
    sjs_save(json, "test2.json");
    exit(0);
}