#ifndef _I18N_
#define _I18N_
#include <vector>
#include <memory>
#include <unordered_map>

#include <unicode/ustream.h>
#include <unicode/resbund.h>
#include <unicode/ustring.h>
#include <unicode/msgfmt.h>

class I18n
{
private:
    static std::unordered_map<std::string, std::unique_ptr<char[]>> locales_data;
    icu::ResourceBundle resource;
    UErrorCode status;
public:
    I18n(const char *locales_path, std::string package_name);
    icu::UnicodeString format(const char* key, const std::vector<icu::Formattable> args = {});
    icu::UnicodeString format(const char* key, const std::vector<icu::UnicodeString> arg_names,
                                               const std::vector<icu::Formattable> arg_values);
    void error(const char* key, const std::vector<icu::UnicodeString> arg_names,
                                const std::vector<icu::Formattable> arg_values, bool quit);
};
#endif