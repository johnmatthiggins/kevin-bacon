#ifndef CLEANER_H
#define CLEANER_H

#include <string>
#include <cstdint>

bool parse_line(std::string& line, int32_t* source, int32_t* destination);
std::string to_four_byte_str(int32_t num);

#endif
