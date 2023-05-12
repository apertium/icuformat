#include <iostream>
#include <unicode/ustream.h>
#include "i18n.h"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "USAGE: icuformat <key>\n";
        return 0;
    }

    I18n i18n;

    std::cout << i18n.format(argv[1]) << std::endl;
    
    return 0;
}