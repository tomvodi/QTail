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

#include <filter/FileFilterWidget.h>
#include <include/FilterGroup.h>

#include <ui_FileFilterWidget.h>

class FileFilterWidgetTest : public QObject
{
   Q_OBJECT

public:
   FileFilterWidgetTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testSetFilterGroups();
};

FileFilterWidgetTest::FileFilterWidgetTest()
{
}

void FileFilterWidgetTest::initTestCase()
{
}

void FileFilterWidgetTest::cleanupTestCase()
{
}

void FileFilterWidgetTest::testSetFilterGroups()
{
   FileFilterWidget widget;

   FilterGroup group("Test Group");
   FilterRule rule("Test Rule");
   group.addFilterRule(rule);

   widget.setFilterGroups({group});

   QVERIFY2(widget.ui->treeWidget->topLevelItemCount() == 1, "Group wasn't added to tree widget");
   QVERIFY2(widget.ui->treeWidget->topLevelItem(0)->childCount() == 1, "Rule wasn't added to tree widget");
}

QTEST_MAIN(FileFilterWidgetTest)

#include "tst_FileFilterWidgetTest.moc"
