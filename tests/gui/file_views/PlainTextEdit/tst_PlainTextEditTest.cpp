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
}

void PlainTextEditTest::appendLinesToPlainTextEdit(PlainTextEdit &textEdit, int lineCount)
{
   for (int i = 0; i < lineCount; ++i) {
      textEdit.appendPlainText("This is a new line of text.");
   }
}

QTEST_MAIN(PlainTextEditTest)

#include "tst_PlainTextEditTest.moc"
