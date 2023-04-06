<h1>Better JSON Parser</h1>
<h2>DISCLAIMER</h2>
<p>This is just an <strong>Preview</strong> release and doesn't gurantee full functionality or stability. At current point of time, it is not more than an simple example of how two write an fast JSON parser using C.</p>
<h2>Setup</h2>
<ul>
<li>
<p>Add the needed source files to your compile path: <strong>Parser/*.c</strong>, 
<strong>Storage/*.c</strong> and <strong>Utils/*.c</strong></p>
</li>
<li>
<p>Include <strong>Parser/SJsonParser.c</strong> and <strong>Parser/SJsonParserA.c</strong> for Json Arrays.</p>
</li>
<li>
<p>Include Parser/SJsonParser.c and Parser/SJsonParserA.c for Json Arrays.</p>
</li>
<li>
<p>Parse a Json file by calling sjs_loadFile(...)</p>
</li>
</ul>

<h2>Example</h2>
<p>Simple example of how you can read a json file that looks like the following:</p>

```json
{
  "name": "Bob Nagel",
  "age": 40,
  "city": "Chicago",
  "pets": ["dog", "bird", "turtle"]
}
```

<p>Start by loading the Json file...</p>

```cpp
#include "Parser/SJsonParser.h" /* basic json parser */
#include "Parser/SJsonParserA.h" /* json parser for arrays */

void main()
{
    /* load example.json */
    SQTree*json = sjs_loadFile("example.json");
    /* set name to "Hans Wurst" */
    sjs_setPair(json, "name", sjs_createValueString("Hans Wurst"));
    /* set age property to  15.5 */
    sjs_setPair(json, "age", sjs_createValueDouble(15.5));
    /* add male property and set it to true */
    sjs_setPair(json, "male", sjs_createValueBool(1));

    /* load pet array */
    SVector*json_array = sjs_getValue(json, "pets")._jsonArray;
    /* get second item of pet array */
    printf("First pet: %s\n", sjs_arr_getValue(sjs_getValue(json, "pets")._jsonArray, 1)._string);
    /* free array */
    sjs_arr_delete(json_array);

    /* write changes to file */
    sjs_save(json, "test2.json");
    exit(0);
}
```
<p>But further documentation can be found in the Header files.</p>

<h2>License</h2>
<p>GNU GPL 3.0</p>