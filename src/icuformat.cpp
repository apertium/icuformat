#include <iostream>
#include <unicode/ustream.h>
#include "i18n.h"

int main(int argc, char* argv[])
{
    if (argc < 3 || argc % 2 == 0) {
        std::cout << "USAGE: icuformat <data-path> <key> <arg-names> <arg-values>\n";
        return 0;
    }

    I18n i18n {argv[1]};
    
    std::vector<icu::UnicodeString> arg_names;
    std::vector<icu::Formattable> arg_values;
    if (argc > 3) {
        int arg_values_start = (argc - 3) / 2 + 3;

        for (int i = 3; i < arg_values_start; i++) {
            arg_names.push_back(argv[i]);
        }
        
        for (int i = arg_values_start; i < argc; i++) {
            arg_values.push_back(argv[i]);
        }
    }
    std::cout << i18n.format(argv[2], arg_names, arg_values) << std::endl;
    return 0;
}
