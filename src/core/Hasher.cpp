#include "core/Hasher.hpp"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

std::string Hasher::sha1_hex(const std::string& data) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(data.data()), data.size(), hash);

    std::ostringstream oss;
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int) hash[i];
    }

    return oss.str();
}