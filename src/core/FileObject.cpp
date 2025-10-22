#include "core/FileObject.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

FileObject::FileObject(fs::path path) : filePath(path) {}

std::string FileObject::read() const {
    std::ifstream in(filePath, std::ios::binary);

    if (!in) {
        throw std::runtime_error("Cannot open file for reading: " + filePath.string());
    }

    std::ostringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

void FileObject::write(const std::string& data) const {
    std::ofstream out(filePath, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Cannot open file for writing: " + filePath.string());
    }

    out << data;
}

const fs::path& FileObject::path() const noexcept {
    return filePath;
}