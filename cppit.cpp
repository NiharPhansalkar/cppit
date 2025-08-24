#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>

enum Command {
    INIT,
    NULL_COMMAND
};

class AppContext {
public:
    AppContext() {
        initializeCommandMap();
    }

    void addArgument(std::string arg) {
        arguments.emplace_back(std::move(arg));
    }

    const std::string& fetchArgument(std::size_t index) const {
        return arguments.at(index);
    }

    const Command getCommand(const std::string& command) const noexcept {
        auto mapIterator = commandMap.find(command);
        return (mapIterator != commandMap.end()) ? mapIterator->second : Command::NULL_COMMAND;
    }

    const std::vector<std::string>& getArguments() const noexcept {
        return arguments;
    }

private:
    std::vector<std::string> arguments;
    std::unordered_map<std::string, Command> commandMap;

    void initializeCommandMap() {
        commandMap.emplace("init", Command::INIT);
    }
};

void handleInit(std::string path) {
    // TODO
}

int main(int argc, char* argv[]) {
    try
    {
        AppContext ctx;

        for (int i = 1; i < argc; i++) {
            ctx.addArgument(argv[i]);
        }

        if (ctx.getArguments().empty()) {
            std::cerr << "Usage: cppit <command> [args...]\n";
            return EXIT_FAILURE;
        }

        const std::string& commandString = ctx.fetchArgument(0);
        Command cmd = ctx.getCommand(commandString);

        switch (cmd)
        {
            case Command::INIT: {
                std::string path;
                if (ctx.getArguments().size() > 1) {
                    path = ctx.fetchArgument(1);
                } else {
                    path = "."; // default to current directory
                }
                handleInit(path);
                break;
            }
            default:
                std::cerr << "Usage: cppit init [path]\n";
                return EXIT_FAILURE;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}