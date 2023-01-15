#include "config.hh"
#include "source.hh"
#include "type.hh"
#include "shell_source.hh"
#include "file_column_source.hh"
#include "on_match_when_past_not_match_type.hh"
#include "on_threshold_cross_type.hh"
#include "while_delta_above_threshold_type.hh"
#include <memory>
#include <map>
#include <string>
#include <thread>
#include <functional>

std::map<std::string, std::function<Source *(Rule *)>> sources;
std::map<std::string, std::function<Type *(Rule *, Source *)>> types;

auto main(int argc, char *argv[]) -> int {
  Config config = parse_config(std::string(getenv("HOME")) + "/.config/sysm/config.ini");

  sources.insert(
    std::pair(
      "shell",
      [](const Rule *rule) -> Source* {
        return new ShellSource(rule);
      }
    )
  );
  sources.insert(
    std::pair(
      "file_column",
      [](const Rule *rule) -> Source* {
        return new FileColumnSource(rule);
      }
    )
  );
  types.insert(
    std::pair(
      "on_match_when_past_not_match",
      [](Rule *rule, Source *source) -> Type* {
        return new OnMatchWhenPastNotMatchType(rule, source);
      }
    )
  );
  types.insert(
    std::pair(
      "on_threshold_cross",
      [](Rule *rule, Source *source) -> Type* {
        return new OnThresholdCrossType(rule, source);
      }
    )
  );
  types.insert(
    std::pair(
      "while_delta_above_threshold",
      [](Rule *rule, Source *source) -> Type* {
        return new WhileDeltaAboveThresholdType(rule, source);
      }
    )
  );

  std::vector<std::thread> threads;
  for (Rule *rule : config.rules) {
    if (rule->enabled) {
      auto source = sources.find(rule->source)->second(rule);
      auto type = types.find(rule->type)->second(rule, source);
      auto thread = std::thread([type = std::move(type)]{ type->run(); });
      threads.push_back(std::move(thread));
    }
  }
  for (auto &thread : threads)
    thread.join();

  return 0;
}
