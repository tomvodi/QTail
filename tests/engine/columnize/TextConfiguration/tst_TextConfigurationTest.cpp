/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QString>
#include <QtTest>

#include <engine/include/columnize/TextConfiguration.h>

class TextConfigurationTest : public QObject
{
   Q_OBJECT

public:
   TextConfigurationTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testType();
};

TextConfigurationTest::TextConfigurationTest()
{
}

void TextConfigurationTest::initTestCase()
{
}

void TextConfigurationTest::cleanupTestCase()
{
}

void TextConfigurationTest::testType()
{
   TextConfiguration config;
   QVERIFY(config.type() == ColumnType::Text);
}

QTEST_APPLESS_MAIN(TextConfigurationTest)

#include "tst_TextConfigurationTest.moc"
