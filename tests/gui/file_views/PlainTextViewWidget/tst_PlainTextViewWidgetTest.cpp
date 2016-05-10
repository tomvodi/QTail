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

class PlainTextViewWidgetTest : public QObject
{
   Q_OBJECT

public:
   PlainTextViewWidgetTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testSetup();
   void testAppendPlainText();
   void testToPlainText();
   void testClear();
   void testScrollBar();
   void testScrollBarOnNotFollowTail();
};

PlainTextViewWidgetTest::PlainTextViewWidgetTest()
{
}

void PlainTextViewWidgetTest::initTestCase()
{
}

void PlainTextViewWidgetTest::cleanupTestCase()
{
}

void PlainTextViewWidgetTest::testSetup()
{

}

void PlainTextViewWidgetTest::testAppendPlainText()
{

}

void PlainTextViewWidgetTest::testToPlainText()
{

}

void PlainTextViewWidgetTest::testClear()
{

}

void PlainTextViewWidgetTest::testScrollBar()
{

}

void PlainTextViewWidgetTest::testScrollBarOnNotFollowTail()
{

}

QTEST_MAIN(PlainTextViewWidgetTest)

#include "tst_PlainTextViewWidgetTest.moc"
