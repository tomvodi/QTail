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

class Settings
{
   friend class SettingsTest;
public:
   enum SettingValue {
      NoValue = 0,
      TextViewFont = 1
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

   QByteArray mainWindowGeometry() const;
   void setMainWindowGeometry(const QByteArray &geometry);

   QByteArray mainWindowState() const;
   void setMainWindowState(const QByteArray &state);

private:
   QStringList highlightingListToStringList(const QList<HighlightingRule> &rules) const;
   QList<HighlightingRule> highlightingStringListToList(const QStringList &array) const;
   QSettings m_settings;
};

Q_DECLARE_METATYPE(Settings::SettingValue)

typedef QSharedPointer<Settings> ApplicationSettings;

#endif // SETTINGS_H
