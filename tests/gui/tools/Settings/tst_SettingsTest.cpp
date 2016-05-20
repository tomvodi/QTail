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

#include <gui/tools/Settings.h>
#include <include/HighlightingRule.h>
#include <TestCommon.h>

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

QTEST_MAIN(SettingsTest)

#include "tst_SettingsTest.moc"
