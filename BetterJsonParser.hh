#ifndef BETTERJSONPARSER_H
    #define BETTERJSONPARSER_H

    #include "SJsonParser.h"
    #include "SQTree.h"

    /* c++ headers */
    #include <string>
    #include <utility>

    using namespace std;

    namespace betterJson
    {
        class JsonData
        {
            private:
            SQTree*json;

            inline char*getkey(std::string str) const
            {
                char*key = (char*)malloc(str.size());
                memcpy(key, str.begin().base(), str.size());
                return key;
            }

            public:
            JsonData();


            /* Operators */
            /* addition operator */
            JsonData& operator+=(const std::pair<std::string, int>& add) noexcept
             {
                sqtr_set(this->json, this->getkey(add.first), sstr_convertIntToCStr(add.second));
                return *this;
            }
            
            JsonData& operator+=(const std::pair<std::string, unsigned int>& add) noexcept 
            {
                sqtr_set(this->json, this->getkey(add.first), sstr_convertUIntToCStr(add.second));
                return *this;
            }

            JsonData& operator+=(const std::pair<std::string, long long>& add) noexcept
            {
                sqtr_set(this->json, this->getkey(add.first), sstr_convertQWORDToCStr(add.second));   
                return *this;
            }
            
            JsonData& operator+=(const std::pair<std::string, unsigned long long>& add) noexcept 
            {
                sqtr_set(this->json, this->getkey(add.first), sstr_convertUQWORDToCStr(add.second));          
                return *this;
            }

            JsonData& operator+=(const std::pair<std::string, std::string>& add) noexcept
             {
                sqtr_set(this->json, this->getkey(add.first), (char*)add.second.c_str());
                return *this;
            }

            JsonData& operator+=(const std::pair<std::string, std::string>& add) noexcept 
            {
                sqtr_set(this->json, this->getkey(add.first), (char*)add.second.c_str());      
                return *this;
            }

            /* substraction operator */
            JsonData& operator-=(const std::string& rem) noexcept
            {
                sqtr_delete(this->json, (char*)rem.c_str());
                return *this;
            }

            /* get function */
            std::string* getValue(const std::string& key) const noexcept
            {
                return new std::string((char*) sqtr_get(json, (char*)key.c_str()) +1);
            }

            ~JsonData()
            {
                sqtr_free(json);
            }
        };
    }

#endif