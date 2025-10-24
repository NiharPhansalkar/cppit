#include "core/ObjectStore.hpp"
#include "core/Hasher.hpp"
#include "core/Compressor.hpp"
#include <fstream>

ObjectStore::ObjectStore(const fs::path& path) : store_path_(path){}

std::string ObjectStore::store(const Blob& object) {
    std::string content = object.fullContent();
    std::string oid = Hasher::sha1_hex(content);

    std::string folder = oid.substr(0,2);
    std::string filename = oid.substr(2);

    fs::path objectDir = store_path_ / folder;
    fs::create_directories(objectDir);

    fs::path filePath = objectDir / filename;

    std::vector<unsigned char> compressed = Compressor::compress(content);

    std::ofstream file(filePath, std::ios::binary);
    if(!file.is_open()) {
        throw std::runtime_error("Failed to write object file");
    }

    file.write(reinterpret_cast<const char*>(compressed.data()), compressed.size());
    file.close();

    return oid;
}