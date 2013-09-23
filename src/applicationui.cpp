

#include "applicationui.hpp"
#include "filedataicon.hpp"
#include "filedatalistmodel.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>
#include <bb/cascades/QListDataModel>

using namespace bb::cascades;

///////////////////////////////////////////////////////////////////////////////

#define BBFM_THREAD_POOL_SIZE 5

ApplicationUI::ApplicationUI(bb::cascades::Application *app)
: QObject(app)
, m_model(new FileDataListModel(false, this))
{
	QThreadPool::globalInstance ()->setMaxThreadCount(BBFM_THREAD_POOL_SIZE);

    // Load file icons
    FileDataIcon::loadIcons();

    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);
    if(!QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()))) {
        // This is an abnormal situation! Something went wrong!
        // Add own code to recover here
        qWarning() << "Recovering from a failed connect()";
    }
    // initial load
    onSystemLanguageChanged();

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("_app", this);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    app->setScene(root);
}

ApplicationUI::~ApplicationUI()
{
    // Free file icons
    FileDataIcon::freeIcons();
}

///////////////////////////////////////////////////////////////////////////////

void ApplicationUI::loadLocalFiles()
{
    setDir("/accounts/1000/shared/photos/photos-1");
	m_model->loadData();
}

void ApplicationUI::loadRemoteFiles()
{
	setDir();
	m_model->loadData();
}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("bbfmtest_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}

///////////////////////////////////////////////////////////////////////////////

bb::cascades::DataModel* ApplicationUI::model() const
{
    return m_model;
}

void ApplicationUI::setDir(const QString& path)
{
	qWarning() << "ApplicationUI::setDir " << path;

	m_model->setDir(path);
}

void ApplicationUI::setDir()
{
	qWarning() << "ApplicationUI::setDir";

	m_model->addFile(QUrl("http://upload.wikimedia.org/wikipedia/commons/6/62/Peace_riding_in_a_triumphal_chariot_Bosio_Carrousel_-_2012-05-28.jpg"));
	m_model->addFile(QUrl("http://upload.wikimedia.org/wikipedia/commons/a/af/Crepuscular_rays_with_reflection_in_GGP.jpg"));
	m_model->addFile(QUrl("http://upload.wikimedia.org/wikipedia/commons/2/2a/Anodorhynchus_hyacinthinus_-Hyacinth_Macaw_-side_of_head.jpg"));
	m_model->addFile(QUrl("http://upload.wikimedia.org/wikipedia/commons/2/29/Bataille_Waterloo_1815_reconstitution_2011_cuirassier.jpg"));
	m_model->addFile(QUrl("http://upload.wikimedia.org/wikipedia/commons/e/ec/Armadillo_Aerospace_Pixel_Hover.jpg"));
	m_model->addFile(QUrl("http://upload.wikimedia.org/wikipedia/commons/f/f5/A_sculpture_at_the_entrance_to_the_palace_of_Versailles.jpg"));
	m_model->addFile(QUrl("http://upload.wikimedia.org/wikipedia/commons/6/6d/Firehole_river_at_Upper_Geyser_Basin-2008-june.jpg"));
	m_model->addFile(QUrl("http://upload.wikimedia.org/wikipedia/commons/7/7c/Peugeot_206_WRC.jpg"));
	m_model->addFile(QUrl("http://upload.wikimedia.org/wikipedia/commons/9/97/Toda_Hut.JPG"));
	m_model->addFile(QUrl("http://upload.wikimedia.org/wikipedia/commons/d/dc/Marriott_Center_1.JPG"));
}

///////////////////////////////////////////////////////////////////////////////

