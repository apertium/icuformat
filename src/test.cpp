#include <iostream>
#include <unicode/ustream.h>
#include "i18n.h"

int main() {
    I18n i18n;

    std::cout << i18n.format("test_message") << std::endl;
    return 0;
}