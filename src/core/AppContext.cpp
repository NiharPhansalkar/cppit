#include <string>
#include <vector>
#include <optional>
#include "core/AppContext.hpp"

void AppContext::addArgument(std::string arg) {
    arguments.emplace_back(std::move(arg));
}

std::optional<std::string> AppContext::getOptionalArgument(const std::size_t& index) const noexcept {
    if (index < arguments.size()) {
        return arguments[index];
    }
    return std::nullopt;
}

const std::string& AppContext::fetchArgument(const std::size_t& index) const {
    return arguments.at(index);
}

const std::vector<std::string>& AppContext::getArguments() const noexcept {
    return arguments;
}