//
// Created by Poyraz Güler on 21.12.2023.
//

#ifndef HW3_HASHTABLE_H
#define HW3_HASHTABLE_H
#include "WordItem.h"
#include <iostream>
#include <vector>
#include <list>
#include <cmath>

class HashTable {
private:
    static const std::size_t initialCapacity;
    static const double loadFactorThreshold;

    std::vector<std::list<WordItem *>> table;
    std::size_t itemCount;

    std::size_t hash(const std::string &key) const {
        std::size_t hashValue = 0;
        const std::size_t prime = 31;  // A prime number for better distribution

        for (char c : key) {
            hashValue = hashValue * prime + c;
        }

        // Consider the occurrence of 'a' characters in the hash
        std::size_t aCount = std::count(key.begin(), key.end(), 'a');
        std::size_t bCount = std::count(key.begin(), key.end(), 'b');
        hashValue = hashValue * prime + aCount +bCount;

        return hashValue % table.size();
    }

    void rehash() {
        std::size_t previousCapacity = table.size();
        std::size_t newCapacity = std::max(initialCapacity, previousCapacity * 2);
        std::vector<std::list<WordItem *>> newTable(newCapacity);

        for (const auto &bucket: table) {
            for (WordItem *wordItem: bucket) {
                std::size_t newIndex = hash(wordItem->word);
                newTable[newIndex].push_back(wordItem);
            }
        }

        double previousLoad = static_cast<double>(itemCount) / previousCapacity;
        double currentLoad = static_cast<double>(itemCount) / newCapacity;

        std::cout << "Rehashed..." << std::endl
                  << "Previous table size: " << previousCapacity
                  << ", new table size: " << newCapacity << ", current unique word count "
                  << static_cast<double>(itemCount) << "," << std::endl
                  << "current load=" << currentLoad << std::endl;

        table = std::move(newTable);
    }

public:
    HashTable() : table(initialCapacity), itemCount(0) {}

    ~HashTable() {
        for (auto &bucket: table) {
            for (WordItem *wordItem: bucket) {
                delete wordItem;
            }
        }
    }

    void insert(WordItem *wordItem) {
        if (itemCount >= loadFactorThreshold * table.size()) {
            rehash();
        }

        std::size_t index = hash(wordItem->word);
        table[index].push_back(wordItem);
        ++itemCount;
    }

    WordItem* get(const std::string& word) const {
        std::size_t index = hash(word);

        // Iterate through all possible locations where the word could be
        for (std::size_t i = 0; i < table.size(); ++i) {
            std::size_t newIndex = (index + i) % table.size();

            for (WordItem* wordItem : table[newIndex]) {
                if (wordItem->word == word) {
                    return wordItem; // Word found
                }
            }
        }

        return nullptr; // Word not found
    }

    void final() {
        std::cout << "After preprocessing, the unique word count is " << static_cast<double>(itemCount)
                  << ". Current load ratio is\n"
                  << static_cast<double>(itemCount) / double(table.size()) << std::endl;
    }
};
#endif // HW3_HASHTABLE_H


