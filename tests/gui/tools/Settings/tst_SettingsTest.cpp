/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QDebug>
#include <QString>
#include <QtTest>
#include <QList>
#include <QCoreApplication>
#include <QFontDatabase>

#include <gui/tools/Settings.h>
#include <include/FilterGroup.h>
#include <include/HighlightingRule.h>
#include <TestCommon.h>
#include <tools/OpenFileSettings.h>

class SettingsTest : public QObject
{
   Q_OBJECT

public:
   SettingsTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void init();
   void testLastOpenDir();
   void testLastOpenFiles();
   void testRecentlyOpenedFiles();
   void testSetHighlightingRules();
   void testTextViewFont();
   void testTextViewLineWrap();
   void testTextViewUpdateInterval();
   void testFilterGroups();
   void testOpenFileSettings();
};

SettingsTest::SettingsTest()
{
}

void SettingsTest::initTestCase()
{
   QCoreApplication::setOrganizationName("SettingsTest");
   QCoreApplication::setApplicationName("SettingsTest");
}

void SettingsTest::cleanupTestCase()
{
   QSettings settings;
   settings.clear();
   settings.sync();
}

void SettingsTest::init()
{
   QSettings settings;
   settings.clear();
   settings.sync();
}

void SettingsTest::testLastOpenDir()
{
   QDir testDir = QDir::homePath();

   Settings settings;
   settings.setLastOpenDir(testDir);
   settings.m_settings.sync();

   Settings settingsRead;
   QVERIFY2(settingsRead.lastOpenDir().absolutePath() == testDir.absolutePath(), "Failed setting/getting last open dir");
}

void SettingsTest::testLastOpenFiles()
{
   QStringList lastOpenFiles({ "file 1", "file 2"});

   Settings settings;
   settings.setLastOpenedFiles(lastOpenFiles);
   settings.m_settings.sync();

   Settings settingsRead;
   QVERIFY2(settingsRead.lastOpenedFiles() == lastOpenFiles, "Failed setting/getting last opened files");
}

void SettingsTest::testRecentlyOpenedFiles()
{
   QStringList recentlyOpenFiles({ "file 1", "file 2"});

   Settings settings;
   settings.setRecentlyOpenedFiles(recentlyOpenFiles);
   settings.m_settings.sync();

   Settings settingsRead;
   QVERIFY2(settingsRead.recentlyOpenedFiles() == recentlyOpenFiles, "Failed setting/getting recently opened files");
}

void SettingsTest::testSetHighlightingRules()
{
   HighlightingRule lineRule1;
   lineRule1.setText("Line rule 1");
   HighlightingRule lineRule2;
   lineRule2.setText("Line rule 2");
   HighlightingRule wordRule1;
   wordRule1.setText("Word rule 1");
   HighlightingRule wordRule2;
   wordRule2.setText("Word rule 2");

   QList<HighlightingRule> wordRules({wordRule1, wordRule2});
   QList<HighlightingRule> lineRules({lineRule1, lineRule2});

   Settings settings;
   settings.setHighlightingRules(lineRules, wordRules);
   settings.m_settings.sync();

   Settings settingsRead;

   QVERIFY2(settingsRead.wordHighlightingRules() == wordRules, "Failed setting/getting word rules");
   QVERIFY2(settingsRead.lineHighlightingRules() == lineRules, "Failed setting/getting line rules");
}

void SettingsTest::testTextViewFont()
{
   Settings settings;
   QFont defaultFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);

   QVERIFY2(settings.textViewFont() == defaultFont, "The wrong default text view font was returned.");

   QFont testFont = TestCommon::testFont();
   settings.setTextViewFont(testFont);
   QVERIFY2(settings.textViewFont() == testFont, "Failed setting/getting text view font");
}

void SettingsTest::testTextViewLineWrap()
{
   Settings settings;
   bool lineWrapOn = true;

   QVERIFY2(settings.textViewLineWrap() == lineWrapOn, "The wrong default text view line wrap value was returned.");

   lineWrapOn = !lineWrapOn;

   settings.setTextViewLineWrap(lineWrapOn);
   QVERIFY2(settings.textViewLineWrap() == lineWrapOn, "Failed setting/getting text view line wrap");
}

void SettingsTest::testTextViewUpdateInterval()
{
   Settings settings;

   int updateInterval = 250;

   QVERIFY2(settings.textViewUpdateIntervalMs() == updateInterval, "Wrong default update interval");

   updateInterval = 45342;
   settings.setTextViewUpdateIntervalMs(updateInterval);
   QVERIFY2(settings.textViewUpdateIntervalMs() == updateInterval, "Failed settings update interval");
}

void SettingsTest::testFilterGroups()
{
   QList<FilterGroup> groups;
   FilterGroup group;
   group.setName("Test group");
   FilterRule rule("test rule");
   group.setFilterRules({rule});
   groups.append(group);

   Settings settings;
   settings.setFilterGroups(groups);

   QVERIFY2(settings.filterGroups() == groups, "Failed save/restore filter groups");
}

void SettingsTest::testOpenFileSettings()
{
   QString fileName("file 1");
   OpenFileSettings fileSettings;
   fileSettings.setActiveFilterIds({QUuid::createUuid(), QUuid::createUuid()});

   Settings settings;
   settings.setOpenFileSettingsForFile(fileName, fileSettings);

   OpenFileSettings storedSettings = settings.openFileSettingsForFile(fileName);

   QVERIFY2(storedSettings == fileSettings, "Settings aren't the same as the stored ones");

   // Test remove
   settings.removeFileSettingsForFile(fileName);
   storedSettings = settings.openFileSettingsForFile(fileName);
   QVERIFY2(storedSettings == OpenFileSettings(), "Settings returned non empty file settings for removed settings");
}

QTEST_MAIN(SettingsTest)

#include "tst_SettingsTest.moc"
