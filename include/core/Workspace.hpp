#pragma once

#include <string>
#include <vector>
#include <filesystem>

class Workspace {
public:
    explicit Workspace(const std::filesystem::path& root);
    std::vector<std::filesystem::path> listFiles() const;

private:
    std::filesystem::path rootPath;
    static const std::vector<std::string> IGNORE;
};