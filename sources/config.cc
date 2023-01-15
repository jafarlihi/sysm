#include "config.hh"
#include "util.hh"
#include <fstream>
#include <sstream>

auto get_line_key(const std::string& str) -> std::string {
  return str.substr(0, str.find(" "));
}

auto get_line_value(const std::string& str) -> std::string {
  std::string result = str.substr(str.find("=") + 2, str.length());
  if (result[0] == '"' && result[result.length() - 1] == '"')
    result = result.substr(1, result.size() - 2);
  return result;
}

auto load_music(Config config) -> void {
  for (Rule *rule : config.rules) {
    if (rule->start_music_filename.length()) {
      replace_substring(rule->start_music_filename, "~", getenv("HOME"));
      rule->start_music.openFromFile(rule->start_music_filename);
      rule->start_music.setVolume(rule->start_music_volume);
    }
    if (rule->content_music_filename.length()) {
      replace_substring(rule->content_music_filename, "~", getenv("HOME"));
      rule->content_music.openFromFile(rule->content_music_filename);
      rule->content_music.setVolume(rule->content_music_volume);
    }
    if (rule->end_music_filename.length()) {
      replace_substring(rule->end_music_filename, "~", getenv("HOME"));
      rule->end_music.openFromFile(rule->end_music_filename);
      rule->end_music.setVolume(rule->end_music_volume);
    }
  }
}

auto parse_config(std::string config_filename) -> Config {
  Config config = Config{};

  std::ifstream f(config_filename);
  std::stringstream configRaw;
  configRaw << f.rdbuf();

  auto lines = split_string_by_newline(configRaw.str());

  Rule *rule;
  bool is_first_rule = true;
  for (auto line : lines) {
    if (line[0] == '[') {
      if (!is_first_rule)
        config.rules.push_back(rule);
      is_first_rule = false;
      rule = new Rule();
      rule->name = line.substr(1, line.size() - 2);
      continue;
    }
    if ("enabled" == get_line_key(line))
      rule->enabled = string_to_bool(get_line_value(line));
    else if ("description" == get_line_key(line))
      rule->description = get_line_value(line);
    else if ("sleep" == get_line_key(line))
      rule->sleep = string_to_uint32_t(get_line_value(line));
    else if ("start_music" == get_line_key(line))
      rule->start_music_filename = get_line_value(line);
    else if ("start_music_volume" == get_line_key(line))
      rule->start_music_volume = string_to_float(get_line_value(line));
    else if ("content_music" == get_line_key(line))
      rule->content_music_filename = get_line_value(line);
    else if ("content_music_volume" == get_line_key(line))
      rule->content_music_volume = string_to_float(get_line_value(line));
    else if ("end_music" == get_line_key(line))
      rule->end_music_filename = get_line_value(line);
    else if ("end_music_volume" == get_line_key(line))
      rule->end_music_volume = string_to_float(get_line_value(line));
    else if ("source" == get_line_key(line))
      rule->source = get_line_value(line);
    else if ("type" == get_line_key(line))
      rule->type = get_line_value(line);
    else if (!std::all_of(line.begin(), line.end(), isspace))
      rule->settings.insert(std::pair(get_line_key(line), get_line_value(line)));
  }
  config.rules.push_back(rule);

  load_music(config);

  return config;
};
