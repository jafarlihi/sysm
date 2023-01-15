#ifndef SYSM_ON_THRESHOLD_CROSS_TYPE_HH
#define SYSM_ON_THRESHOLD_CROSS_TYPE_HH

#include "type.hh"

class OnThresholdCrossType : public Type {
  public:
    using Type::Type;
    auto run() -> void override;
  private:
    auto isAboveThreshold() -> bool;
};

#endif
