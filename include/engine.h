#pragma once
#include <iostream>
#include <mutex>

std::string wordCleaning(std::string word);

struct Entry;

struct RelativeIndex;

class OpeningError;

class JsonFileContainingError;

class ConverterJSON;

std::mutex freqAccess;

class InvertedIndex;

class SearchServer;

