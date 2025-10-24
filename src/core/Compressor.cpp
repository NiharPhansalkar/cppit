#include "core/Compressor.hpp"
#include <zlib.h>
#include <stdexcept>

std::vector<unsigned char> Compressor::compress(const std::string& data) {
    uLong src_len = data.size();
    uLong dest_len = compressBound(src_len);
    std::vector<unsigned char> dest(dest_len);

    if (compress2(dest.data(), &dest_len,
                  reinterpret_cast<const unsigned char*>(data.data()),
                  src_len, Z_BEST_SPEED) != Z_OK) {
        throw std::runtime_error("Compression failed");
    }

    dest.resize(dest_len);
    return dest;
}