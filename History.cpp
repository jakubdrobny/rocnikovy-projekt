#include "HistoryEntry.h"
#include "History.h"

void History::addEntry(HistoryEntry entry) {
    this->entries.push_back(entry);
    this->len++;
}