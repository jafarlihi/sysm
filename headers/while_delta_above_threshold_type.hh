#ifndef SYSM_WHILE_DELTA_ABOVE_THRESHOLD_TYPE_HH
#define SYSM_WHILE_DELTA_ABOVE_THRESHOLD_TYPE_HH

#include "type.hh"

class WhileDeltaAboveThresholdType : public Type {
  public:
    using Type::Type;
    auto run() -> void override;
};

#endif
