#ifndef application_h
#define application_h

#include <QTranslator>
#include <QApplication>

class Application : public QApplication
{
	Q_OBJECT

public:
    typedef enum FLASHCENTERI18N {
        Chinese,
        English
    };

public:
	Application(int &argc, char **argv);
	~Application();
	bool Initialize();
	bool Finalize();
	FLASHCENTERI18N GetLanguage() const;
	void SetLanguage(FLASHCENTERI18N language);

private:
	QTranslator mEnglishTranslator;
    // ÖÐÎÄ¼òÌå
	QTranslator mChSimplTranslator;
	FLASHCENTERI18N mLanguage;

};


#endif // application_h