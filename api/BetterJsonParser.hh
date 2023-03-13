#ifndef BETTERJSONPARSER_H
    #define BETTERJSONPARSER_H

    #include "../Parser/SJsonParserA.h"
    #include "../Parser/SJsonParser.h"
    #include "../Storage/SVector.h"
    #include "../Storage/SQTree.h"
    #include "../Utils/Convert.h"

    #include "Exceptions.hh"

    #include <string>
    #include <utility>
    #include <variant>

    using namespace std;

    #define JsonValue std::variant<bool, int, unsigned int, long long, unsigned long long, double, std::string*, std::nullptr_t, betterJson::JsonArray*, betterJson::JsonData*>

    namespace betterJson
    {

        /* contains a key and a Corresponding value */
        class JsonObject
        {
            public:
            JsonObject(std::string* key, JsonValue value) :
            key(key),
            value(value) {};
            private:
            std::string* key;
            JsonValue value;
        };

        class JsonElement
        {
            public:
            JsonElement(JsonValue value) :
            value(value) {};
            private:
            JsonValue value;
        };

        enum class SJS_Datatype : char
        {
            SJS_JSON = 1,
            SJS_ARRAY = 2,
            SJS_NUM = 3,
            SJS_NULL = 4,
            SJS_STRING = 5,
            SJS_BOOL = 6
        };

        class JsonData
        {
            private:
            mutable SQTree*json;

            inline char*getkey(const std::string* str) const noexcept
            {
                char*key = (char*)malloc(str->size());
                memcpy(key, str->begin().base(), str->size());
                return key;
            }

            inline JsonObject*getObject(char* raw_value, std::string* key) const
            {
                if(raw_value == null)
                    throw JsonKeyNotFoundException("No value for " + *key + " found.");
                switch(*raw_value++)
                {
                    case _SJS_BOOL:
                        return new betterJson::JsonObject(key, (bool)strcmp(raw_value, "true") == 0);
                    case _SJS_NUM:
                        /* examine exact number type */
                        switch (convert_getType(raw_value))
                        {
                            case NT_FLOAT:
                                return new betterJson::JsonObject(key, convert_CStrToDouble(raw_value));
                            case NT_INT:
                                return new betterJson::JsonObject(key, convert_CStrToInt(raw_value));
                            case NT_LONG:
                                return new betterJson::JsonObject(key, convert_CStrToLong(raw_value));
                            case NT_NONE: /* check if number is false detected */
                                return new betterJson::JsonObject(key, new std::string(raw_value));
                        }
                    case _SJS_STRING:
                        return new betterJson::JsonObject(key, new std::string(raw_value));
                    case _SJS_NULL:
                        return new betterJson::JsonObject(key, nullptr);
                    case _SJS_ARRAY:
                        return new betterJson::JsonObject(key, new betterJson::JsonArray(raw_value));
                    case _SJS_JSON:
                        return new betterJson::JsonObject(key, new betterJson::JsonData(raw_value));
                    default:
                        throw betterJson::InvalidValueException(std::string("The Valuetype " + *(raw_value-1), "is invalid."));

                }
                return nullptr;
            }

            public:
            JsonData(char* data)
            {
                json = sjs_parseString(data);
            }

            /**
             * @brief get corresponding value of key
             * 
             * @param key 
             * @return value of key as std::string* 
             */
            std::string* 
            getString(const std::string& key) const
            {
                char* value = (char*)sqtr_get(json, (char*)key.c_str());
                if(value == null)
                    throw JsonKeyNotFoundException("No value for " + key + " found.");

                return new std::string(value + 1);
            }

            /**
             * @brief get corresponding value of key
             * 
             * @param key 
             * @return value of key as int
             */
            int 
            getInt(const std::string& key) const
            {
                char* value = (char*)sqtr_get(json, (char*)key.c_str());
                if(value == null)
                    throw JsonKeyNotFoundException("No value for " + key + " found.");

                return convert_CStrToInt(value +1);
            }

            /**
             * @brief get corresponding value of key
             * 
             * @param key 
             * @return value of key as unsigned integer
             */
            unsigned int 
            getUInt(const std::string& key) const
            {
                char* value = (char*)sqtr_get(json, (char*)key.c_str());
                if(value == null)
                    throw JsonKeyNotFoundException("No value for " + key + " found.");

                return convert_CStrToUInt(value +1);
            }

            /**
             * @brief get corresponding value of key
             * 
             * @param key 
             * @return value of key as 64 bit integer
             */
            long long 
            getLong(const std::string& key) const
            {
                char* value = (char*)sqtr_get(json, (char*)key.c_str());
                if(value == null)
                    throw JsonKeyNotFoundException("No value for " + key + " found.");

                return convert_CStrToLong(value +1);
            }

            /**
             * @brief get corresponding value of key
             * 
             * @param key 
             * @return value of key as unsigned 64 bit integer
             */
            unsigned long long 
            getULong(const std::string& key) const
            {
                char* value = (char*)sqtr_get(json, (char*)key.c_str());
                if(value == null)
                    throw JsonKeyNotFoundException("No value for " + key + " found.");

                return convert_CStrToULong(value +1);
            }

            /**
             * @brief get corresponding value of key
             * 
             * @param key 
             * @return value of key as float
             */
            float 
            getFloat(const std::string& key) const
            {
                char* value = (char*)sqtr_get(json, (char*)key.c_str());
                if(value == null)
                    throw JsonKeyNotFoundException("No value for " + key + " found.");

                return convert_CStrToFloat(value +1);
            }

            /**
             * @brief get corresponding value of key
             * 
             * @param key 
             * @return value of key as double 
             */
            double 
            getDouble(const std::string& key) const
            {
                char* value = (char*)sqtr_get(json, (char*)key.c_str());
                if(value == null)
                    throw JsonKeyNotFoundException("No value for " + key + " found.");

                return convert_CStrToDouble(value +1);
            }


            /**
             * @brief Pops the Element of containing key 
             * 
             * @return the key and value of the leftmost Element wrapped in an JsonObject
             */
            JsonObject* 
            pop(std::string* key)
            {
                char* raw_value = (char*)sqtr_pop(this->json, (char*)key->c_str());
                return this->getObject(raw_value, key);
            }

            /**
             * @brief Pops the Leftmost Element out of the internal representation of the JSON Data
             * 
             * @return the key and value of the leftmost Element wrapped in an JsonObject
             */
            JsonObject* 
            popl(void) noexcept
            {
                SQNode* node = sqtr_popl(this->json);
                char* raw_value = node->value;
                char* raw_key = node->key;
                free(node->value);
                free(node->key);
                free(node);
                return this->getObject(raw_value, new std::string(raw_key));
            }

            /**
             * @brief removes the element coresponding to <key>
             * 
             * @return the key and value of the leftmost Element wrapped in an JsonObject
             */
            inline void 
            remove(const std::string& key) noexcept
            {
                sqtr_delete(this->json, (char*)key.c_str());
            }


            /**
             * @brief adds an element to the JSON Data
             * 
             * @param add Pair that gets added to the JSON Data
             */
            inline void 
            add(const std::pair<std::string, int>& add) noexcept
            {
                char* value = (char*)malloc(MAX_LENGTH_INT + 1);
                convert_IntToCStr(add.second, value);
                sqtr_set(this->json, this->getkey(&(add.first)), value);
            }
            
            /**
             * @brief adds an element to the JSON Data
             * 
             * @param add Pair that gets added to the JSON Data
             */
            inline void 
            add(const std::pair<std::string, unsigned int>& add) noexcept 
            {
                char* value = (char*)malloc(MAX_LENGTH_UINT + 1);
                convert_UIntToCStr(add.second, value);
                sqtr_set(this->json, this->getkey(&(add.first)), value);
            }

            /**
             * @brief adds an element to the JSON Data
             * 
             * @param add Pair that gets added to the JSON Data
             */
            inline void 
            add(const std::pair<std::string, long long>& add) noexcept
            {
                char* value = (char*)malloc(MAX_LENGTH_LONG + 1);
                convert_LongToCStr(add.second, value);
                sqtr_set(this->json, this->getkey(&(add.first)), value);
            }
            
            /**
             * @brief adds an element to the JSON Data
             * 
             * @param add Pair that gets added to the JSON Data
             */
            inline void 
            add(const std::pair<std::string, unsigned long long>& add) noexcept 
            {
                char* value = (char*)malloc(MAX_LENGTH_ULONG + 1);
                convert_ULongToCStr(add.second, value);
                sqtr_set(this->json, this->getkey(&(add.first)), value);          
            }


            /**
             * @brief adds an element to the JSON Data
             * 
             * @param add Pair that gets added to the JSON Data
             */
            inline void 
            add(const std::pair<std::string, double>& add) noexcept
            {
                char* value = (char*)malloc(MAX_LENGTH_FLOAT + 1);
                convert_DoubleToCStr(add.second, value);
                sqtr_set(this->json, this->getkey(&(add.first)), value);   
            }
            
            /**
             * @brief adds an element to the JSON Data
             * 
             * @param add Pair that gets added to the JSON Data
             */
            inline void 
            add(const std::pair<std::string, float>& add) noexcept 
            {
                char* value = (char*)malloc(MAX_LENGTH_FLOAT + 1);
                convert_FloatToCStr(add.second, value);
                sqtr_set(this->json, this->getkey(&(add.first)), value);          
            }

            /**
             * @brief adds an element to the JSON Data
             * 
             * @param add Pair that gets added to the JSON Data
             */
            inline void 
            add(const std::pair<std::string, std::string>& add) noexcept
             {
                sqtr_set(this->json, this->getkey(&(add.first)), (char*)add.second.c_str());
            }

            /* Operators */
            /* addition operator */
            JsonData& 
            operator+=(const std::pair<std::string, int>& add) noexcept
            {
                this->add(add);
                return *this;
            }
            
            JsonData& 
            operator+=(const std::pair<std::string, unsigned int>& add) noexcept 
            {
                this->add(add);
                return *this;
            }

            JsonData& 
            operator+=(const std::pair<std::string, long long>& add) noexcept
            {
                this->add(add);
                return *this;
            }
            
            JsonData& 
            operator+=(const std::pair<std::string, unsigned long long>& add) noexcept 
            {
                this->add(add); 
                return *this;
            }

            /* floating points */
            JsonData& 
            operator+=(const std::pair<std::string, float>& add) noexcept
            {
                this->add(add);
                return *this;
            }
            
            JsonData& 
            operator+=(const std::pair<std::string, double>& add) noexcept 
            {
                this->add(add); 
                return *this;
            }

            JsonData& 
            operator+=(const std::pair<std::string, std::string>& add) noexcept
            {
                this->add(add);
                return *this;
            }

            /* substraction operator */
            JsonData& 
            operator-=(const std::string& rem) noexcept
            {
                this->remove(rem);
                return *this;
            }

            ~JsonData()
            {
                sqtr_free(json);
            }
        };

        class JsonArray
        {
            private:
            SVector* array;
            
            inline JsonElement*
            getObject(char* raw_value, long long index) const
            {
                if(raw_value == null)
                    throw JsonKeyNotFoundException(std::string("No value for " + index, "found."));
                switch(*raw_value++)
                {
                    case _SJS_BOOL:
                        return new betterJson::JsonElement((bool)strcmp(raw_value, "true") == 0);
                    case _SJS_NUM:
                        /* examine exact number type */
                        switch (convert_getType(raw_value))
                        {
                            case NT_FLOAT:
                                return new betterJson::JsonElement(convert_CStrToDouble(raw_value));
                            case NT_INT:
                                return new betterJson::JsonElement(convert_CStrToInt(raw_value));
                            case NT_LONG:
                                return new betterJson::JsonElement(convert_CStrToLong(raw_value));
                            case NT_NONE: /* check if number is false detected */
                                return new betterJson::JsonElement(new std::string(raw_value));
                        }
                    case _SJS_STRING:
                        return new betterJson::JsonElement(new std::string(raw_value));
                    case _SJS_NULL:
                        return new betterJson::JsonElement(nullptr);
                    case _SJS_ARRAY:
                        return new betterJson::JsonElement(new betterJson::JsonArray(raw_value));
                    case _SJS_JSON:
                        return new betterJson::JsonElement(new betterJson::JsonData(raw_value));
                    default:
                        throw betterJson::InvalidValueException(std::string("The Valuetype " + *(raw_value-1), "is invalid."));

                }
                return nullptr;
            }

            public:
            JsonArray(char* data)
            {
                array = sjs_arr_parseString(data);
            }
        };
    }

#endif