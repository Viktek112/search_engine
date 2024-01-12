#pragma once
#include "InvertedIndex.h"
#include "ConverterJSON.h"
#include <vector>
#include "Structs.h"
#include <map>
#include <sstream>

class SearchServer {
private:
    InvertedIndex index;
    ConverterJSON converter;
    std::map<std::string, std::vector<Entry>> freqDictionary;
public:
    explicit SearchServer(InvertedIndex& idx);

    std::vector<std::string> requestsInput();

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& requestsInput);
};