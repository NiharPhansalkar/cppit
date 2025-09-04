#pragma once

#include "core/Command.hpp";
#include "core/CommandRegistrar.hpp";

class CommitCommand : public Command {
public:
    void execute(const AppContext& ctx) override;
private:
    static CommandRegistrar registrar;
};