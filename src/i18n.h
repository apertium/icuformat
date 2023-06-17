#ifndef _I18N_
#define _I18N_
#include <unicode/resbund.h>
#include <unicode/ustring.h>
#include <unicode/msgfmt.h>
#include <vector>

class I18n
{
private:
    icu::ResourceBundle resource;
    UErrorCode status;
public:
    I18n(const char *locales_path);
    icu::UnicodeString format(const char* key, const std::vector<icu::Formattable> args = {});
    icu::UnicodeString format(const char* key, const std::vector<icu::UnicodeString> arg_names, const std::vector<icu::Formattable> arg_values);
};
#endif