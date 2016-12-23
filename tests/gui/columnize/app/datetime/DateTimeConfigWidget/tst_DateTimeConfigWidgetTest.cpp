/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QString>
#include <QtTest>
#include <QDebug>
#include <QCoreApplication>

#include <app/datetime/DateTimeConfigWidget.h>
#include <ui_DateTimeConfigWidget.h>

class DateTimeConfigWidgetTest : public QObject
{
   Q_OBJECT

public:
   DateTimeConfigWidgetTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testDefault();
   void testSetGetLocale();
};

DateTimeConfigWidgetTest::DateTimeConfigWidgetTest()
{
}

void DateTimeConfigWidgetTest::initTestCase()
{
}

void DateTimeConfigWidgetTest::cleanupTestCase()
{
}

void DateTimeConfigWidgetTest::testDefault()
{
   DateTimeConfigWidget widget;
}

void DateTimeConfigWidgetTest::testSetGetLocale()
{

}

QTEST_MAIN(DateTimeConfigWidgetTest)

#include "tst_DateTimeConfigWidgetTest.moc"
