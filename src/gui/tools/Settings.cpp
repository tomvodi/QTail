/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */
#include "Settings.h"

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonValue>

#include <include/HighlightingRule.h>

static const QString LastOpenDirValueName("last open dir");
static const QString LastOpenedFilesValueName("last open files");
static const QString RecentlyOpenedFilesValueName("recent files");
static const QString WordHighlightingRulesValueName("word rules");
static const QString LineHighlightingRulesValueName("line rules");

Settings::Settings()
{
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

QList<HighlightingRule> Settings::wordRules() const
{
   return highlightingStringListToList(m_settings.value(WordHighlightingRulesValueName).toStringList());
}

QList<HighlightingRule> Settings::lineRules() const
{
   return highlightingStringListToList(m_settings.value(LineHighlightingRulesValueName).toStringList());
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

