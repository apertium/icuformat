#include <iostream>
#include <unicode/ustream.h>
#include <unicode/udata.h>
#include <unicode/utypes.h>
#include "i18n.h"
int main() {
    /*
    UErrorCode status = U_ZERO_ERROR;
    UDataMemory *locales_dat = NULL;
    locales_dat = udata_open(LOCALES_DIR, "dat", "locales", &status);
    if (!U_SUCCESS(status)) {
        std::cerr << status << std::endl;
        exit(EXIT_FAILURE);
    }

    // UDataInfo *pInfo = NULL;
    // udata_getInfo(data, pInfo);
    // std::cout << pInfo->size << std::endl;

    udata_setAppData("locales.dat", udata_getMemory(locales_dat), &status);
    if (!U_SUCCESS(status)) {
        std::cerr << "setAppData" << std::endl;
        std::cerr << status << std::endl;
        exit(EXIT_FAILURE);
    }*/
    I18n i18n {LOCALES_DIR};

    std::cout << i18n.format("test_message") << std::endl;
    std::cout << i18n.format("complex_message", {"Ahmed", "Egypt"}) << std::endl;
    return 0;
}