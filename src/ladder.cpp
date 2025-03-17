#include "ladder.h"  // Replace with the actual header file name
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

bool edit_distance_within(const std::string& word1, const std::string& word2, int threshold) {
    int len1 = word1.size();
    int len2 = word2.size();
    // If len diff > 1, the distance not within threshold
    if (abs(len1 - len2) > 1) return false;
    // Both words have the same len 
    if (len1 == len2) {
        int mismatch_count = 0;
        for (size_t index = 0; index < len1; ++index) {
            if (word1[index] != word2[index]) {
                if (++mismatch_count > threshold) return false;
            }
        }
        return true;
    }
    // Differ in len by 1
    const std::string& smaller = (len1 < len2) ? word1 : word2;
    const std::string& larger = (len1 < len2) ? word2 : word1;

    int pos1 = 0, pos2 = 0;
    bool discrepancy_found = false;
    while (pos1 < smaller.size() && pos2 < larger.size()) {
        if (smaller[pos1] != larger[pos2]) {
            if (discrepancy_found) return false; 
            discrepancy_found = true;
            ++pos2;
        } else {
            ++pos1;
            ++pos2;
        }
    }
    return true;
}

bool is_adjacent(const std::string& word1, const std::string& word2) {
    if (word1.size() != word2.size()) { 
        return edit_distance_within(word1, word2, 1); 
    }

    int difference_count = 0;

    for (size_t index = 0; index < word1.size(); ++index) {
        if (word1[index] != word2[index]) { 
            ++difference_count;
            if (difference_count > 1) { 
                return false; 
            }
        }
    }

    return (difference_count == 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {};

    std::set<std::string> remaining_words = word_list;
    std::queue<std::vector<std::string>> paths_queue;
    
    paths_queue.push({begin_word});
    remaining_words.erase(begin_word);

    while (!paths_queue.empty()) {
        std::vector<std::string> current_sequence = paths_queue.front();
        paths_queue.pop();
        
        std::string last_word = current_sequence.back();
        
        if (last_word == end_word) return current_sequence;

        for (auto it = remaining_words.begin(); it != remaining_words.end();) {
            if (is_adjacent(last_word, *it)) {
                std::vector<std::string> new_sequence = current_sequence;
                new_sequence.push_back(*it);
                paths_queue.push(new_sequence);
                it = remaining_words.erase(it); 
            } else {
                ++it;
            }
        }
    }

    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Unable to open file " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    for (const string& word : ladder) {
        cout << word << " -> ";
    }
    cout << "END" << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
    

}