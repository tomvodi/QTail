/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QString>
#include <QtTest>

#include <engine/include/columnize/DateTimeConfigurationHelper.h>

class DateTimeConfigurationHelperTest : public QObject
{
   Q_OBJECT

public:
   DateTimeConfigurationHelperTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testType();
};

DateTimeConfigurationHelperTest::DateTimeConfigurationHelperTest()
{
}

void DateTimeConfigurationHelperTest::initTestCase()
{
}

void DateTimeConfigurationHelperTest::cleanupTestCase()
{
}

void DateTimeConfigurationHelperTest::testType()
{
   ColConfig colConfig(new ColumnConfiguration(ColumnType::DateTime));
   DateTimeConfigurationHelper config(colConfig);
   QVERIFY(config.type() == ColumnType::DateTime);
}

QTEST_APPLESS_MAIN(DateTimeConfigurationHelperTest)

#include "tst_DateTimeConfigurationHelperTest.moc"
