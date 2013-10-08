#include "utils.h"

std::vector<std::string> split(const std::string &s, char delim, bool include_empty_tokens) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)) {
        if (include_empty_tokens || !item.empty()) {
            elems.push_back(item);
        }
    }

    return elems;
}

