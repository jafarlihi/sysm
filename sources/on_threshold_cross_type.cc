#include "on_threshold_cross_type.hh"
#include <thread>
#include <chrono>
#include <regex>

auto OnThresholdCrossType::run() -> void {
  bool past_match = this->isAboveThreshold();
  bool current_match;

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(this->get_rule()->sleep));
    if (this->get_rule()->content_music.getStatus() == sf::SoundSource::Status::Stopped)
      this->get_rule()->content_music.stop();
    current_match = this->isAboveThreshold();
    if (!past_match && current_match)
      this->get_rule()->content_music.play();
    past_match = current_match;
  }
}

auto OnThresholdCrossType::isAboveThreshold() -> bool {
  auto content = this->get_source()->fetch();
  return std::stoi(content) > std::stoi(this->get_rule()->settings.find("threshold")->second);
}
