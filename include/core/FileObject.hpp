#pragma once

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class FileObject {
public:
    explicit FileObject(fs::path path);

    std::string read() const;

    void write(const std::string& data) const;

    const fs::path& path() const noexcept;

private:
    fs::path filePath;
};