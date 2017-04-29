/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QString>
#include <QtTest>

#include <engine/include/columnize/DateTimeConfiguration.h>

class DateTimeConfigurationTest : public QObject
{
   Q_OBJECT

public:
   DateTimeConfigurationTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testType();
};

DateTimeConfigurationTest::DateTimeConfigurationTest()
{
}

void DateTimeConfigurationTest::initTestCase()
{
}

void DateTimeConfigurationTest::cleanupTestCase()
{
}

void DateTimeConfigurationTest::testType()
{
   DateTimeConfiguration config;
   QVERIFY(config.type() == ColumnType::DateTime);
}

QTEST_APPLESS_MAIN(DateTimeConfigurationTest)

#include "tst_DateTimeConfigurationTest.moc"
