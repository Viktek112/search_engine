#include "Structs.h"


struct Entry {
    size_t docId, count;
};

struct RelativeIndex{
    size_t docId;
    float rank;
    bool operator == (const RelativeIndex& other) const {
        return (docId == other.docId && rank == other.rank);
    }
};