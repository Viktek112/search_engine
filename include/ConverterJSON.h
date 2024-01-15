#pragma once
#include <iostream>
#include "Structs.h"
#include "nlohmann/json.hpp"

class ConverterJSON {
private:
    const std::string configJsonPath = "config.json";
    nlohmann::json configJsonFile;
    const std::string requestsJsonPath = "requests.json";
    nlohmann::json requestsJsonFile;
    const std::string answersJsonPath = "answers.json";
    nlohmann::json answersJsonFile;


public:
    ConverterJSON();

    std::vector<std::string> GetTextDocuments();

    int GetResponsesLimit();

    std::vector<std::string> GetRequests();

    void putAnswers(std::vector<std::vector<RelativeIndex>>answers);
};
