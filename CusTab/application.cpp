#include "application.h"

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
{
	if (!mEnglishTranslator.load("fcbrowser_en", ":/FCBrowser/i18n/")) {}
	if (!mChSimplTranslator.load("fcbrowser_zh", ":/FCBrowser/i18n/")) {}
}

Application::~Application()
{
}

bool Application::Initialize()
{
    return true;
}

bool Application::Finalize()
{
    return true;
}

Application::FLASHCENTERI18N Application::GetLanguage() const 
{
    return mLanguage;
}

void Application::SetLanguage(FLASHCENTERI18N language)
{
    if (mLanguage == language) { return; }

    mLanguage = language;

    this->removeTranslator(&mEnglishTranslator);
    this->removeTranslator(&mChSimplTranslator);

    if (language == English) {
        this->installTranslator(&mEnglishTranslator);
    } else if (language == Chinese) {
        this->installTranslator(&mChSimplTranslator);
    }
}
