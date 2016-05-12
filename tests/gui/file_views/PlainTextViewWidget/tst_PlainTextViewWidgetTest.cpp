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
   void testScrollBar();
   void testScrollBarOnNotFollowTail();

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

void PlainTextViewWidgetTest::testScrollBar()
{
   QSKIP("just for testing");
   // Just for fiddling around with text scrolling
   PlainTextViewWidget viewWidget;
   viewWidget.show();  // Only with show, the text area will scroll when new text is appended.
   QPlainTextEdit *textEdit = viewWidget.ui->plainTextEdit;
   QScrollBar *verticalScrollBar = textEdit->verticalScrollBar();

   qDebug() << "Scrollbar value: " << verticalScrollBar->value();

   appendLinesToTextViewWidget(viewWidget, 1000);

//   QCoreApplication::processEvents();

   qDebug() << "Scrollbar value: " << verticalScrollBar->value();
}

/*!
 * \brief PlainTextViewWidgetTest::testScrollBarOnNotFollowTail
 * Setting the not follow tail check box shouldn't result in scrolling down by appending text.
 */
void PlainTextViewWidgetTest::testScrollBarOnNotFollowTail()
{
   PlainTextViewWidget viewWidget;
   viewWidget.show();
   viewWidget.ui->followTailCheckBox->setChecked(true);

   QPlainTextEdit *textEdit = viewWidget.ui->plainTextEdit;
   QScrollBar *verticalScrollBar = textEdit->verticalScrollBar();

   appendLinesToTextViewWidget(viewWidget, 1000);

   QVERIFY2(verticalScrollBar->value() == 0, "Text view was scrolled despite no follow was set.");
}

void PlainTextViewWidgetTest::appendLinesToTextViewWidget(PlainTextViewWidget &widget, int lineCount)
{
   for (int i = 0; i < lineCount; ++i) {
      widget.appendPlainText("This is a new line of text.");
   }
}

QTEST_MAIN(PlainTextViewWidgetTest)

#include "tst_PlainTextViewWidgetTest.moc"
