#ifndef _I18N_
#define _I18N_
#include <unicode/resbund.h>
#include <unicode/ustring.h>

class I18n {
    private:
    icu::ResourceBundle resource;
    UErrorCode status = U_ZERO_ERROR;
    public:
    I18n();
    icu::UnicodeString format(const char* key);
};
#endif