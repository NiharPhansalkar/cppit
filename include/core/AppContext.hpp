#pragma once
#include <string>
#include <vector>
#include <optional>

class AppContext {
public:
    void addArgument(std::string arg);
    std::optional<std::string> getOptionalArgument(const std::size_t& index) const noexcept;
    const std::string& fetchArgument(const std::size_t& index) const;
    const std::vector<std::string>& getArguments() const noexcept;
private:
    std::vector<std::string> arguments;
};