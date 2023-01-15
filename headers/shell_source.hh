#ifndef SYSM_SHELL_SOURCE_HH
#define SYSM_SHELL_SOURCE_HH

#include "source.hh"

class ShellSource : public Source {
  public:
    using Source::Source;
    auto fetch() -> std::string override;
};

#endif
