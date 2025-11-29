
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main() {
    std::ifstream f("waste_data.json");
    if(!f.is_open()) {
        std::cerr << "Failed to open waste_data.json\n";
        return 1;
    }

    json data;
    f >> data;

    // Access data at runtime
    std::cout << "Smart Waste Sorting & Recycling System\n";
    std::cout << "Loaded waste samples: " << data["samples"].size() << "\n";

    // TODO: implement classification, sorting, robotic arm control, optimization

    return 0;
}
