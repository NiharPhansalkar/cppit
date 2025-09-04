#include "core/Command.hpp"
#include "core/CommandRegistrar.hpp"
#include "commands/CommitCommand.hpp";
#include <filesystem>
#include <iostream>

void CommitCommand::execute(const AppContext& ctx) {
    namespace fs = std::filesystem;
    try {
        fs::path rootPath = fs::absolute(fs::current_path());
        fs::path gitPath = rootPath / ".git";
        fs::path dbPath = rootPath /"objects";
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error resolving path: " << e.what() << std::endl;
    }
}