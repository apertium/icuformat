#include <unicode/ustream.h>
#include <unicode/resbund.h>
#include <unicode/locid.h>
#include <unicode/ustring.h>
#include <unicode/msgfmt.h>
#include "i18n.h"

I18n::I18n() : resource(LOCALES_DIR, icu::Locale().getName(), status)
{
    if (!U_SUCCESS(status)) {
        std::cerr << "Error in accessing locales directory!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

icu::UnicodeString I18n::format(const char* key)
{
    icu::UnicodeString output;
    
    icu::ResourceBundle pattern = resource.get(key, status);
    if (!U_SUCCESS(status)) {
        std::cerr << "Error: key not found!" << std::endl;
        exit(EXIT_FAILURE);
    }

    output = pattern.getString(status);
    if (!U_SUCCESS(status)) {
        std::cerr << "Error in getting key text!" << std::endl;
        exit(EXIT_FAILURE);
    }

    return output;
}