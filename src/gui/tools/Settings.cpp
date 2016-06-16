/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */
#include "Settings.h"

#include <QCoreApplication>
#include <QFontDatabase>
#include <QJsonDocument>
#include <QJsonValue>

#include <include/HighlightingRule.h>

static const QString LastOpenDirValueName("last open dir");
static const QString LastOpenedFilesValueName("last open files");
static const QString RecentlyOpenedFilesValueName("recent files");
static const QString WordHighlightingRulesValueName("word rules");
static const QString LineHighlightingRulesValueName("line rules");
static const QString TextViewFontValueName("text view font");
static const QString MainWindowGeometryValueName("main window geometry");
static const QString MainWindowStateValueName("main window state");

Settings::Settings()
{
   qRegisterMetaType<Settings::SettingValue>("Settings::SettingValue");
}

void Settings::setLastOpenDir(const QDir &dir)
{
   m_settings.setValue(LastOpenDirValueName, dir.absolutePath());
}

QDir Settings::lastOpenDir() const
{
   return QDir(m_settings.value(LastOpenDirValueName).toString(), QCoreApplication::applicationDirPath());
}

void Settings::setLastOpenedFiles(const QStringList &files)
{
   m_settings.setValue(LastOpenedFilesValueName, files);
}

/*!
 * \brief Settings::lastOpenFiles
 * A list of the files that were opened the last time the application was started.
 */
QStringList Settings::lastOpenedFiles() const
{
   return m_settings.value(LastOpenedFilesValueName).toStringList();
}

void Settings::setRecentlyOpenedFiles(const QStringList &files)
{
   m_settings.setValue(RecentlyOpenedFilesValueName, files);
}

QStringList Settings::recentlyOpenedFiles() const
{
   return m_settings.value(RecentlyOpenedFilesValueName).toStringList();
}

void Settings::setHighlightingRules(const QList<HighlightingRule> &lineRules,
                                    const QList<HighlightingRule> &wordRules)
{
   m_settings.setValue(LineHighlightingRulesValueName, highlightingListToStringList(lineRules));
   m_settings.setValue(WordHighlightingRulesValueName, highlightingListToStringList(wordRules));
}

QList<HighlightingRule> Settings::wordHighlightingRules() const
{
   return highlightingStringListToList(m_settings.value(WordHighlightingRulesValueName).toStringList());
}

QList<HighlightingRule> Settings::lineHighlightingRules() const
{
   return highlightingStringListToList(m_settings.value(LineHighlightingRulesValueName).toStringList());
}

QFont Settings::textViewFont() const
{
   QFont defaultFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
   QString fontString = m_settings.value(TextViewFontValueName, defaultFont.toString()).toString();
   QFont font;
   if (!font.fromString(fontString)) {
      return defaultFont;
   }

   return font;
}

void Settings::setTextViewFont(const QFont &font)
{
   m_settings.setValue(TextViewFontValueName, font.toString());
}

QByteArray Settings::mainWindowGeometry() const
{
   return m_settings.value(MainWindowGeometryValueName).toByteArray();
}

void Settings::setMainWindowGeometry(const QByteArray &geometry)
{
   m_settings.setValue(MainWindowGeometryValueName, geometry);
}

QByteArray Settings::mainWindowState() const
{
   return m_settings.value(MainWindowStateValueName).toByteArray();
}

void Settings::setMainWindowState(const QByteArray &state)
{
   m_settings.setValue(MainWindowStateValueName, state);
}

QStringList Settings::highlightingListToStringList(const QList<HighlightingRule> &rules) const
{
   QStringList stringList;

   foreach (const HighlightingRule &rule, rules) {
      QJsonDocument jsonDoc(rule.toJson());
      stringList.append(QString(jsonDoc.toJson(QJsonDocument::Compact)));
   }

   return stringList;
}

QList<HighlightingRule> Settings::highlightingStringListToList(const QStringList &stringList) const
{
   QList<HighlightingRule> rules;

   foreach (const QString &value, stringList) {
      HighlightingRule rule;
      QJsonDocument jsonDoc = QJsonDocument::fromJson(value.toUtf8());
      QJsonObject jsonObject = jsonDoc.object();
      rule.fromJson(jsonObject);
      rules.append(rule);
   }

   return rules;
}

