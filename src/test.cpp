#include <iostream>
#include <unicode/ustream.h>
#include "i18n.h"


int main() {
    I18n i18n {LOCALES_DATA};

    std::cout << i18n.format("test_message") << std::endl;
    std::cout << i18n.format("complex_message", {"Ahmed", "Egypt"}) << std::endl;
    return 0;
}