#include "Errors.h"
#include <iostream>
#include <exception>

class OpeningError: public std::exception {
private:
    std::string message;
public:
    explicit OpeningError(const std::string& fileName): message{ "Failed to open file: " + fileName + "."} {}
    [[nodiscard]] const char* what() const noexcept override{
        return message.c_str();
    }
};

class JsonFileContainingError: public std::exception {
private:
    std::string message;
public:
    JsonFileContainingError(const std::string& fileName, const std::string& containerName): message{"Failed to find container "+containerName+" in file "+fileName+"."} {}
    [[nodiscard]] const char* what() const noexcept override{
        return message.c_str();
    }
};