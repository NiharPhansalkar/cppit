#include "core/Blob.hpp"

Blob::Blob(const std::string& type, const std::string& content)
    : type_(type), content_(content) {}

std::string Blob::type() const {
    return type_;
}

std::string Blob::content() const {
    return content_;
}

std::string Blob::fullContent() const {
    return type_ + " " + std::to_string(content_.size()) + '\0' + content_;
}