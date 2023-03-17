#ifndef KEYNOTFOUNDEXCEPTION_H
    #define KEYNOTFOUNDEXCEPTION_H

    #include <iostream>
    #include <exception>

    namespace betterJson
    {
        /* gets thrown when trying to pop the leftmost element out of an empty Json file */
        class EmptyJsonException : public std::runtime_error
        {
        public:
            EmptyJsonException(const std::string& message) : std::runtime_error(message) {}
        };

        /* gets thrown when trying to access an key that doesnt exist */
        class JsonKeyNotFoundException : public std::runtime_error
        {
        public:
            JsonKeyNotFoundException(const std::string& message) : std::runtime_error(message) {}
        };

        /* gets thrown when trying to access an value of an invalid type */
        class InvalidValueException : public std::runtime_error
        {
        public:
            InvalidValueException(const std::string& message) : std::runtime_error(message) {}
        };

        /* gets thrown when trying to access an value of an invalid type */
        class JsonArrayOutOfBoundsException : public std::runtime_error
        {
        public:
            JsonArrayOutOfBoundsException(const std::string &message) : std::runtime_error(message) {}
        };
    }

#endif