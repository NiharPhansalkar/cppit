#pragma once

#include <string>

class Hasher {
public:
    static std::string sha1_hex(const std::string& data);
};