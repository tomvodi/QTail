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
#include <QScrollBar>
#include <TestCommon.h>

#include <gui/file_views/PlainTextViewWidget.h>
#include <ui_PlainTextViewWidget.h>

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
   void testLineWrap();

private:
   void appendLinesToTextViewWidget(PlainTextViewWidget &widget, int lineCount);
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
   PlainTextViewWidget viewWidget;
   QVERIFY2(viewWidget.ui->plainTextEdit->isReadOnly(), "Text view not read only");
}

void PlainTextViewWidgetTest::testAppendPlainText()
{
   QString testText("test test");
   PlainTextViewWidget viewWidget;
   viewWidget.appendPlainText(testText);
   QVERIFY2(viewWidget.ui->plainTextEdit->toPlainText() == testText, "Text wasn't appended.");
}

void PlainTextViewWidgetTest::testToPlainText()
{
   QString testText("test test");
   PlainTextViewWidget viewWidget;
   viewWidget.ui->plainTextEdit->appendPlainText(testText);
   QVERIFY2(viewWidget.toPlainText() == testText, "Text wasn't returned.");
}

void PlainTextViewWidgetTest::testClear()
{
   QString testText("test test");
   PlainTextViewWidget viewWidget;
   viewWidget.ui->plainTextEdit->appendPlainText(testText);
   viewWidget.clear();
   QVERIFY2(viewWidget.ui->plainTextEdit->toPlainText().isEmpty(), "Text wasn't cleared.");
}

void PlainTextViewWidgetTest::testLineWrap()
{
   bool lineWrapOn = false;
   PlainTextViewWidget viewWidget;
   viewWidget.setLineWrapOn(lineWrapOn);
   QVERIFY2(viewWidget.lineWrapOn() == lineWrapOn, "Wrong line wrap value returned");
   QVERIFY2(viewWidget.ui->plainTextEdit->lineWrapMode() == QPlainTextEdit::NoWrap, "Failed settings line wrap on text edit");

   lineWrapOn = true;
   viewWidget.setLineWrapOn(lineWrapOn);
   QVERIFY2(viewWidget.lineWrapOn() == lineWrapOn, "Wrong toggled line wrap value returned");
   QVERIFY2(viewWidget.ui->plainTextEdit->lineWrapMode() == QPlainTextEdit::WidgetWidth, "Failed settings toggled line wrap on text edit");
}

void PlainTextViewWidgetTest::appendLinesToTextViewWidget(PlainTextViewWidget &widget, int lineCount)
{
   for (int i = 0; i < lineCount; ++i) {
      widget.appendPlainText("This is a new line of text.");
   }
}

QTEST_MAIN(PlainTextViewWidgetTest)

#include "tst_PlainTextViewWidgetTest.moc"
