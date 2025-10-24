#pragma once
#include <string>
#include <vector>

class Compressor {
public:
    static std::vector<unsigned char> compress(const std::string& data);
};