/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QDebug>
#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QScrollBar>

#include <gui/file_views/PlainTextEdit.h>
#include "ui_PlainTextEdit.h"

class PlainTextEditTest : public QObject
{
   Q_OBJECT

public:
   PlainTextEditTest();

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
   void appendLinesToTextEdit(QPlainTextEdit *textEdit, int lineCount);
};

PlainTextEditTest::PlainTextEditTest()
{
}

void PlainTextEditTest::initTestCase()
{
}

void PlainTextEditTest::cleanupTestCase()
{
}

void PlainTextEditTest::testSetup()
{
   PlainTextViewWidget textEdit;
   QVERIFY2(textEdit.ui->plainTextEdit->isReadOnly(), "Text edit isn't read only");
   QVERIFY2(textEdit.ui->plainTextEdit->centerOnScroll(), "Text isn't centered on scroll");
   QVERIFY2(textEdit.ui->followTailCheckBox->isChecked() == false, "Text isn't centered on scroll");
}

void PlainTextEditTest::testAppendPlainText()
{
   QString testText("testestest");
   PlainTextViewWidget textEdit;
   textEdit.appendPlainText(testText);
   QVERIFY2(textEdit.ui->plainTextEdit->toPlainText() == testText, "Plain text wasn't added to text edit");
}

void PlainTextEditTest::testToPlainText()
{
   QString testText("testestest");
   PlainTextViewWidget textEdit;
   textEdit.ui->plainTextEdit->setPlainText(testText);
   QVERIFY2(textEdit.toPlainText() == testText, "Plain text wasn't returned from text edit");
}

void PlainTextEditTest::testClear()
{
   QString testText("testestest");
   PlainTextViewWidget textEdit;
   textEdit.ui->plainTextEdit->setPlainText(testText);

   textEdit.clear();

   QVERIFY2(textEdit.ui->plainTextEdit->toPlainText().isEmpty(), "Plain text edit wasn't cleared");
}

void PlainTextEditTest::testScrollBar()
{
   QSKIP("Only for fiddling around with text edit");
   PlainTextViewWidget plainTextEdit;
   QPlainTextEdit *textEdit = plainTextEdit.ui->plainTextEdit;
   QScrollBar *verticalScrollBar = textEdit->verticalScrollBar();
   connect(verticalScrollBar, &QScrollBar::valueChanged,
           [this] (int value) {
      qDebug() << "Value changed: " << value;
   });

   appendLinesToTextEdit(textEdit, 5000);

   verticalScrollBar->setValue(verticalScrollBar->maximum() / 2 );
}

/*!
 * \brief PlainTextEditTest::testScrollBarOnNotFollowTail
 * If set to not follow tail, appending lines should not result in scrolling down to
 * bottom of file.
 */
void PlainTextEditTest::testScrollBarOnNotFollowTail()
{
   PlainTextViewWidget plainTextEdit;
   plainTextEdit.show(); // Show plain text edit in order to force scrolling of text area
   QPlainTextEdit *textEdit = plainTextEdit.ui->plainTextEdit;
   QScrollBar *verticalScrollBar = textEdit->verticalScrollBar();

   plainTextEdit.ui->followTailCheckBox->setChecked(false);
   appendLinesToTextEdit(textEdit, 1000);

   QVERIFY2(verticalScrollBar->value() == 0, "Text edit was scrolled down by appending text.");
}

void PlainTextEditTest::appendLinesToTextEdit(QPlainTextEdit *textEdit, int lineCount)
{
   for (int i = 0; i < lineCount; ++i) {
      textEdit->appendPlainText("new line");
   }
}

QTEST_MAIN(PlainTextEditTest)

#include "tst_PlainTextEditTest.moc"
