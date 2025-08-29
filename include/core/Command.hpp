#pragma once
#include "AppContext.hpp"

// Command interface
class Command {
public:
    virtual ~Command() = default;
    virtual void execute(const AppContext& ctx) = 0;
};