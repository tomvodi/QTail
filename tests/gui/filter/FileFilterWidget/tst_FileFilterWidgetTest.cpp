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
   void testSetFilterGroupsDefault();
   void testSetActiveFilterIds();
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

void FileFilterWidgetTest::testSetFilterGroupsDefault()
{
   FileFilterWidget widget;

   FilterGroup group("Test Group");
   FilterRule rule("Test Rule");
   group.addFilterRule(rule);

   widget.setFilterGroups({group});

   QVERIFY2(widget.ui->treeWidget->topLevelItemCount() == 1, "Group wasn't added to tree widget");
   QVERIFY2(widget.ui->treeWidget->topLevelItem(0)->childCount() == 1, "Rule wasn't added to tree widget");

   QTreeWidgetItemIterator it(widget.ui->treeWidget);
   bool atLeastOneItemIsChecked = false;
   while (*it) {
      if ((*it)->checkState(0) == Qt::Checked) {
         atLeastOneItemIsChecked = true;
         break;
      }
      ++it;
   }

   QVERIFY2(!atLeastOneItemIsChecked, "At least one item is checked");
}

void FileFilterWidgetTest::testSetActiveFilterIds()
{
   FileFilterWidget widget;

   FilterGroup group("Test Group");
   FilterRule rule("Test Rule");
   FilterRule rule2("Test Rule 2");
   group.addFilterRule(rule);
   group.addFilterRule(rule2);

   widget.setFilterGroups({group});
   widget.setActiveFilterIds({rule2.id()});

   QVERIFY2(widget.ui->treeWidget->topLevelItemCount() == 1, "Group wasn't added to tree widget");
   QList<QTreeWidgetItem*> ruleItem = widget.ui->treeWidget->findItems(rule2.filter(), Qt::MatchRecursive);
   Q_ASSERT(ruleItem.count());

   QVERIFY2(ruleItem.at(0)->checkState(0) == Qt::Checked, "Active rule wasn't checked");
}

QTEST_MAIN(FileFilterWidgetTest)

#include "tst_FileFilterWidgetTest.moc"
