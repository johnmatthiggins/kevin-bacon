#include <fstream>
#include <string>
#include <cstdio>
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
    string next_line;

    while (std::getline(fstream, next_line))
    {
        int source;
        int destination;

        parse_line(next_line, &source, &destination);

        // Check source and destination afterward.
        
    }

    return 0;
}

bool parse_line(std::string& line, int* source, int* destination)
{
    bool success = true;

    constexpr int SOURCE_PARSE = 0;
    constexpr int DESTINATION_PARSE = 1;
    constexpr int EXIT_PARSE = 2;
    std::string number;
    char* c = line.c_str();

    int state = SOURCE_PARSE;

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

