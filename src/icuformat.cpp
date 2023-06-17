#include <iostream>
#include <unicode/ustream.h>
#include "i18n.h"

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cout << "USAGE: icuformat <data-path> <key> <args>\n";
        return 0;
    }

    I18n i18n {argv[1]};
    
    std::vector<icu::Formattable> arguments;
    for (int i = 3; i < argc; i++) {
        arguments.push_back(argv[i]);
    }

    std::cout << i18n.format(argv[2], arguments) << std::endl;
    return 0;
}
