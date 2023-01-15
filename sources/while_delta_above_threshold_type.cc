#include "while_delta_above_threshold_type.hh"
#include <thread>
#include <chrono>

auto WhileDeltaAboveThresholdType::run() -> void {
  this->get_rule()->content_music.setLoop(true);

  uint64_t past_sectors = std::stoul(this->get_source()->fetch());
  uint64_t current_sectors;
  bool active = false;

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(this->get_rule()->sleep));
    current_sectors = std::stoul(this->get_source()->fetch());

    bool above_threshold = current_sectors - past_sectors > std::stoul(this->get_rule()->settings.find("threshold")->second);
    if (above_threshold && !active) {
      active = true;
      this->get_rule()->content_music.stop();
      this->get_rule()->end_music.stop();
      this->get_rule()->start_music.play();
      this->get_rule()->content_music.play(); // TODO: Play only after start finishes
    } else if (!above_threshold && active) {
      active = false;
      this->get_rule()->content_music.stop();
      this->get_rule()->start_music.stop();
      this->get_rule()->end_music.play();
    }

    past_sectors = current_sectors;
  }
}
