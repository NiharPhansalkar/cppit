#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <filesystem>

namespace fs = std::filesystem;

class Workspace {
public:
    explicit Workspace(const fs::path& root);
    std::vector<fs::path> listFiles() const;

private:
    fs::path rootPath;
    static const std::unordered_set<fs::path> IGNORE;
};