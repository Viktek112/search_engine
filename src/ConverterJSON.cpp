#include "ConverterJSON.h"
#include "nlohmann/json.hpp"
#include "Errors.h"
#include <fstream>

class ConverterJSON {
private:
    const std::string configJsonPath = "..\\config.json";
    nlohmann::json configJsonFile;
    const std::string requestsJsonPath = "..\\requests.json";
    nlohmann::json requestsJsonFile;
    const std::string answersJsonPath = "..\\answers.json";
    nlohmann::json answersJsonFile;


public:
    ConverterJSON(){
        std::ifstream ifSJsonFile(configJsonPath);
        if (ifSJsonFile.is_open()) {
            ifSJsonFile >> configJsonFile;
        } else {
            throw OpeningError(configJsonPath);
        }
        ifSJsonFile.close();
        ifSJsonFile.open(requestsJsonPath);
        if (ifSJsonFile.is_open()) {
            ifSJsonFile >> requestsJsonFile;
        } else {
            throw OpeningError(requestsJsonPath);
        }
        ifSJsonFile.close();
    };

    std::vector<std::string> GetTextDocuments(){
        std::vector<std::string> docums;
        if (configJsonFile.contains("files")) {
            for (const auto& i: configJsonFile["files"]) {
                std::string bufPath = i;
                std::replace(bufPath.begin(), bufPath.end(), '/', '\\');
                std::ifstream subFile(bufPath);
                if (subFile.is_open()) {
                    std::ostringstream sstr;
                    sstr << subFile.rdbuf();
                    docums.push_back(sstr.str());
                } else {
                    throw OpeningError(bufPath);
                }
            }
        } else {
            throw JsonFileContainingError(configJsonPath, "files");
        }

        return docums;
    };

    int GetResponsesLimit(){
        if (configJsonFile.contains("config")) {
            if (configJsonFile["config"].contains("max_responses")) {
                return (int) configJsonFile["config"]["max_responses"];
            } else {
                throw JsonFileContainingError(configJsonPath, "max_responses");
            }
        } else {
            throw JsonFileContainingError(configJsonPath, "config");
        }
    };

    std::vector<std::string> GetRequests(){
        std::vector <std::string> requests = {};
        if (requestsJsonFile.contains("requests")) {
            for (const auto& i: requestsJsonFile["requests"]) {
                requests.push_back((std::string)i);
            }
            return requests;
        } else {
            throw JsonFileContainingError(configJsonPath, "requests");
        }
    };

    void putAnswers(std::vector<std::vector<std::pair<int, float>>>answers){
        for (int i = 0; i < answers.size(); i++) {
            std::string numOfRequest;
            for (int n = 0; n < 3-std::to_string(i).length();n++) {
                numOfRequest += "0";
            }
            numOfRequest += std::to_string(i+1);

            if (!answers[i].empty()) {
                answersJsonFile["answers"]["request" + numOfRequest]["result"] = "true";
                for (auto & j : answers[i]) {
                    nlohmann::json::value_type block;
                    block["docid"] = j.first;
                    block["rank"] = j.second;
                    answersJsonFile["answers"]["request" + numOfRequest]["relevance"].push_back(block);
                }
            }
            std::ofstream ofstreamJsonFile(answersJsonPath);
            ofstreamJsonFile << answersJsonFile;
            ofstreamJsonFile.close();
        }
    };
};
