#pragma once
#include "CommandRegistry.hpp"

// Helper for auto-registering commands
class CommandRegistrar {
public:
    CommandRegistrar(const std::string& name, CommandRegistry::FactoryFunction factory) {
        CommandRegistry::instance().registerCommand(name, std::move(factory));
    }
};
