#include <fstream>
#include <string>
#include <cstdio>
#include <cstdint>
#include "cleaner.h"

/**
 * The main entry point to the program.
 *
 * @param argc
 * @param argv
 * @return The exit code for the program.
 */
int main(int argc, char** argv)
{
    using std::string;

    if (argc < 3)
    {
        printf("Not enough arguments...\n");
        return 0;
    }

    string source(argv[1]);
    string destination(argv[2]);

    std::ifstream file(source.c_str());
    std::ofstream dest_file(destination.c_str());
    string next_line;

    while (std::getline(file, next_line))
    {
        int32_t source;
        int32_t destination;

        parse_line(next_line, &source, &destination);

        // Check source and destination afterward.
        std::string source_str = to_four_byte_str(source);
        std::string destination_str = to_four_byte_str(destination);

        dest_file << source_str << destination_str << '\n';
    }

    file.close();
    dest_file.close();

    return 0;
}

bool parse_line(std::string& line, int32_t* source, int32_t* destination)
{
    bool success = true;

    constexpr int SOURCE_PARSE = 0;
    constexpr int DESTINATION_PARSE = 1;
    constexpr int EXIT_PARSE = 2;
    std::string number;
    const char* c = line.c_str();

    int32_t state = SOURCE_PARSE;

    while (state != EXIT_PARSE && *c)
    {
        switch (state)
        {
            case SOURCE_PARSE:
                if (isdigit(*c))
                {
                    number.push_back(*c);
                }
                else if (*c != 'n' && *c != 'm')
                {
                    state = DESTINATION_PARSE;
                    *source = stoi(number);
                    number.clear();
                }
                break;
            case DESTINATION_PARSE:
                if (isdigit(*c))
                {
                    number.push_back(*c);
                }
                else if (*c != 'n' && *c != 'm')
                {
                    state = DESTINATION_PARSE;
                    *destination = stoi(number);
                }
                break;
            case EXIT_PARSE:
                // Don't do anything just exit.
                break;
        }

        c++;
    }

    return success;
}

std::string to_four_byte_str(int32_t num)
{
    char* num_str = (char*)&num;

    char four_byte_str[5] = { num_str[0], num_str[1], num_str[2], num_str[3], '\0' };
    std::string four_bytes(four_byte_str);

    return four_bytes;
}
