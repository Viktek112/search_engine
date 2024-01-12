#include "SearchEngine.h"

SearchServer::SearchServer(InvertedIndex& idx) : index(idx){
    freqDictionary = idx.getFreqDictionary();
};

std::vector<std::string> SearchServer::requestsInput() {
    return converter.GetRequests();
};

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& requestsInput){
    std::vector<std::vector<RelativeIndex>> result = {};
    for (const auto & i : requestsInput) {
        std::map<std::string, Entry> wordRelevance;
        std::vector<int> absoluteRelevance = {};
        std::vector<RelativeIndex> relevantRelevance = {};
        result.emplace_back();
        std::istringstream iss(i);
        std::string buf;
        std::vector<std::string> uniqueWords = {};
        while (!iss.eof()){
            iss >> buf;
            buf = wordCleaning(buf);
            if (std::count(uniqueWords.begin(), uniqueWords.end(), buf) == 0){
                uniqueWords.push_back(buf);
            }
        }
        for (const auto& j : uniqueWords) {
            for (size_t k = 0; k < converter.GetTextDocuments().size(); k++){
                if (freqDictionary.count(j) != 0) {
                    wordRelevance.insert(std::pair<std::string, Entry>(j, (Entry) {k, freqDictionary[j][k].count}));
                } else {
                    wordRelevance.insert(std::pair<std::string, Entry>(j, (Entry) {k, 0}));
                }
            }
        }
        for (size_t j = 0; j < converter.GetTextDocuments().size(); j++) {
            int currentAbsRelevence = 0;
            for (const auto& k : wordRelevance) {
                if (k.second.docId == j) {
                    currentAbsRelevence += (int)k.second.count;
                }
            }
            absoluteRelevance.push_back(currentAbsRelevence);
        }
        for (int j = 0; j < absoluteRelevance.size();j++) {
            relevantRelevance.push_back((RelativeIndex){(size_t)j,(float)absoluteRelevance[j]/ (float)*std::max_element(absoluteRelevance.begin(),absoluteRelevance.end())});
        }
        result.push_back(relevantRelevance);
    }
    return result;
};
