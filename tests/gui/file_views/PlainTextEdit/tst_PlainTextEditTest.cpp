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

class PlainTextEditTest : public QObject
{
   Q_OBJECT

public:
   PlainTextEditTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testSetup();
   void testDisabledScroll();

private:
   void appendLinesToPlainTextEdit(PlainTextEdit &textEdit, int lineCount);
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
   PlainTextEdit textEdit;
   QVERIFY2(textEdit.isReadOnly(), "Text edit isn't read only");
   QVERIFY2(textEdit.scrollEnabled() == true, "Wrong default scroll enabled value");
}

void PlainTextEditTest::testDisabledScroll()
{
   PlainTextEdit textEdit;
   textEdit.show();

   textEdit.setScrollEnabled(false);
   appendLinesToPlainTextEdit(textEdit, 1000);

   QVERIFY2(textEdit.verticalScrollBar()->value() == 0, "Text view was scrolled to bottom by appending text");
}

void PlainTextEditTest::appendLinesToPlainTextEdit(PlainTextEdit &textEdit, int lineCount)
{
   for (int i = 0; i < lineCount; ++i) {
      textEdit.appendPlainText("This is a new line of text.");
   }
}

QTEST_MAIN(PlainTextEditTest)

#include "tst_PlainTextEditTest.moc"
