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

#include <gui/file_views/PlainTextView.h>

class PlainTextViewTest : public QObject
{
   Q_OBJECT

public:
   PlainTextViewTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testFeatures();
};

PlainTextViewTest::PlainTextViewTest()
{
}

void PlainTextViewTest::initTestCase()
{
}

void PlainTextViewTest::cleanupTestCase()
{
}

void PlainTextViewTest::testFeatures()
{
   PlainTextView textView;
   QVERIFY2(textView.viewFeatures().testFlag(FileViewInterface::HasTextView),
            "Text view doesn't have text view enabled.");
   QVERIFY2(!textView.viewFeatures().testFlag(FileViewInterface::HasStateView),
            "Text view has state view enabled.");
}

QTEST_MAIN(PlainTextViewTest)

#include "tst_PlainTextViewTest.moc"
