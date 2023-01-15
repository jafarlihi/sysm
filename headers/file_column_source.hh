#ifndef SYSM_FILE_COLUMN_SOURCE_HH
#define SYSM_FILE_COLUMN_SOURCE_HH

#include "source.hh"

class FileColumnSource : public Source {
  public:
    using Source::Source;
    auto fetch() -> std::string override;
};

#endif
