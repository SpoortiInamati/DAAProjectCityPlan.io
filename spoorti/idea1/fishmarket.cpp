
#include <bits/stdc++.h>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

// Dynamic Smart Fish Market Auction Platform (Data Loaded from JSON)

struct Fish {
    string id;
    string name;
    double weight;
    double basePrice;
};

int main() {
    string file;
    cout << "Enter JSON file name: ";
    cin >> file;

    ifstream f(file);
    if (!f.is_open()) {
        cerr << "Error: Cannot open JSON file.\n";
        return 1;
    }

    json data;
    f >> data;

    // Authentication hash
    unordered_map<string, string> userHash;
    for (auto &u : data["users"])
        userHash[u["username"]] = u["hash"];

    // Fish listings stored in AVL-like sorted structure → std::map
    map<string, Fish> fishListings;
    for (auto &fsh : data["fish_listings"]) {
        Fish fobj;
        fobj.id = fsh["id"];
        fobj.name = fsh["name"];
        fobj.weight = fsh["weight"];
        fobj.basePrice = fsh["basePrice"];
        fishListings[fobj.id] = fobj;
    }

    // Max-heap for bidding
    priority_queue<pair<double,string>> bids; // (amount, buyer)

    for (auto &b : data["bids"]) {
        bids.push({b["amount"], b["buyer"]});
    }

    // Winner extraction
    if (!bids.empty()) {
        auto best = bids.top();
        cout << "\nHighest Bid: " << best.first 
             << " by " << best.second << "\n";
    } else {
        cout << "No bids available.\n";
    }

    // Delivery routing (placeholder)
    cout << "\nDelivery routing graph loaded with "
         << data["graph"]["edges"].size() << " edges.\n";

    return 0;
}
