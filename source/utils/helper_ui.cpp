#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QTime>
#include <QUrl>
#include <QWidget>
#include <QtDebug>
#include <string>
#include <unordered_map>

#include "helper_ui.h"

#include <qtpreprocessorsupport.h>

QString HelperUi::loadStyleSheetFromResource(const QString& resourcePath)
{
    QFile qss(resourcePath);
    if (!qss.open(QFile::ReadOnly)) {
        qWarning() << QStringLiteral("Failed to load style:") << resourcePath;
        return {};
    }

    return qss.readAll();
}

QString HelperUi::formatTextColor(const QString& text, const QString& color)
{
    return QString("<font color=\"%1\">%2</font> ").arg(color).arg(text);
}

std::optional<QJsonDocument> HelperUi::loadJson(const QString& filePath)
{
    QFile loadFile(filePath);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return {};
    }
    return QJsonDocument::fromJson(loadFile.readAll());
    ;
}

std::optional<QString> HelperUi::installFont(const QString& fontPath)
{
    static std::unordered_map<std::string, std::string> fontExists;
    if (auto mayBeExist = fontExists.find(fontPath.toStdString());
        mayBeExist != fontExists.end())
        return QString::fromStdString(mayBeExist->second);

    auto fontID = QFontDatabase::addApplicationFont(fontPath);
    if (QFontDatabase::applicationFontFamilies(fontID).size() > 0) {
        QString shouldOnlyOneAvailable =
            QFontDatabase::applicationFontFamilies(fontID).at(0);
        fontExists.insert(std::make_pair(fontPath.toStdString(),
                                         shouldOnlyOneAvailable.toStdString()));
        return std::make_optional(shouldOnlyOneAvailable);
    } else {
        qWarning() << "Font not found!";
        return {};
    }
}

void HelperUi::makeWidgetTransparent(QWidget* widget, bool ignoreMouseEvent)
{
    widget->setWindowFlags(Qt::FramelessWindowHint);
    widget->setAttribute(Qt::WA_NoSystemBackground);
    widget->setAttribute(Qt::WA_TranslucentBackground);
    if (ignoreMouseEvent)
        widget->setAttribute(Qt::WA_TransparentForMouseEvents);
    foreach(QWidget* child, widget->findChildren<QWidget*>())

        makeWidgetTransparent(child, ignoreMouseEvent);
}
QString HelperUi::readFileContent(QString const& filePath)
{
    QFile handle(filePath);
    if (handle.exists() && handle.open(QIODevice::ReadOnly)) {
        QTextStream stream(&handle);
        stream.setEncoding(QStringConverter::Utf8);
        stream.setAutoDetectUnicode(true);
        return stream.readAll();
    }
    return {};
}

bool HelperUi::writeFileContent(QString const& filePath, QString const& content)
{
    QFile fileHandel(filePath);
    if (!fileHandel.open(QIODevice::WriteOnly)) {
        qCritical() << "Open file for writing failed: " << filePath;
        return {};
    }
    QTextStream stream(&fileHandel);
    stream.setEncoding(QStringConverter::Utf8);
    stream.setAutoDetectUnicode(true);
    stream << content;
    return true;
}
