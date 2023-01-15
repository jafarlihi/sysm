#include "file_column_source.hh"

auto FileColumnSource::fetch() -> std::string {
  std::string result;
  FILE *file = fopen(this->get_rule()->settings.find("file")->second.c_str(), "r");
  int count = 0;
  char word[100];
  while (fscanf(file, "%99s", word) != EOF)
    if (count++ == std::stoi(this->get_rule()->settings.find("column")->second)) {
      result = word;
      break;
    }
  fclose(file);
  return result;
}
