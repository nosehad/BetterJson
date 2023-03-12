#include "test.hpp"
#include <string>

int main()
{
    /*char* str = cstr_createe();
    cstr_appends(str, "Hello World!\n");
    cstr_appends(str, "Hello World!\n");
    for(int i = 0; i < 1000000; ++i)
        cstr_appends(str, "We and our partners use cookies to Store and/or access information on a device. We and our partners use data for Personalised ads and content, ad and content measurement, audience\n");
    cstr_serialize(str);
    //printf("%s\n", str);
    cstr_delete(str);*/

    SString* str = sstr_createe();
    for(int i = 0; i < 1000000; ++i)
        sstr_appends(str, "We and our partners use cookies to Store and/or access information on a device. We and our partners use data for Personalised ads and content, ad and content measurement, audience\n", 180);
    

    /*std::string* str = new std::string();
    for(int i = 0; i < 1000000; ++i)
        str->append("We and our partners use cookies to Store and/or access information on a device. We and our partners use data for Personalised ads and content, ad and content measurement, audience\n");
    */
    return -875756;
}