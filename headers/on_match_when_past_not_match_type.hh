#ifndef SYSM_ON_MATCH_WHEN_PAST_NOT_MATCH_TYPE_HH
#define SYSM_ON_MATCH_WHEN_PAST_NOT_MATCH_TYPE_HH

#include "type.hh"

class OnMatchWhenPastNotMatchType : public Type {
  public:
    using Type::Type;
    auto run() -> void override;
  private:
    auto isMatch() -> bool;
};

#endif
