#include "shell_source.hh"
#include <array>

auto ShellSource::fetch() -> std::string {
  std::array<char, 8192> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(this->get_rule()->settings.find("command")->second.c_str(), "r"), pclose);
  if (!pipe)
    throw std::runtime_error("popen failed"); // TODO: Handle error better
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    result += buffer.data();
  return result;
}
