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
   void testScrollBarOnNotFollowTail();
   void testScrollBarOnNotFollowStayInDocument();
   void testScrollAwayFromEndRemovesFollowTailOption();
   void testScrollToEndActivatesFollowTailOption();

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
   QVERIFY2(viewWidget.ui->followTailCheckBox->isChecked() == false, "Follow tail check box isn't set to false");
   QVERIFY2(viewWidget.ui->plainTextEdit->scrollEnabled() == false, "Follow tail isn't disabled in text edit.");
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

/*!
 * \brief PlainTextViewWidgetTest::testScrollBarOnNotFollowTail
 * Setting the not follow tail check box shouldn't result in scrolling down by appending text.
 */
void PlainTextViewWidgetTest::testScrollBarOnNotFollowTail()
{
   PlainTextViewWidget viewWidget;
   viewWidget.show();
   viewWidget.ui->followTailCheckBox->setChecked(false);

   QPlainTextEdit *textEdit = viewWidget.ui->plainTextEdit;
   QScrollBar *verticalScrollBar = textEdit->verticalScrollBar();

   appendLinesToTextViewWidget(viewWidget, 1000);

   QVERIFY2(verticalScrollBar->value() == 0, "Text view was scrolled despite no follow was set.");
}

void PlainTextViewWidgetTest::testScrollBarOnNotFollowStayInDocument()
{
   PlainTextViewWidget viewWidget;
   viewWidget.show();
   viewWidget.ui->followTailCheckBox->setChecked(true);

   QPlainTextEdit *textEdit = viewWidget.ui->plainTextEdit;
   QScrollBar *verticalScrollBar = textEdit->verticalScrollBar();

   // After appending a few lines with follow tail enabled, if follow tail is disabled,
   // the scrollbar value should stay the same when more lines will be appended
   appendLinesToTextViewWidget(viewWidget, 500);

   viewWidget.ui->followTailCheckBox->setChecked(false);

   int currentScrollPosition (verticalScrollBar->value());
   Q_ASSERT(currentScrollPosition != 0);

   appendLinesToTextViewWidget(viewWidget, 500);

   QVERIFY2(verticalScrollBar->value() == currentScrollPosition, "The text view was scrolled despite no follow tail is set.");
}

/*!
 * \brief PlainTextViewWidgetTest::testScrollAwayFromEndRemovesFollowTailOption
 * If currently the follow tail option is set, but the user scrolls upwards, the option
 * should be removed in order to freely scroll in the text edit.
 */
void PlainTextViewWidgetTest::testScrollAwayFromEndRemovesFollowTailOption()
{
   PlainTextViewWidget viewWidget;
   viewWidget.show();
   viewWidget.ui->followTailCheckBox->setChecked(true);

   QPlainTextEdit *textEdit = viewWidget.ui->plainTextEdit;
   QScrollBar *verticalScrollBar = textEdit->verticalScrollBar();

   appendLinesToTextViewWidget(viewWidget, 100);
   TestCommon::waitMsecs(100);

   int scrollMax = verticalScrollBar->maximum();
   int scrollValue = verticalScrollBar->value();
   QVERIFY2(scrollValue == scrollMax, "Text view wasn't scrolled to end.");

   verticalScrollBar->setValue(verticalScrollBar->value() - 1);

   QVERIFY2(viewWidget.ui->followTailCheckBox->isChecked() == false,
            "Follow tail wasn't disabled on scrolling away from end");
}

void PlainTextViewWidgetTest::testScrollToEndActivatesFollowTailOption()
{
   PlainTextViewWidget viewWidget;
   viewWidget.show();
   viewWidget.ui->followTailCheckBox->setChecked(false);

   QPlainTextEdit *textEdit = viewWidget.ui->plainTextEdit;
   QScrollBar *verticalScrollBar = textEdit->verticalScrollBar();

   appendLinesToTextViewWidget(viewWidget, 100);
   TestCommon::waitMsecs(100);

   int scrollValue = verticalScrollBar->value();
   QVERIFY2(scrollValue == 0, "Text view was scrolled despite no follow option.");

   verticalScrollBar->setValue(verticalScrollBar->maximum());

   QVERIFY2(viewWidget.ui->followTailCheckBox->isChecked() == true,
            "Follow tail wasn't enabled on scrolling to end");
}

void PlainTextViewWidgetTest::appendLinesToTextViewWidget(PlainTextViewWidget &widget, int lineCount)
{
   for (int i = 0; i < lineCount; ++i) {
      widget.appendPlainText("This is a new line of text.");
   }
}

QTEST_MAIN(PlainTextViewWidgetTest)

#include "tst_PlainTextViewWidgetTest.moc"
