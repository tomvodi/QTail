/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QString>
#include <QtTest>
#include <gui/tools/OpenFileSettings.h>

class OpenFileSettingsTest : public QObject
{
   Q_OBJECT

public:
   OpenFileSettingsTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testActiveFilterIds();
   void testToAndFromStream();
};

OpenFileSettingsTest::OpenFileSettingsTest()
{
}

void OpenFileSettingsTest::initTestCase()
{
}

void OpenFileSettingsTest::cleanupTestCase()
{
}

void OpenFileSettingsTest::testActiveFilterIds()
{
   OpenFileSettings settings;

   QList<QUuid> activeIds({QUuid::createUuid(), QUuid::createUuid()});
   settings.setActiveFilterIds(activeIds);
   QVERIFY2(settings.activeFilterIds() == activeIds, "Failed set/get active ids");
}

void OpenFileSettingsTest::testToAndFromStream()
{
   OpenFileSettings settingsOut;
   settingsOut.setActiveFilterIds({QUuid::createUuid(), QUuid::createUuid()});

   QByteArray dataOut;
   QDataStream streamOut(&dataOut, QIODevice::ReadWrite);
   streamOut << settingsOut;

   QDataStream streamIn(&dataOut, QIODevice::ReadOnly);

   OpenFileSettings settingsIn;
   streamIn >> settingsIn;

   QVERIFY2(settingsOut == settingsIn, "Streamed settings aren't deserialized correctly");
}

QTEST_APPLESS_MAIN(OpenFileSettingsTest)

#include "tst_OpenFileSettingsTest.moc"
