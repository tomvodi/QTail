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

#include <gui/file_views/SearchBar.h>
#include <ui_SearchBar.h>

class SearchBarTest : public QObject
{
   Q_OBJECT

public:
   SearchBarTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testConstructor();
};

SearchBarTest::SearchBarTest()
{
}

void SearchBarTest::initTestCase()
{
}

void SearchBarTest::cleanupTestCase()
{
}

void SearchBarTest::testConstructor()
{
   SearchBar bar;
   QVERIFY2(bar.resultNumber() == 0, "Wrong default result number");
   QVERIFY2(bar.resultCount() == 0, "Wrong default result count");
}

QTEST_MAIN(SearchBarTest)

#include "tst_SearchBarTest.moc"
