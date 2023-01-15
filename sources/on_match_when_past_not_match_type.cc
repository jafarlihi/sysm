#include "on_match_when_past_not_match_type.hh"
#include <thread>
#include <chrono>
#include <regex>

auto OnMatchWhenPastNotMatchType::run() -> void {
  bool past_match = this->isMatch();
  bool current_match;

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(this->get_rule()->sleep));
    if (this->get_rule()->content_music.getStatus() == sf::SoundSource::Status::Stopped)
      this->get_rule()->content_music.stop();
    current_match = this->isMatch();
    if (!past_match && current_match)
      this->get_rule()->content_music.play();
    past_match = current_match;
  }
}

auto OnMatchWhenPastNotMatchType::isMatch() -> bool {
  auto content = this->get_source()->fetch();
  return std::regex_search(content, std::regex{this->get_rule()->settings.find("match")->second});
}
