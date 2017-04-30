/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QString>
#include <QtTest>

#include <engine/include/columnize/SelectionConfigurationHelper.h>

class SelectionConfigurationHelperTest : public QObject
{
   Q_OBJECT

public:
   SelectionConfigurationHelperTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testType();
};

SelectionConfigurationHelperTest::SelectionConfigurationHelperTest()
{
}

void SelectionConfigurationHelperTest::initTestCase()
{
}

void SelectionConfigurationHelperTest::cleanupTestCase()
{
}

void SelectionConfigurationHelperTest::testType()
{
   ColConfig colConfig(new ColumnConfiguration(ColumnType::Selection));
   SelectionConfigurationHelper config(colConfig);
   QVERIFY(config.type() == ColumnType::Selection);
}

QTEST_APPLESS_MAIN(SelectionConfigurationHelperTest)

#include "tst_SelectionConfigurationHelperTest.moc"
