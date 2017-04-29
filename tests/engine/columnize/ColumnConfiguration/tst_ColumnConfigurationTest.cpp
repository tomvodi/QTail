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

QTEST_APPLESS_MAIN(ColumnConfigurationTest)

#include "tst_ColumnConfigurationTest.moc"
