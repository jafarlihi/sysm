#ifndef SYSM_TYPE_HH
#define SYSM_TYPE_HH

#include "config.hh"
#include "source.hh"

class Type {
  public:
    explicit Type(Rule *r, Source *s) : rule{r}, source{s} {};
    virtual auto run() -> void {};
    auto get_rule() -> Rule* { return this->rule; };
    auto get_source() -> Source* { return this->source; };
  private:
    Rule *rule;
    Source *source;
};

#endif
