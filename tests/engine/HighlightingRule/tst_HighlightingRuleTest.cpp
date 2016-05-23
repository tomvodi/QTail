/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <include/HighlightingRule.h>
#include <TestCommon.h>

class HighlightingRuleTest : public QObject
{
   Q_OBJECT

public:
   HighlightingRuleTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testSetterAndGetter();
   void testToAndFromJson();
   void testSerializationAndDeserialization();
};

HighlightingRuleTest::HighlightingRuleTest()
{
}

void HighlightingRuleTest::initTestCase()
{
}

void HighlightingRuleTest::cleanupTestCase()
{
}

void HighlightingRuleTest::testSetterAndGetter()
{
   QFont testFont = TestCommon::testFont();
   QColor foregroundColor(Qt::blue);
   QColor backgroundColor(Qt::yellow);
   QString testText("test text");

   HighlightingRule rule;

   rule.setFont(testFont);
   QVERIFY2(rule.font() == testFont, "Failed set/get font");

   rule.setForegroundColor(foregroundColor);
   QVERIFY2(rule.foregroundColor() == foregroundColor, "Failed set/get foregroundColor");

   rule.setBackgroundColor(backgroundColor);
   QVERIFY2(rule.backgroundColor() == backgroundColor, "Failed set/get backgroundColor");

   rule.setText(testText);
   QVERIFY2(rule.text() == testText, "Failed set/get text");

   Qt::CaseSensitivity caseSensitivity((rule.caseSensitivity() == Qt::CaseSensitive ? Qt::CaseInsensitive : Qt::CaseSensitive));
   rule.setCaseSensitivity(caseSensitivity);
   QVERIFY2(rule.caseSensitivity() == caseSensitivity, "Failed set/get caseSensitivity");
}

void HighlightingRuleTest::testToAndFromJson()
{
   QFont testFont = TestCommon::testFont();
   QColor foregroundColor(Qt::blue);
   QColor backgroundColor(Qt::yellow);
   QString testText("test text");

   HighlightingRule rule;
   rule.setFont(testFont);
   rule.setForegroundColor(foregroundColor);
   rule.setBackgroundColor(backgroundColor);
   rule.setText(testText);
   Qt::CaseSensitivity caseSensitivity((rule.caseSensitivity() == Qt::CaseSensitive ? Qt::CaseInsensitive : Qt::CaseSensitive));
   rule.setCaseSensitivity(caseSensitivity);

   QJsonObject json = rule.toJson();

   HighlightingRule deserializedRule;
   deserializedRule.fromJson(json);

   QVERIFY2(rule == deserializedRule, "Failed serialize and deserialize rule");
}

void HighlightingRuleTest::testSerializationAndDeserialization()
{
   QFont testFont = TestCommon::testFont();
   QColor foregroundColor(Qt::blue);
   QColor backgroundColor(Qt::yellow);
   QString testText("test text");

   HighlightingRule rule;
   rule.setFont(testFont);
   rule.setForegroundColor(foregroundColor);
   rule.setBackgroundColor(backgroundColor);
   rule.setText(testText);
   Qt::CaseSensitivity caseSensitivity((rule.caseSensitivity() == Qt::CaseSensitive ? Qt::CaseInsensitive : Qt::CaseSensitive));
   rule.setCaseSensitivity(caseSensitivity);

   QByteArray data;
   QDataStream writeStream(&data, QIODevice::WriteOnly);

   // Serialize
   writeStream << rule;

   // Deserialize
   QDataStream readStream(&data, QIODevice::ReadOnly);
   HighlightingRule deserializedRule;
   readStream >> deserializedRule;

   QVERIFY2(deserializedRule == rule, "Failed serializing/deserializing rule");
}

QTEST_MAIN(HighlightingRuleTest)

#include "tst_HighlightingRuleTest.moc"
