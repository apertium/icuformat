#include <iostream>
#include <unicode/ustream.h>
#include <unicode/udata.h>
#include <unicode/utypes.h>
#include "i18n.h"
int main() {
    /*
    UErrorCode status = U_ZERO_ERROR;
    u_setDataDirectory(LOCALES_DATA);
    void *data = udata_open(LOCALES_DATA, "res", "icuformat", &status);
    if (!U_SUCCESS(status)) {
        std::cerr << status << std::endl;
        exit(EXIT_FAILURE);
    }*/
    I18n i18n {LOCALES_DIR};

    std::cout << i18n.format("test_message") << std::endl;
    std::cout << i18n.format("complex_message", {"Ahmed", "Egypt"}) << std::endl;
    return 0;
}