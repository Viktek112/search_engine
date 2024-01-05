#pragma once
#include <mutex>
#include <iostream>

class InvertedIndex;

std::mutex freqAccess;

std::string wordCleaning(std::string word);