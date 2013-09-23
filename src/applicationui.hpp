#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>

namespace bb
{
    namespace cascades
    {
        class Application;
        class LocaleHandler;
        class DataModel;
    }
}

class QTranslator;
class FileDataListModel;

class ApplicationUI : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bb::cascades::DataModel* model READ model CONSTANT)

public:
    ApplicationUI(bb::cascades::Application *app);
    virtual ~ApplicationUI();

    Q_INVOKABLE void loadLocalFiles();
    Q_INVOKABLE void loadRemoteFiles();

private slots:
    void onSystemLanguageChanged();

private:
    bb::cascades::DataModel* model() const;

    void setDir(const QString& path);
    void setDir();

    QTranslator* m_pTranslator;
    bb::cascades::LocaleHandler* m_pLocaleHandler;
    FileDataListModel* m_model;
};

#endif /* ApplicationUI_HPP_ */
