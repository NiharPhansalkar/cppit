#include "commands/CommitCommand.hpp"

#include "core/Workspace.hpp"
#include "core/ObjectStore.hpp"
#include "core/Blob.hpp"
#include "core/FileObject.hpp"

#include <filesystem>
#include <iostream>
#include <system_error>

namespace fs = std::filesystem;

void CommitCommand::execute(const AppContext& /*ctx*/) {
    try {
        fs::path rootPath = fs::absolute(fs::current_path());
        fs::path gitPath = rootPath / ".git";
        fs::path objectsPath = gitPath / "objects";

        // Ensure .git/objects exists
        std::error_code ec;
        if (!fs::exists(objectsPath)) {
            fs::create_directories(objectsPath, ec);
            if (ec) {
                std::cerr << "Failed to create objects directory: " << ec.message() << "\n";
                return;
            }
        }

        Workspace workspace(rootPath);
        ObjectStore store(objectsPath);

        for (const auto& filePath : workspace.listFiles()) {
            // Skip anything inside the .git directory
            if (filePath.string().rfind(gitPath.string(), 0) == 0) {
                continue;
            }

            FileObject fileObj(filePath);
            std::string data = fileObj.read(); // assume binary-safe read

            // Construct blob and let ObjectStore handle hashing/compression/storage
            Blob blob("blob", data);
            std::string oid = store.store(blob);

            std::cout << "Committed blob: " << oid << "  " << filePath.string() << "\n";
        }

    } catch (const std::exception& ex) {
        std::cerr << "Commit failed: " << ex.what() << std::endl;
    }
}

// Command registration
CommandRegistrar CommitCommand::registrar("commit", [] {
    return std::make_unique<CommitCommand>();
});
