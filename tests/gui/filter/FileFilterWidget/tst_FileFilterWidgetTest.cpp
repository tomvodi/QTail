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
   void testActiveFilterIdsAfterSettingFilterGroups();
   void testEmitActiveFilterIdsChanged();
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

/*!
 * \brief FileFilterWidgetTest::testActiveFilterIdsAfterSettingFilterGroups
 * If this happened:
 * - FilterGroups were set
 * - Some filters were activated (checked)
 * - New FilterGroups were set
 * The previously activated filter rules with the same id must be still activated.
 */
void FileFilterWidgetTest::testActiveFilterIdsAfterSettingFilterGroups()
{
   FileFilterWidget widget;

   FilterGroup defaultGroup("Test Group");
   FilterRule rule1("Test Rule");
   FilterRule activeRule("Test Rule 2");
   defaultGroup.addFilterRule(rule1);
   defaultGroup.addFilterRule(activeRule);

   widget.setFilterGroups({defaultGroup});
   widget.setActiveFilterIds({activeRule.id()});

   FilterGroup newGroup("Overwrite Group");
   newGroup.addFilterRule(FilterRule("New first rule"));
   newGroup.addFilterRule(FilterRule("A new second rule"));
   newGroup.addFilterRule(activeRule);

   widget.setFilterGroups({newGroup});

   QList<QTreeWidgetItem*> ruleItem = widget.ui->treeWidget->findItems(activeRule.filter(), Qt::MatchRecursive);
   Q_ASSERT(ruleItem.count());

   QVERIFY2(ruleItem.at(0)->checkState(0) == Qt::Checked, "Active rule has been unchecked after setting new filter groups");
}

/*!
 * \brief FileFilterWidgetTest::testEmitActiveFilterIdsChanged
 * Adding an active rule view code and activating a rule via gui.
 * After that, a click on the apply filters button should result in a list with
 * both ids, the filter id of the previously activated item and the item selected in
 * the ui.
 */
void FileFilterWidgetTest::testEmitActiveFilterIdsChanged()
{
   FileFilterWidget widget;
   QSignalSpy spy(&widget, SIGNAL(activeFilterIdsChanged(QList<QUuid>)));

   FilterGroup group("Test Group");
   FilterRule rule("Test Rule");
   FilterRule codeActiveRule("Test Rule 2");
   FilterRule uiActiveRule("Test Rule UI");
   group.addFilterRule(rule);
   group.addFilterRule(codeActiveRule);
   group.addFilterRule(uiActiveRule);

   widget.setFilterGroups({group});
   widget.setActiveFilterIds({codeActiveRule.id()});

   QList<QTreeWidgetItem*> ruleItems = widget.ui->treeWidget->findItems(uiActiveRule.filter(), Qt::MatchRecursive);
   Q_ASSERT(ruleItems.count());
   ruleItems.at(0)->setCheckState(0, Qt::Checked);

   widget.ui->applyFiltersButton->clicked();
   QVERIFY2(spy.count() == 1, "active filter ids changed signal wasn't emitted.");
   QVariantList parameters = spy.at(0);
   QList<QUuid> activeFilters = parameters.at(0).value<QList<QUuid> >();
   QVERIFY2(activeFilters.count() == 2, "Not all active filters were in the emitted parameter");
}

QTEST_MAIN(FileFilterWidgetTest)

#include "tst_FileFilterWidgetTest.moc"
