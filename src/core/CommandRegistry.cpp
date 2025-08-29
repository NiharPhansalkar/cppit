#include "core/CommandRegistry.hpp"
#include <stdexcept>

CommandRegistry& CommandRegistry::instance() {
    static CommandRegistry inst;
    return inst;
}

void CommandRegistry::registerCommand(const std::string& name, FactoryFunction factory) {
    registry_[name] = std::move(factory);
}

std::unique_ptr<Command> CommandRegistry::create(const std::string& name) const {
    auto command = registry_.find(name);
    if (command == registry_.end()) {
        throw std::runtime_error("Unknown command: " + name);
    }
    return command->second();
}