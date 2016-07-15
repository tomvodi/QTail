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

#include <include/FilterGroup.h>
#include <include/HighlightingRule.h>

static const QString LastOpenDirValueName("last open dir");
static const QString LastOpenedFilesValueName("last open files");
static const QString RecentlyOpenedFilesValueName("recent files");
static const QString WordHighlightingRulesValueName("word rules");
static const QString LineHighlightingRulesValueName("line rules");

static const QString TextViewFontValueName("textview/font");
static const QString TextViewLineWrapValueName("textview/linewrap");
static const QString TextViewUpdateIntervalValueName("textview/updateinterval");

static const QString MainWindowGeometryValueName("main window geometry");
static const QString MainWindowStateValueName("main window state");

static const QString FilterGroupsValueName("filter groups");

Settings::Settings()
{
   qRegisterMetaType<Settings::SettingCategory>("Settings::SettingCategory");
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

bool Settings::textViewLineWrap() const
{
   return m_settings.value(TextViewLineWrapValueName, true).toBool();
}

void Settings::setTextViewLineWrap(bool wrapOn)
{
   m_settings.setValue(TextViewLineWrapValueName, wrapOn);
}

/*!
 * \brief Settings::textViewUpdateIntervalMs
 * The update interval of text views in milliseconds.
 * \return
 */
int Settings::textViewUpdateIntervalMs() const
{
   return m_settings.value(TextViewUpdateIntervalValueName, 250).toInt();
}

void Settings::setTextViewUpdateIntervalMs(int interval)
{
   m_settings.setValue(TextViewUpdateIntervalValueName, interval);
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

QList<FilterGroup> Settings::filterGroups() const
{
   QStringList groupList = m_settings.value(FilterGroupsValueName).toStringList();
   return filterGroupListFromStringList(groupList);
}

void Settings::setFilterGroups(const QList<FilterGroup> &filterGroups)
{
   QStringList groupList = filterGroupListToStringList(filterGroups);
   m_settings.setValue(FilterGroupsValueName, groupList);
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

QList<HighlightingRule> Settings::highlightingStringListToList(const QStringList &list) const
{
   QList<HighlightingRule> rules;

   foreach (const QString &value, list) {
      HighlightingRule rule;
      QJsonDocument jsonDoc = QJsonDocument::fromJson(value.toUtf8());
      QJsonObject jsonObject = jsonDoc.object();
      rule.fromJson(jsonObject);
      rules.append(rule);
   }

   return rules;
}

QStringList Settings::filterGroupListToStringList(const QList<FilterGroup> &groups) const
{
   QStringList stringList;

   foreach (const FilterGroup &group, groups) {
      QJsonDocument jsonDoc(group.toJson());
      stringList.append(QString(jsonDoc.toJson(QJsonDocument::Compact)));
   }

   return stringList;
}

QList<FilterGroup> Settings::filterGroupListFromStringList(const QStringList &list) const
{
   QList<FilterGroup> groups;

   foreach (const QString &value, list) {
      FilterGroup group;
      QJsonDocument jsonDoc = QJsonDocument::fromJson(value.toUtf8());
      QJsonObject jsonObject = jsonDoc.object();
      group.fromJson(jsonObject);
      groups.append(group);
   }

   return groups;
}

