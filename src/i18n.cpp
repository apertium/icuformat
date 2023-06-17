#include <unicode/ustream.h>
#include <unicode/resbund.h>
#include <unicode/locid.h>
#include <unicode/ustring.h>
#include <unicode/msgfmt.h>
#include <unicode/udata.h>
#include <filesystem>
#include <fstream>
#include <vector>
#include <memory>
#include "i18n.h"

I18n::I18n(const char *locales_path) : resource("", "", status)
{
    status = U_ZERO_ERROR;

    std::ifstream file;
    file.open(locales_path);

    if (!file.is_open()) {
        std::cerr << "Error in opening data file!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::streamsize file_size = std::filesystem::file_size(std::filesystem::path{locales_path});

    auto locales_data = std::make_unique<char[]>(file_size);

    file.read(locales_data.get(), file_size);
    
    udata_setAppData("locales", locales_data.get(), &status);

    if (!U_SUCCESS(status)) {
        std::cerr << "Error in loading data!" << std::endl;
        std::cerr << u_errorName(status) << std::endl;
        exit(EXIT_FAILURE);
    }

    resource = icu::ResourceBundle("locales", icu::Locale().getName(), status);

    if (!U_SUCCESS(status)) {
        std::cerr << "Error in initializing resource bundle" << std::endl;
        std::cerr << u_errorName(status) << std::endl;
        exit(EXIT_FAILURE);
    }
}

icu::UnicodeString I18n::format(const char* key, const std::vector<icu::Formattable> args)
{
    icu::UnicodeString pattern;
    icu::UnicodeString output;
    
    icu::ResourceBundle resource_object = resource.get(key, status);
    if (!U_SUCCESS(status)) {
        std::cerr << "Error: key not found!" << std::endl;
        std::cerr << u_errorName(status) << std::endl;
        exit(EXIT_FAILURE);
    }

    pattern = resource_object.getString(status);
    if (!U_SUCCESS(status)) {
        std::cerr << "Error in getting key text!" << std::endl;
        std::cerr << u_errorName(status) << std::endl;
        exit(EXIT_FAILURE);
    }

    icu::MessageFormat::format(pattern, args.data(), args.size(), output, status);
    if (!U_SUCCESS(status)) {
        std::cerr << "Error in formatting!" << std::endl;
        std::cerr << u_errorName(status) << std::endl;
        exit(EXIT_FAILURE);
    }

    return output;
}


icu::UnicodeString I18n::format(const char* key, const std::vector<icu::UnicodeString> arg_names, const std::vector<icu::Formattable> arg_values)
{
    icu::UnicodeString pattern;
    icu::UnicodeString output;
    
    icu::ResourceBundle resource_object = resource.get(key, status);
    if (!U_SUCCESS(status)) {
        std::cerr << "Error: key not found!" << std::endl;
        std::cerr << u_errorName(status) << std::endl;
        exit(EXIT_FAILURE);
    }

    pattern = resource_object.getString(status);
    if (!U_SUCCESS(status)) {
        std::cerr << "Error in getting key text!" << std::endl;
        std::cerr << u_errorName(status) << std::endl;
        exit(EXIT_FAILURE);
    }

    icu::MessageFormat formatter {pattern, status};
    if (!U_SUCCESS(status)) {
        std::cerr << "Error in formatting!" << std::endl;
        std::cerr << u_errorName(status) << std::endl;
        exit(EXIT_FAILURE);
    }

    formatter.format(arg_names.data(), arg_values.data(), arg_values.size(), output, status);
    
    if (!U_SUCCESS(status)) {
        std::cerr << "Error in formatting!" << std::endl;
        std::cerr << u_errorName(status) << std::endl;
        exit(EXIT_FAILURE);
    }

    return output;
}

