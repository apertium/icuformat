#include <unicode/ustream.h>
#include <unicode/resbund.h>
#include <unicode/locid.h>
#include <unicode/ustring.h>
#include <unicode/msgfmt.h>
#include <vector>
#include "i18n.h"

I18n::I18n(const char* locales_path) : resource("", "", status)
{
    status = U_ZERO_ERROR;

    u_setDataDirectory(locales_path);
    resource = icu::ResourceBundle("locales", icu::Locale().getName(), status);

    if (!U_SUCCESS(status)) {
        std::cerr << "Error in accessing locales directory!" << std::endl;
        exit(EXIT_FAILURE);
    }
    status = U_ZERO_ERROR;
}

icu::UnicodeString I18n::format(const char* key, const std::vector<icu::Formattable> args)
{
    icu::UnicodeString pattern;
    icu::UnicodeString output;
    
    icu::ResourceBundle resource_object = resource.get(key, status);
    if (!U_SUCCESS(status)) {
        std::cerr << "Error: key not found!" << std::endl;
        exit(EXIT_FAILURE);
    }

    pattern = resource_object.getString(status);
    if (!U_SUCCESS(status)) {
        std::cerr << "Error in getting key text!" << std::endl;
        exit(EXIT_FAILURE);
    }

    icu::MessageFormat::format(pattern, args.data(), args.size(), output, status);
    if (!U_SUCCESS(status)) {
        std::cerr << "Error in formatting!" << std::endl;
        exit(EXIT_FAILURE);
    }

    return output;
}