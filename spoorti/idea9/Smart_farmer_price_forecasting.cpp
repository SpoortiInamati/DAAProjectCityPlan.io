
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <cmath>
#include "json.hpp"

using json = nlohmann::json;

// --------------------- TRIE FOR CROP SEARCH -----------------------
struct TrieNode {
    bool end = false;
    std::unordered_map<char, TrieNode*> next;
};

class Trie {
public:
    TrieNode* root = new TrieNode();

    void insert(const std::string &word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!curr->next[c]) curr->next[c] = new TrieNode();
            curr = curr->next[c];
        }
        curr->end = true;
    }

    bool search(const std::string &word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!curr->next[c]) return false;
            curr = curr->next[c];
        }
        return curr->end;
    }
};

// ------------------ MERGE SORT FOR PRICE SORTING -------------------
void merge(std::vector<double>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    std::vector<double> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i=0, j=0, k=l;
    while (i<n1 && j<n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i<n1) arr[k++] = L[i++];
    while (j<n2) arr[k++] = R[j++];
}

void mergeSort(std::vector<double>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m+1, r);
    merge(arr, l, m, r);
}

// ------------------ FENWICK TREE FOR PRICE ANALYTICS ---------------
class Fenwick {
public:
    std::vector<double> tree;
    int n;

    Fenwick(int size) : n(size), tree(size+1, 0) {}

    void update(int i, double val) {
        while (i <= n) {
            tree[i] += val;
            i += (i & -i);
        }
    }

    double sum(int i) {
        double s = 0;
        while (i > 0) {
            s += tree[i];
            i -= (i & -i);
        }
        return s;
    }
};

// ------------------ LINEAR REGRESSION FOR PRICE TREND --------------
double linearRegression(const std::vector<double>& x, const std::vector<double>& y) {
    double n = x.size();
    double sumX = 0, sumY = 0, sumXY = 0, sumXX = 0;

    for(int i=0;i<n;i++){
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i]*y[i];
        sumXX += x[i]*x[i];
    }

    double slope = (n*sumXY - sumX*sumY) / (n*sumXX - sumX*sumX);
    return slope;
}

// ---------------------- MAIN PROGRAM -------------------------------
int main() {
    std::ifstream file("farmers_price.json");
    if (!file.is_open()) {
        std::cout << "Error: JSON file not found.\n";
        return 1;
    }

    json data;
    file >> data;

    std::cout << "Smart Farmers Price Formatting System Loaded Successfully!\n";

    // Example: Load crops into Trie
    Trie cropTrie;
    for (auto &crop : data["crops"]) {
        cropTrie.insert(crop.get<std::string>());
    }

    std::cout << "Enter crop name to search: ";
    std::string query;
    std::cin >> query;

    if (cropTrie.search(query)) {
        std::cout << "Crop exists in database.\n";
    } else {
        std::cout << "Crop NOT found.\n";
    }

    return 0;
}
