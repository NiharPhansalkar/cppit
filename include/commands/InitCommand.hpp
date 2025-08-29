#pragma once

#include "core/Command.hpp"
#include "core/CommandRegistrar.hpp"

class InitCommand : public Command {
public:
    void execute(const AppContext& ctx) override;
private:
    static CommandRegistrar registrar;
};