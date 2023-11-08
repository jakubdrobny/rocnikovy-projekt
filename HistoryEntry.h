#ifndef HistoryEntry_H
#define HistoryEntry_H

#include <vector>

class HistoryEntry {
    public:
        int from;
        std::vector<int> to;
        
        HistoryEntry() {}
        HistoryEntry(int from): from(from) {}
        HistoryEntry(int from, std::vector<int> to): from(from), to(to) {}

        void add(int newTo);
};

#endif