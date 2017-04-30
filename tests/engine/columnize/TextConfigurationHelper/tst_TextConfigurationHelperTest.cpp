/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QString>
#include <QtTest>

#include <engine/include/columnize/TextConfigurationHelper.h>

class TextConfigurationHelperTest : public QObject
{
   Q_OBJECT

public:
   TextConfigurationHelperTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testType();
};

TextConfigurationHelperTest::TextConfigurationHelperTest()
{
}

void TextConfigurationHelperTest::initTestCase()
{
}

void TextConfigurationHelperTest::cleanupTestCase()
{
}

void TextConfigurationHelperTest::testType()
{
   ColConfig colConfig(new ColumnConfiguration(ColumnType::Text));
   TextConfigurationHelper config(colConfig);
   QVERIFY(config.type() == ColumnType::Text);
}

QTEST_APPLESS_MAIN(TextConfigurationHelperTest)

#include "tst_TextConfigurationHelperTest.moc"
