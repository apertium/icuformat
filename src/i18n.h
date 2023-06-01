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
    I18n(const char* locales_dir);
    icu::UnicodeString format(const char* key, const std::vector<icu::Formattable> args = {});
};
#endif