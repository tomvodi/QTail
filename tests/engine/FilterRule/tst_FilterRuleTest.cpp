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

QTEST_MAIN(FilterRuleTest)

#include "tst_FilterRuleTest.moc"
