#ifndef History_H
#define History_H

#include "HistoryEntry.h"

#include <vector>

class History {
    public:
        int len = 0;
        std::vector<HistoryEntry> entries;

        void addEntry(HistoryEntry entry);
};

#endif