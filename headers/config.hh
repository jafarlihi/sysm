#ifndef SYSM_CONFIG_HH
#define SYSM_CONFIG_HH

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <SFML/Audio.hpp>

struct Rule {
  std::string name;
  bool enabled;
  std::string description;
  uint32_t sleep;
  std::string start_music_filename;
  sf::Music start_music;
  float start_music_volume = 100.f;
  std::string content_music_filename;
  sf::Music content_music;
  float content_music_volume = 100.f;
  std::string end_music_filename;
  sf::Music end_music;
  float end_music_volume = 100.f;
  std::string source;
  std::string type;
  std::map<std::string, std::string> settings;
};

struct Config {
  std::vector<Rule *> rules;
};

auto parse_config(std::string config_filename) -> Config;

#endif
