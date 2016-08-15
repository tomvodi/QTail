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
#include <QTextDocument>

#include <gui/file_views/PlainTextView.h>
#include <gui/file_views/PlainTextViewWidget.h>
#include <TestCommon.h>
#include <include/FilterRule.h>
#include <include/TextViewSettings.h>

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
   void testReadCompleteUntil();
   void testSetTextViewSettings();
   void testSetActiveFilterRules();
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

void PlainTextViewTest::testReadCompleteUntil()
{
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testReadCompleteUntil.log"));

   QString testFileContent("Test text\nTest line 2\nTest Line 3\n");
   QString testFileContent2("Test line 4\n");
   QFile outFile(filePath);
   outFile.open(QIODevice::WriteOnly);
   outFile.write(testFileContent.toUtf8());
   outFile.write(testFileContent2.toUtf8());
   outFile.close();

   TestCommon::waitMsecs(100);

   PlainTextView textView;
   QFileInfo fileInfo(filePath);
   textView.setFileInfo(fileInfo);

   textView.readCompleteFileUntil(testFileContent.length());
   QString textViewText = textView.m_textEdit->toPlainText();
   QVERIFY2(textViewText.count(), "No text in text loaded into text view");
   QVERIFY2(textViewText == testFileContent, "Too much or too less text was loaded into text view");
}

void PlainTextViewTest::testSetTextViewSettings()
{
   QFont testFont = TestCommon::testFont();

   PlainTextView textView;
   TextViewSettings settings;
   settings.setFont(testFont);
   settings.setLineWrapOn(!textView.m_textEdit->lineWrapOn());
   textView.setTextViewSettings(settings);

   QVERIFY2(textView.m_textDocument->defaultFont() == testFont, "Default font wasn't set.");
   QVERIFY2(textView.m_textEdit->lineWrapOn() == settings.lineWrapOn(), "Failed setting line wrap");
}

void PlainTextViewTest::testSetActiveFilterRules()
{
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testSetActiveFilterRules.log"));

   QString firstVisibleLine("Test line invisible (no match)");
   QString secondVisibleLine("Test line invisible 2 (no match)");
   QString firstLineFilterMatch(">> Filter match line");
   QString thirdVisibleLine("Test line invisible 3 (no match)");

   QStringList fileLines({firstVisibleLine, secondVisibleLine, firstLineFilterMatch, thirdVisibleLine});
   QFile outFile(filePath);
   outFile.open(QIODevice::WriteOnly);
   outFile.write(fileLines.join('\n').toUtf8());
   outFile.close();

   TestCommon::waitMsecs(100);

   PlainTextView textView;
   QFileInfo fileInfo(filePath);
   textView.setFileInfo(fileInfo);

   FilterRule filter;
   filter.setFilter(firstLineFilterMatch);
   textView.setActiveFilters({filter});

   textView.readCompleteFileUntil(fileInfo.size());
   Q_ASSERT(textView.m_textDocument->blockCount());

   qDebug() << "Block count: " << textView.m_textDocument->blockCount();
   QVERIFY2(textView.m_textDocument->blockCount() < 4, "No line was filtered out.");
   QVERIFY2(textView.m_textDocument->blockCount() == 1, "Line with filter match was filtered out.");
}

QTEST_MAIN(PlainTextViewTest)

#include "tst_PlainTextViewTest.moc"
