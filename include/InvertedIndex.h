#pragma once
#include <mutex>
#include <iostream>

class InvertedIndex{
public:
    InvertedIndex() = default;
};

std::mutex freqAccess;

std::string wordCleaning(std::string word);