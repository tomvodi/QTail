/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QString>
#include <QtTest>

#include <engine/include/columnize/ColumnConfigurationHelper.h>

class ColumnConfigurationHelperTest : public QObject
{
   Q_OBJECT

public:
   ColumnConfigurationHelperTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testConstructor();
   void testSetGetType();
};

ColumnConfigurationHelperTest::ColumnConfigurationHelperTest()
{
}

void ColumnConfigurationHelperTest::initTestCase()
{
}

void ColumnConfigurationHelperTest::cleanupTestCase()
{
}

void ColumnConfigurationHelperTest::testConstructor()
{
   ColConfig config(new ColumnConfiguration);
   ColumnConfigurationHelper helper(config);

   QVERIFY(helper.columnConfiguration() == config);
}

void ColumnConfigurationHelperTest::testSetGetType()
{
   ColConfig config(new ColumnConfiguration);
   ColumnConfigurationHelper helper(config);

   helper.setType(ColumnType::Text);
   QVERIFY(helper.type() == ColumnType::Text);
}

QTEST_APPLESS_MAIN(ColumnConfigurationHelperTest)

#include "tst_ColumnConfigurationHelperTest.moc"
