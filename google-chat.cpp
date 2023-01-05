#include <QCommandLineParser>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWebEngineProfile>
#include <QProcessEnvironment>
#include <QSystemTrayIcon>
#include <QDebug>
#include <QIcon>
#include <QAction>
#include <QMenu>
#include <QTranslator>

#include <QtGlobal>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName(QCoreApplication::tr("Google Chat"));
    QCoreApplication::setApplicationVersion("1.0");
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    QCommandLineParser parser, childParser;
    parser.setApplicationDescription(QCoreApplication::tr("Chat client for Google Chat"));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption({{"p", "profile"}, QCoreApplication::tr("main", "Run as a different <profile>"), "profile", "Default"});
    childParser.addOption({"child", "Run child process"});
    childParser.addOption({{"p", "profile"}, QCoreApplication::tr("main", "Run as a different <profile>"), "profile", "Default"});
    QStringList args;
    for (int i = 0; i < argc; ++i) {
        args << argv[i];
    }
    childParser.parse(args);

    if (childParser.isSet("child")) {
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        QtWebEngineQuick::initialize();
        QGuiApplication app(argc, argv);
        // Load bundled icon theme for SysTrayIcon        
        QIcon::setThemeName("google-chat");
        // Disable OffTheRecord and force persistent cookies in order to save cookies to application profile
        QQuickWebEngineProfile::defaultProfile()->setOffTheRecord(false);
        QQuickWebEngineProfile::defaultProfile()->setPersistentCookiesPolicy(QQuickWebEngineProfile::ForcePersistentCookies);
        // Save cookies and session storage to a specific user profile
        QQuickWebEngineProfile::defaultProfile()->setStorageName(childParser.value("profile"));

        app.setWindowIcon(QIcon::fromTheme(QStringLiteral("google-chat")));

        QQmlApplicationEngine engine;
        engine.load(QUrl(QStringLiteral("qrc:/google-chat.qml")));

        return app.exec();
    } else {
        QCoreApplication app(argc, argv);
        qInfo() << "Starting Google Chat client.";
        qputenv("PULSE_PROP_OVERRIDE_application.icon", "google-chat");
        qputenv("PULSE_PROP_OVERRIDE_application.icon_name", "google-chat");
        qputenv("PULSE_PROP_OVERRIDE_application.name", QCoreApplication::tr("Google Chat").toLocal8Bit());
        qputenv("PULSE_PROP_application.icon", "google-chat");
        qputenv("PULSE_PROP_application.icon_name", "google-chat");
        qputenv("PULSE_PROP_application.name", QCoreApplication::tr("Google Chat").toLocal8Bit());
        QProcess child;
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        env.insert("PULSE_PROP_OVERRIDE_application.icon", "google-chat");
        env.insert("PULSE_PROP_OVERRIDE_application.icon_name", "google-chat");
        env.insert("PULSE_PROP_application.icon", "google-chat");
        env.insert("PULSE_PROP_application.icon_name", "google-chat");
        env.insert("PULSE_PROP_OVERRIDE_application.name", QCoreApplication::tr("Google Chat").toLocal8Bit());
        env.insert("PULSE_PROP_application.name", QCoreApplication::tr("Google Chat").toLocal8Bit());
        child.setProcessEnvironment(env);
        child.setProgram(argv[0]);
        parser.process(app);
        QStringList arguments;
        arguments << "--child";
        arguments << "--profile" << parser.value("profile");
        qInfo() << QString("Using profile " + parser.value("profile")).toStdString().c_str();
        child.setArguments(arguments);
        child.setProcessChannelMode(QProcess::MergedChannels);
        child.start(argv[0], arguments);
        child.waitForFinished(-1);
    }
}

