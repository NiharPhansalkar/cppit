#pragma once

#include <string>

class Blob {
public:
    Blob(const std::string& type, const std::string& content);

    std::string type() const;
    std::string content() const;
    std::string fullContent() const; // Git style header + content
private:
    std::string type_;
    std::string content_;
};