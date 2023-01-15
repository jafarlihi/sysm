#include "util.hh"
#include <sstream>
#include <algorithm>

auto replace_substring(std::string& str, const std::string& from, const std::string& to) -> void {
  size_t start_pos = str.find(from);
  if (start_pos == std::string::npos)
    return;
  str.replace(start_pos, from.length(), to);
}

auto string_to_bool(std::string str) -> bool {
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  std::istringstream is(str);
  bool b;
  is >> std::boolalpha >> b;
  return b;
}

auto string_to_uint32_t(const std::string& str) -> uint32_t {
  return static_cast<uint32_t>(std::stoul(str));
}

auto string_to_float(const std::string& str) -> float {
  return ::atof(str.c_str());
}

auto split_string_by_newline(const std::string& str) -> std::vector<std::string> {
  auto result = std::vector<std::string>{};
  auto ss = std::stringstream{str};
  for (std::string line; std::getline(ss, line, '\n');)
    result.push_back(line);
  return result;
}
