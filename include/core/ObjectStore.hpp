#pragma once

#include "Blob.hpp"
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class ObjectStore {
public:
    ObjectStore(const fs::path& path);

    // Store a Blob and return its SHA-1 OID
    std::string store(const Blob& object);

private:
    fs::path store_path_;
};
