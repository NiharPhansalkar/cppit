#include "core/Command.hpp"
#include "core/CommandRegistrar.hpp"
#include "commands/CommitCommand.hpp"
#include "core/Workspace.hpp"
#include <filesystem>
#include <iostream>

void CommitCommand::execute(const AppContext& ctx) {
    namespace fs = std::filesystem;
    try {
        fs::path rootPath = fs::absolute(fs::current_path());
        fs::path gitPath = rootPath / ".git";
        fs::path dbPath = rootPath /"objects";

        Workspace ws = Workspace(rootPath);
        /*
            Database db = Database(dbPath)
            ws
        */
        for (const auto& file : ws.listFiles()) {
            FileObject fileContent = ws.openFile(file);
            std::string data = fileContent.read();

            /*
                Blob = Blob(data)
                db.store(blob)
            */
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error resolving path: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "File read runtime error: " << e.what() << std::endl;
    }
}

CommandRegistrar CommitCommand::registrar("commit", [] {
    return std::make_unique<CommitCommand>();
});