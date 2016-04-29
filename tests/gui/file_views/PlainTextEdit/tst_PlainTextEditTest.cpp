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

QTEST_MAIN(PlainTextEditTest)

#include "tst_PlainTextEditTest.moc"
