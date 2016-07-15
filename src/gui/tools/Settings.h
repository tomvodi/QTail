/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */
#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDir>
#include <QList>
#include <QSettings>
#include <QSharedPointer>
#include <QMetaType>

class HighlightingRule;
class FilterGroup;

class Settings
{
   friend class SettingsTest;
public:
   enum SettingCategory {
      NoValue = 0,
      TextViewSettings = 1
   };

   Settings();

   void setLastOpenDir(const QDir &dir);
   QDir lastOpenDir() const;

   void setLastOpenedFiles(const QStringList &files);
   QStringList lastOpenedFiles() const;

   void setRecentlyOpenedFiles(const QStringList &files);
   QStringList recentlyOpenedFiles() const;

   void setHighlightingRules(const QList<HighlightingRule> &lineHighlightingRules,
                             const QList<HighlightingRule> &wordHighlightingRules);

   QList<HighlightingRule> wordHighlightingRules() const;
   QList<HighlightingRule> lineHighlightingRules() const;

   QFont textViewFont() const;
   void setTextViewFont(const QFont &font);

   bool textViewLineWrap() const;
   void setTextViewLineWrap(bool wrapOn);

   int textViewUpdateIntervalMs() const;
   void setTextViewUpdateIntervalMs(int interval);

   QByteArray mainWindowGeometry() const;
   void setMainWindowGeometry(const QByteArray &geometry);

   QByteArray mainWindowState() const;
   void setMainWindowState(const QByteArray &state);

   QList<FilterGroup> filterGroups() const;
   void setFilterGroups(const QList<FilterGroup> &filterGroups);

private:
   QStringList highlightingListToStringList(const QList<HighlightingRule> &rules) const;
   QList<HighlightingRule> highlightingStringListToList(const QStringList &list) const;
   QStringList filterGroupListToStringList(const QList<FilterGroup> &groups) const;
   QList<FilterGroup> filterGroupListFromStringList(const QStringList &list) const;
   QSettings m_settings;
};

Q_DECLARE_METATYPE(Settings::SettingCategory)

typedef QSharedPointer<Settings> ApplicationSettings;

#endif // SETTINGS_H
