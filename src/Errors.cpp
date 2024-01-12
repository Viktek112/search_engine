#include "Errors.h"

OpeningError::OpeningError(const std::string& fileName): message{ "Failed to open file: " + fileName + "."} {};

JsonFileContainingError::JsonFileContainingError(const std::string& fileName, const std::string& containerName): message{"Failed to find container "+containerName+" in file "+fileName+"."} {};