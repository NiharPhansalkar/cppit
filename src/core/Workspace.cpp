#include "core/Workspace.hpp"

const std::unordered_set<fs::path> Workspace::IGNORE = {".", "..", ".git"};

Workspace::Workspace(const fs::path& root) : rootPath(root) {}

std::vector<fs::path> Workspace::listFiles() const {
    std::vector<fs::path> files;

    for (const auto& file : fs::directory_iterator(rootPath)) {
        std::string name = file.path().filename().string();

        if (IGNORE.find(name) == IGNORE.end()) {
            files.emplace_back(file.path());
        }
    }
}

FileObject Workspace::openFile(const fs::path& absolutePath) const {
    return FileObject(absolutePath);
}