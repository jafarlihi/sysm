#ifndef SYSM_SOURCE_HH
#define SYSM_SOURCE_HH

#include "config.hh"

class Source {
  public:
    explicit Source(const Rule *r) : rule{r} {};
    virtual auto fetch() -> std::string { return nullptr; };
    auto get_rule() -> const Rule* { return this->rule; };
  private:
    const Rule *rule;
};

#endif
