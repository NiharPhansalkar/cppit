#pragma once
#include "Command.hpp"
#include <functional>
#include <map>
#include <memory>
#include <string>

class CommandRegistry {
public:
    using FactoryFunction = std::function<std::unique_ptr<Command>()>;

    static CommandRegistry& instance();

    void registerCommand(const std::string& name, FactoryFunction factory);
    std::unique_ptr<Command> create(const std::string& name) const;
private:
    std::map<std::string, FactoryFunction> registry_;
};