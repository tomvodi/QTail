/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QString>
#include <QtTest>

#include <engine/include/columnize/SelectionConfiguration.h>

class SelectionConfigurationTest : public QObject
{
   Q_OBJECT

public:
   SelectionConfigurationTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testType();
};

SelectionConfigurationTest::SelectionConfigurationTest()
{
}

void SelectionConfigurationTest::initTestCase()
{
}

void SelectionConfigurationTest::cleanupTestCase()
{
}

void SelectionConfigurationTest::testType()
{
   SelectionConfiguration config;
   QVERIFY(config.type() == ColumnType::Selection);
}

QTEST_APPLESS_MAIN(SelectionConfigurationTest)

#include "tst_SelectionConfigurationTest.moc"
