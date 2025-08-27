#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <filesystem>
#include <functional>
#include <optional>

// -------------------- CONTEXT --------------------
class AppContext {
public:
    void addArgument(std::string arg) {
        arguments.emplace_back(std::move(arg));
    }

    const std::string& fetchArgument(std::size_t index) const {
        return arguments.at(index); // throws if out-of-range
    }

    std::optional<std::string> getOptionalArgument(std::size_t index) const noexcept {
        if (index < arguments.size()) {
            return arguments[index];
        }
        return std::nullopt;
    }

    const std::vector<std::string>& getArguments() const noexcept {
        return arguments;
    }

private:
    std::vector<std::string> arguments;
};

// -------------------- COMMAND REGISTRY --------------------
class CommandRegistry {
public:
    using CommandHandler = std::function<void(const AppContext&)>;

    void registerCommand(const std::string& name, CommandHandler handler) {
        handlers[name] = std::move(handler);
    }

    bool execute(const std::string& name, const AppContext& ctx) const {
        auto it = handlers.find(name);
        if (it != handlers.end()) {
            it->second(ctx);
            return true;
        }
        return false;
    }

private:
    std::unordered_map<std::string, CommandHandler> handlers;
};

// -------------------- COMMAND HANDLERS --------------------
void handleInit(const AppContext& ctx) {
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

// -------------------- MAIN --------------------
int main(int argc, char* argv[]) {
    try {
        AppContext ctx;

        for (int i = 1; i < argc; i++) {
            ctx.addArgument(argv[i]);
        }

        if (ctx.getArguments().empty()) {
            std::cerr << "Usage: cppit <command> [args...]\n";
            return EXIT_FAILURE;
        }

        const std::string& commandString = ctx.fetchArgument(0);

        // Setup registry
        CommandRegistry registry;
        registry.registerCommand("init", handleInit);

        if (!registry.execute(commandString, ctx)) {
            std::cerr << "Unknown command: " << commandString << "\n";
            std::cerr << "Usage: cppit <command> [args...]\n";
            return EXIT_FAILURE;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
