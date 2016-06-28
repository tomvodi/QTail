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

#include <include/FilterGroup.h>

class FilterGroupTest : public QObject
{
   Q_OBJECT

public:
   FilterGroupTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testStringConstructor();
   void testSetGetName();
   void testSetGetFilterRules();
   void testAppendFilterRule();
};

FilterGroupTest::FilterGroupTest()
{
}

void FilterGroupTest::initTestCase()
{
}

void FilterGroupTest::cleanupTestCase()
{
}

void FilterGroupTest::testStringConstructor()
{
   QString testGroupName("Testgroup");
   FilterGroup group(testGroupName);

   QVERIFY2(group.name() == testGroupName, "Failed setting groupname through constructor");
}

void FilterGroupTest::testSetGetName()
{
   QString testGroupName("Testgroup");
   FilterGroup group;
   group.setName(testGroupName);

   QVERIFY2(group.name() == testGroupName, "Failed setting/getting groupname");
}

void FilterGroupTest::testSetGetFilterRules()
{
   FilterRule rule1("Rule 1");
   FilterRule rule2("Rule 2");
   QList<FilterRule> ruleList;
   ruleList << rule1 << rule2;

   FilterGroup group;
   group.setFilterRules(ruleList);
   QVERIFY2(group.filterRules() == ruleList, "Failed set/get rules");
}

void FilterGroupTest::testAppendFilterRule()
{
   FilterRule rule("Rule 1");

   FilterGroup group;
   group.addFilterRule(rule);
   QVERIFY2(group.filterRules().contains(rule), "Failed add rule");
}

QTEST_MAIN(FilterGroupTest)

#include "tst_FilterGroupTest.moc"
