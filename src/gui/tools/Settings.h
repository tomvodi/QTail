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

class HighlightingRule;

class Settings
{
   friend class SettingsTest;
public:
    Settings();

    void setLastOpenDir(const QDir &dir);
    QDir lastOpenDir() const;

    void setLastOpenedFiles(const QStringList &files);
    QStringList lastOpenedFiles() const;

    void setRecentlyOpenedFiles(const QStringList &files);
    QStringList recentlyOpenedFiles() const;

    void setHighlightingRules(const QList<HighlightingRule> &lineRules,
                              const QList<HighlightingRule> &wordRules);

    QList<HighlightingRule> wordRules() const;
    QList<HighlightingRule> lineRules() const;

private:
    QStringList highlightingListToStringList(const QList<HighlightingRule> &rules) const;
    QList<HighlightingRule> highlightingStringListToList(const QStringList &array) const;
    QSettings m_settings;
};

#endif // SETTINGS_H
