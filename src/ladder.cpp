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

bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (abs(static_cast<int>(str1.size()) - static_cast<int>(str2.size())) > d)
        return false;
    
    int count = 0;
    for (size_t i = 0; i < min(str1.size(), str2.size()); ++i) {
        if (str1[i] != str2[i]) {
            if (++count > d) return false;
        }
    }
    count += abs(static_cast<int>(str1.size()) - static_cast<int>(str2.size()));

    return count <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word) return {};
    set<string> local_set = word_list;
    queue<vector<string>> queue_path;
    queue_path.push({begin_word});
    local_set.erase(begin_word);
    while (!queue_path.empty()){
        vector<string> word_ladder = queue_path.front();
        queue_path.pop();
        string cur_word = word_ladder.back();
        if (cur_word == end_word) return word_ladder;
        for (auto word = local_set.begin(); word != local_set.end();) {
            if (is_adjacent(cur_word, *word)){
                vector<string> updated_ladder = word_ladder;
                updated_ladder.push_back(*word);
                queue_path.push(updated_ladder);
                word = local_set.erase(word);
            } else {++word;}
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