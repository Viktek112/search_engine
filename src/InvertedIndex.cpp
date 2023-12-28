#include "InvertedIndex.h"
#include "Structs.h"
#include <vector>
#include <map>
#include <sstream>
#include <thread>


std::string wordCleaning(std::string word) {
    while ((word.back() >= 32 and word.back() <= 47) or (word.back() >= 58 and word.back() <= 64)
           or (word.back() >= 91 and word.back() <= 96) or (word.back() >= 123 and word.back() <= 127)){
        word.erase(word.end()-1);
    }
    while ((word.front() >= 32 and word.front() <= 47) or (word.front() >= 58 and word.front() <= 64)
           or (word.front() >= 91 and word.front() <= 96) or (word.front() >= 123 and word.front() <= 127)){
        word.erase(0,1);
    }
    return word;
}

class InvertedIndex {
private:
    std::map<std::string, std::vector<Entry>> freqDictionary;
    std::vector<std::string> docs = {};

    void convertDocumentsIntoDatabase(const std::string& txt, size_t num) {
        std::map<std::string,size_t> words;
        std::istringstream iss(txt);
        std::string buf;
        while (!iss.eof()){
            iss >> buf;
            buf = wordCleaning(buf);
            if (words.count(buf) == 0){
                words.insert(std::pair<std::string,size_t>(buf,1));
            } else {
                words[buf] += 1;
            }
        }
        for (auto & word : words) {
            freqAccess.lock();
            if (freqDictionary.count(word.first) == 0) {
                std::pair <std::string,std::vector<Entry>> PaBuf(word.first,
                                                                 static_cast<const std::vector<Entry>>(std::vector{
                                                                         (Entry) {num, word.second}}));
                freqDictionary.insert(PaBuf);
            } else {
                freqDictionary[word.first].push_back((Entry){num,word.second});
            }
            freqAccess.unlock();
        }
    }

public:
    void UpdateDocumentBase(const std::vector<std::string>& doc) {
        docs = doc;
        std::vector<std::thread> threads = {};
        for (int i = 0; i < doc.size(); i++) {
            threads.emplace_back(&InvertedIndex::convertDocumentsIntoDatabase, this, docs[i], i);
        }
        for (int i = 0; i < doc.size(); i++) {
            threads[i].join();
        }
    }

    auto getFreqDictionary() {
        return freqDictionary;
    }
};