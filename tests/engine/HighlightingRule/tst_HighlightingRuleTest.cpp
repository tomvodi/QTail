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

QTEST_MAIN(HighlightingRuleTest)

#include "tst_HighlightingRuleTest.moc"
