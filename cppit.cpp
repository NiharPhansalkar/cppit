#include "core/AppContext.hpp"
#include "core/CommandRegistry.hpp"
#include "commands/InitCommand.hpp"
#include <iostream>

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

        // Factory-driven command execution
        std::unique_ptr<Command> command = CommandRegistry::instance().create(commandString);
        command->execute(ctx);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}