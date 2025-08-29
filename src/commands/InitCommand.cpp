#include "core/Command.hpp"
#include "core/CommandRegistrar.hpp"
#include "commands/InitCommand.hpp"
#include <filesystem>
#include <iostream>


void InitCommand::execute(const AppContext& ctx) {
    try {
        std::filesystem::path targetPath = std::filesystem::absolute(ctx.getOptionalArgument(1).value_or("."));
        const std::filesystem::path gitDir = targetPath / ".git";
    
        // Define repository structure
        const std::vector<std::filesystem::path> repoStructure = {
            gitDir,
            gitDir / "objects",
            gitDir / "refs"
        };
    
        for (const auto& dir : repoStructure) {
            std::filesystem::create_directories(dir);
        }
    
        std::cout << "Initialized empty cppit repository in "
                  << std::filesystem::canonical(gitDir) << "\n";
    } catch(const std::filesystem::filesystem_error& e) {
        std::cerr << "Error resolving path: " << e.what() << std::endl;
    }
}

// static auto-registration
CommandRegistrar InitCommand::registrar("init", [] {
    return std::make_unique<InitCommand>();
});