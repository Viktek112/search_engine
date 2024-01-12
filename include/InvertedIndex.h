#pragma once
#include "Structs.h"
#include "../src/Structs.cpp"
#include <mutex>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <thread>

std::string wordCleaning(std::string word);

class InvertedIndex {
private:
    std::map<std::string, std::vector<Entry>> freqDictionary;
    std::vector<std::string> docs = {};

    void convertDocumentsIntoDatabase(const std::string& txt, size_t num);

public:
    void UpdateDocumentBase(const std::vector<std::string>& doc);

    std::map<std::string, std::vector<Entry>> getFreqDictionary();
};

