#include <unicode/ustream.h>
#include <unicode/resbund.h>
#include <unicode/locid.h>
#include <unicode/ustring.h>
#include <unicode/msgfmt.h>
#include <unicode/udata.h>
#include <filesystem>
#include <vector>
#include "i18n.h"

I18n::I18n(const char *locales_path) : resource("", "", status)
{
    status = U_ZERO_ERROR;

    FILE *file = fopen(locales_path, "r");
    if (file == NULL) {
        std::cerr << "Error in opening data file!" << std::endl;
        exit(EXIT_FAILURE);
    }
    size_t file_size = std::filesystem::file_size(std::filesystem::path{locales_path});
    
    void *locales_data = malloc(file_size);
    size_t success_reads = fread(locales_data, 1, file_size, file);

    if (success_reads != file_size) {
        std::cerr << "Error in loading data file!" << std::endl;
        exit(EXIT_FAILURE);
    }

    udata_setAppData("locales", locales_data, &status);
    
    fclose(file);
    free(locales_data);

    if (!U_SUCCESS(status)) {
        std::cerr << "Error in loading data!" << std::endl;
        std::cerr << u_errorName(status) << std::endl;
        exit(EXIT_FAILURE);
    }
    resource = icu::ResourceBundle("locales", icu::Locale().getName(), status);

    if (!U_SUCCESS(status)) {
        std::cerr << "Error in accessing locales directory!" << std::endl;
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

