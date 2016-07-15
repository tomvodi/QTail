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

#include <include/FilterRule.h>

class FilterRuleTest : public QObject
{
   Q_OBJECT

public:
   FilterRuleTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testConstructor();
   void testSetGetFilter();
   void testSetGetCaseSensitivity();
   void testActive();
   void testToAndFromJson();
};

FilterRuleTest::FilterRuleTest()
{
}

void FilterRuleTest::initTestCase()
{
}

void FilterRuleTest::cleanupTestCase()
{
}

void FilterRuleTest::testConstructor()
{
   QString filter("blablabla");
   FilterRule rule(filter);

   QVERIFY2(rule.filter() == filter, "Failed set filter with constructor");
}

void FilterRuleTest::testSetGetFilter()
{
   QString filter("blablabla");
   FilterRule rule;
   rule.setFilter(filter);
   QVERIFY2(rule.filter() == filter, "Failed set/get filter");
}

void FilterRuleTest::testSetGetCaseSensitivity()
{
   FilterRule rule;
   QVERIFY2(rule.caseSensitivity() == Qt::CaseInsensitive,
            "Wrong default case sensitivity");

   rule.setCaseSensitivity(Qt::CaseSensitive);
   QVERIFY2(rule.caseSensitivity() == Qt::CaseSensitive, "Failed set/get case sensitivity");
}

void FilterRuleTest::testActive()
{
   FilterRule rule;
   QVERIFY2(rule.isActive(), "Default rule isn't active");

   rule.setActive(false);
   QVERIFY2(rule.isActive() == false, "Failed set/get rule active");
}

void FilterRuleTest::testToAndFromJson()
{
   FilterRule rule("Rule 1");
   rule.setActive(!rule.isActive());
   rule.setCaseSensitivity(rule.caseSensitivity() == Qt::CaseInsensitive ? Qt::CaseSensitive : Qt::CaseInsensitive);

   QJsonObject ruleJson = rule.toJson();

   QVERIFY2(! ruleJson.isEmpty(), "Empty json returned");
   FilterRule rule2;
   rule2.fromJson(ruleJson);

   QVERIFY2(rule == rule2, "Failed convert to and from json");
}

QTEST_MAIN(FilterRuleTest)

#include "tst_FilterRuleTest.moc"
