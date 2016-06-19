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

QTEST_MAIN(FilterGroupTest)

#include "tst_FilterGroupTest.moc"
