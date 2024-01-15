#include "InvertedIndex.h"

std::mutex freqAccess;

std::string wordCleaning(std::string word) {
    while ((word.back() >= ' ' and word.back() <= '/') or (word.back() >= ':' and word.back() <= '@')
           or (word.back() >= '[' and word.back() <= '\'') or (word.back() >= '{' and word.back() <= '~')){
        word.erase(word.end()-1);
    }
    while ((word.front() >= ' ' and word.front() <= '/') or (word.front() >= ':' and word.front() <= '@')
           or (word.front() >= '[' and word.front() <= '\'') or (word.front() >= '{' and word.front() <= '~')){
        word.erase(0,1);
    }
    return word;
}


void InvertedIndex::convertDocumentsIntoDatabase(const std::string& txt, size_t num) {
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

void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& doc) {
    docs = doc;
    std::vector<std::thread> threads = {};
    for (int i = 0; i < doc.size(); i++) {
        threads.emplace_back(&InvertedIndex::convertDocumentsIntoDatabase, this, docs[i], i);
    }
    for (int i = 0; i < doc.size(); i++) {
        threads[i].join();
    }
}


std::map<std::string, std::vector<Entry>> InvertedIndex::getFreqDictionary() {
    return freqDictionary;
}
