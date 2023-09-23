
#ifndef __HELPER_UI_H__
#define __HELPER_UI_H__

#include <QString>
#include <optional>

#include <qpoint.h>

class QJsonDocument;
class QGraphicsScene;
class QGraphicsItem;
class QWidget;

class HelperUi
{
  public:
    static QString loadStyleSheetFromResource(const QString& resourcePath);
    static QString formatTextColor(const QString& text, const QString& color);
    /**
     * @brief NOTE all QJson* are implictly shared
     * @param filePath
     * @return
     */
    static std::optional<QJsonDocument> loadJson(const QString& filePath);

    static std::optional<QString> installFont(const QString& fontPath);

    static void makeWidgetTransparent(QWidget* widget,
                                      bool ignoreMouseEvent = false);

    static QString readFileContent(QString const& filePath
                                 );

    static bool writeFileContent(QString const& filePath,
                                 QString const& content);
};

#endif  // __HELPER_UI_H__
