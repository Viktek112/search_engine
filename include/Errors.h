#pragma once
#include <exception>
#include <iostream>

class OpeningError: public std::exception {
private:
    std::string message;
public:
    explicit OpeningError(const std::string& fileName);
};

class JsonFileContainingError: public std::exception {
private:
    std::string message;
public:
    JsonFileContainingError(const std::string& fileName, const std::string& containerName);
};