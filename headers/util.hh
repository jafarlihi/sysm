#ifndef SYSM_UTIL_HH
#define SYSM_UTIL_HH

#include <string>
#include <vector>

auto replace_substring(std::string& str, const std::string& from, const std::string& to) -> void;
auto string_to_bool(std::string str) -> bool;
auto string_to_uint32_t(const std::string& str) -> uint32_t;
auto string_to_float(const std::string& str) -> float;
auto split_string_by_newline(const std::string& str) -> std::vector<std::string>;

#endif
