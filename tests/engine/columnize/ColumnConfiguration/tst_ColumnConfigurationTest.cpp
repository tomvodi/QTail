/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QString>
#include <QtTest>

#include <engine/include/columnize/ColumnConfiguration.h>

class ColumnConfigurationTest : public QObject
{
   Q_OBJECT

public:
   ColumnConfigurationTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testType();
   void testTypeConstructor();
   void testSetTypeGetType();
   void testSetGetConfiguration();
};

ColumnConfigurationTest::ColumnConfigurationTest()
{
}

void ColumnConfigurationTest::initTestCase()
{
}

void ColumnConfigurationTest::cleanupTestCase()
{
}

void ColumnConfigurationTest::testType()
{
   ColumnConfiguration config;
   QVERIFY(config.type() == ColumnType::None);
}

void ColumnConfigurationTest::testTypeConstructor()
{
   ColumnConfiguration config(ColumnType::DateTime);
   QVERIFY(config.type() == ColumnType::DateTime);
}

void ColumnConfigurationTest::testSetTypeGetType()
{
   ColumnConfiguration config;
   QVERIFY(config.type() != ColumnType::Text);

   config.setType(ColumnType::Text);
   QVERIFY(config.type() == ColumnType::Text);
}

void ColumnConfigurationTest::testSetGetConfiguration()
{
   ColumnConfiguration config;
   QJsonObject testObject;
   testObject.insert("blabla", "testtest");

   config.setConfiguration(testObject);
   QVERIFY(config.configuration() == testObject);
}

QTEST_APPLESS_MAIN(ColumnConfigurationTest)

#include "tst_ColumnConfigurationTest.moc"
