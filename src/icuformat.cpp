#include <iostream>
#include <unicode/ustream.h>
#include "i18n.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "USAGE: icuformat <key> <args>\n";
        return 0;
    }

    I18n i18n {LOCALES_DATA};
    
    std::vector<icu::Formattable> arguments;
    for (int i = 2; i < argc; i++) {
        arguments.push_back(argv[i]);
    }

    std::cout << i18n.format(argv[1], arguments) << std::endl;
    return 0;
}