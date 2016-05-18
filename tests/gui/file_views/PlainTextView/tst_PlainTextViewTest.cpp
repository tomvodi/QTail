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
#include <gui/file_views/PlainTextViewWidget.h>

class PlainTextViewTest : public QObject
{
   Q_OBJECT

public:
   PlainTextViewTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testFeatures();
   void testAppendLine();
   void testAppendLines();
   void testClear();
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

void PlainTextViewTest::testAppendLine()
{
   PlainTextView textView;
   auto textEdit = textView.m_textEdit;

   QString testLine(QStringLiteral("This is a test line"));
   textView.appendLine(testLine);

   QVERIFY2(textEdit->toPlainText() == testLine, "Test line wasn't added.");
}

void PlainTextViewTest::testAppendLines()
{
   PlainTextView textView;
   auto textEdit = textView.m_textEdit;

   QString testLine1(QStringLiteral("This is a test line"));
   QString testLine2(QStringLiteral("This is a second test line"));
   textView.appendLines({testLine1, testLine2});

   QVERIFY2(textEdit->toPlainText() == testLine1 + '\n' + testLine2, "Test lines weren't added.");
}

void PlainTextViewTest::testClear()
{
   PlainTextView textView;
   auto textEdit = textView.m_textEdit;

   textEdit->appendPlainText("This is some plain text");
   textView.clearTextView();

   QVERIFY2(textEdit->toPlainText().isEmpty(), "Text edit wasn't cleared.");
}

QTEST_MAIN(PlainTextViewTest)

#include "tst_PlainTextViewTest.moc"
