#include <filesystem>
#include <fstream>
#include <iostream>
#include <unicode/locid.h>
#include <unicode/udata.h>
#include "i18n.h"

std::unordered_map<std::string, std::unique_ptr<char[]>> I18n::locales_data;

I18n::I18n(const char *locales_path, std::string package_name) : resource("", "", status)
{
    status = U_ZERO_ERROR;
    if (locales_data.find(package_name) == locales_data.end()) {
        
        std::ifstream file;
        file.open(locales_path);

        if (!file.is_open()) {
            std::cerr << "Error in opening data file!" << std::endl;
            std::cerr << "File: " << locales_path << std::endl;
            std::cerr << "Package Name: " << package_name << std::endl;
            exit(EXIT_FAILURE);
        }

        std::streamsize file_size = std::filesystem::file_size(std::filesystem::path{locales_path});

        locales_data[package_name] = std::make_unique<char[]>(file_size);

        file.read(locales_data[package_name].get(), file_size);

        udata_setAppData(package_name.c_str(), locales_data[package_name].get(), &status);

        if (!U_SUCCESS(status)) {
            std::cerr << "Error in loading data!" << std::endl;
            std::cerr << "Package Name: " << package_name << std::endl;
            std::cerr << u_errorName(status) << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    
    resource = icu::ResourceBundle(package_name.c_str(), icu::Locale().getName(), status);

    if (!U_SUCCESS(status)) {
        std::cerr << "Error in initializing resource bundle" << std::endl;
        std::cerr << "Package Name: " << package_name << std::endl;
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
        std::cerr << "Key: " << key << std::endl;
        std::cerr << u_errorName(status) << std::endl;
        exit(EXIT_FAILURE);
    }

    pattern = resource_object.getString(status);
    if (!U_SUCCESS(status)) {
        std::cerr << "Error in getting key text!" << std::endl;
        std::cerr << "Key: " << key << std::endl;
        std::cerr << u_errorName(status) << std::endl;
        exit(EXIT_FAILURE);
    }

    icu::MessageFormat::format(pattern, args.data(), args.size(), output, status);
    if (!U_SUCCESS(status)) {
        std::cerr << "Error in formatting!" << std::endl;
        std::cerr << "Key: " << key << std::endl;
        std::cerr << u_errorName(status) << std::endl;
        exit(EXIT_FAILURE);
    }

    return output;
}


icu::UnicodeString I18n::format(const char* key, const std::vector<icu::UnicodeString> arg_names,
                                                 const std::vector<icu::Formattable> arg_values)
{
    icu::UnicodeString pattern;
    icu::UnicodeString output;
    
    icu::ResourceBundle resource_object = resource.get(key, status);
    if (!U_SUCCESS(status)) {
        std::cerr << "Error: key not found!" << std::endl;
        std::cerr << "Key: " << key << std::endl;
        std::cerr << u_errorName(status) << std::endl;
        exit(EXIT_FAILURE);
    }

    pattern = resource_object.getString(status);
    if (!U_SUCCESS(status)) {
        std::cerr << "Error in getting key text!" << std::endl;
        std::cerr << "Key: " << key << std::endl;
        std::cerr << u_errorName(status) << std::endl;
        exit(EXIT_FAILURE);
    }

    icu::MessageFormat formatter {pattern, status};
    if (!U_SUCCESS(status)) {
        std::cerr << "Error in formatting!" << std::endl;
        std::cerr << "Key: " << key << std::endl;
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

void I18n::error(const char* key, const std::vector<icu::UnicodeString> arg_names,
                                  const std::vector<icu::Formattable> arg_values, bool quit)
{
    std::cerr << format(key, arg_names, arg_values) << std::endl;
    if (quit) {
        exit(EXIT_FAILURE);
    }
}