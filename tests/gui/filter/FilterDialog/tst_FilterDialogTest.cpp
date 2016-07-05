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
#include <TestCommon.h>

#include <filter/FilterDialog.h>
#include <include/FilterGroup.h>

#include <ui_FilterDialog.h>

class FilterDialogTest : public QObject
{
   Q_OBJECT

public:
   FilterDialogTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testDefaultDialog();
   void testSetFilterGroups();
   void testSetCurrentGroupName();
   void testAddGroupWithName();
   void testAddFilter();
   void testEditCurrentItem();
   void testFilterListWhenChangingGroup();
   void testAddFilterRuleItem();
   void teston_addFilterButton_clicked();
};

FilterDialogTest::FilterDialogTest()
{
}

void FilterDialogTest::initTestCase()
{
}

void FilterDialogTest::cleanupTestCase()
{
}

void FilterDialogTest::testDefaultDialog()
{
   FilterDialog dialog;

   // A default dialog must contain at least one filter group
   QVERIFY2(dialog.ui->filterGroupComboBox->count() == 1, "No default rule in list");
}

void FilterDialogTest::testSetFilterGroups()
{
   QList<FilterGroup> filterGroups;
   FilterGroup filterGroup1("Filter group 1");
   FilterRule filterRule1("FilterRule 1");
   FilterRule filterRule2("FilterRule 2");
   filterGroup1.setFilterRules({filterRule1, filterRule2});
   FilterGroup filterGroup2("Filter groups 2");
   filterGroups << filterGroup1 << filterGroup2;

   FilterDialog dialog;
   dialog.setFilterGroups(filterGroups);

   QVERIFY2(dialog.ui->filterGroupComboBox->count() == filterGroups.count(),
            "Not all filter groups were added to list");
   QVERIFY2(dialog.ui->filterGroupComboBox->currentText() == "Filter group 1",
            "Wrong selected filter group");
   QVERIFY2(dialog.ui->filtersListWidget->count(), "No filters of the current group visible");
   QVERIFY2(dialog.ui->filtersListWidget->count() == 2,
            "Not exactly two filters of the current group visible");
   QVERIFY2(dialog.ui->filtersListWidget->item(0)->text() == filterRule1.filter(),
            "Filter rules were added in wrong order");
}

void FilterDialogTest::testSetCurrentGroupName()
{
   QList<FilterGroup> filterGroups;
   filterGroups.append(FilterGroup("Filter group 1"));
   filterGroups.append(FilterGroup("Filter groups 2"));

   FilterDialog dialog;
   dialog.setFilterGroups(filterGroups);

   dialog.setCurrentGroupName("Test name");
   QVERIFY2(dialog.ui->filterGroupComboBox->currentText() == "Test name",
            "Current group name wasn't changed");
}

void FilterDialogTest::testAddGroupWithName()
{
   QList<FilterGroup> filterGroups;
   filterGroups.append(FilterGroup("Filter group 1"));
   filterGroups.append(FilterGroup("Filter groups 2"));

    FilterDialog dialog;
    dialog.setFilterGroups(filterGroups);

    QString newGroupName("New filter group");
    dialog.addGroup(newGroupName);

    QVERIFY2(dialog.ui->filterGroupComboBox->count() == 3, "New group wasn't added.");
    QVERIFY2(dialog.ui->filterGroupComboBox->currentText() == newGroupName,
             "New group isn't current item");

    // Check if it is possible to add groups with the same name
    dialog.addGroup(newGroupName);
    QVERIFY2(dialog.ui->filterGroupComboBox->count() == 4, "Duplicate group wasn't added.");
}

void FilterDialogTest::testAddFilter()
{
   FilterDialog dialog;
   QString testText("test text");
   dialog.ui->regexLineEdit->setText(testText);
   dialog.ui->caseSensitiveCheckBox->setChecked(true);

   dialog.ui->addFilterButton->click();
   QVERIFY2(dialog.ui->filtersListWidget->count() == 1, "No filter was added with add button");
   QVERIFY2(dialog.ui->filtersListWidget->item(0)->text() == testText, "Added filter hasn't right text");
   QVERIFY2(dialog.ui->filtersListWidget->currentRow() == 0, "Added filter isn't current item");
   QListWidgetItem *currentItem = dialog.ui->filtersListWidget->currentItem();
   Q_ASSERT(currentItem);

   bool currentItemCaseSensitive = currentItem->data(FilterDialog::CaseSensitiveDataRole).toBool();
   QVERIFY2(currentItemCaseSensitive == true, "Case sensitive data wasn't set from checbox.");
   QVERIFY2(currentItem->flags().testFlag(Qt::ItemIsEditable), "New item isn't editable");
}

void FilterDialogTest::testEditCurrentItem()
{
   FilterDialog dialog;
   dialog.ui->regexLineEdit->setText("default text");
   dialog.ui->caseSensitiveCheckBox->setChecked(true);

   dialog.on_addFilterButton_clicked();

   // Changing the current item through line edit and checkbox
   Q_ASSERT(dialog.ui->filtersListWidget->currentItem());
   QString testText("test text");
   bool newCaseValue = !dialog.ui->caseSensitiveCheckBox->isChecked();
   dialog.ui->regexLineEdit->setText(testText);
   dialog.ui->regexLineEdit->editingFinished();
   dialog.ui->caseSensitiveCheckBox->setChecked(newCaseValue);

   QListWidgetItem *currentItem = dialog.ui->filtersListWidget->currentItem();
   Q_ASSERT(currentItem);

   QVERIFY2(currentItem->text() == testText, "Text wasn't set from line edit to list item");

   bool currentItemCaseSensitive = currentItem->data(FilterDialog::CaseSensitiveDataRole).toBool();
   QVERIFY2(currentItemCaseSensitive == newCaseValue, "Case sensitive wasn't set in list item");

   // Edit the item text directly should result in changing the text in regex line edit
   QString newText("new new new");
   currentItem->setText(newText);
   QVERIFY2(dialog.ui->regexLineEdit->text() == newText,
            "Editing item text doesn't change regex line edit text");
}

/*!
 * \brief FilterDialogTest::testFilterListWhenChangingGroup
 * Every group has a list of filters assigned to it. Changing the selected group
 * should show the group's filters in the list.
 */
void FilterDialogTest::testFilterListWhenChangingGroup()
{
   QList<FilterGroup> filterGroups;
   FilterGroup filterGroup1("Filter group 1");
   FilterRule filterRule1("FilterRule 1");
   FilterRule filterRule2("FilterRule 2");
   filterGroup1.setFilterRules({filterRule1, filterRule2});
   FilterGroup filterGroup2("Filter groups 2");
   FilterRule filterRule3("FilterRule 3");
   FilterRule filterRule4("FilterRule 4");
   filterGroup2.setFilterRules({filterRule3, filterRule4});
   filterGroups << filterGroup1 << filterGroup2;

   FilterDialog dialog;
   dialog.setFilterGroups(filterGroups);

   dialog.ui->filterGroupComboBox->setCurrentIndex(1);
   Q_ASSERT(dialog.ui->filterGroupComboBox->currentText() == filterGroup2.name());

   QVERIFY2(dialog.ui->filtersListWidget->count() == 2, "Wrong item count after changing filter group");
   QVERIFY2(dialog.ui->filtersListWidget->item(0)->text() == filterRule3.filter(),
            "Wrong text of first filter rule after changing group");
   QVERIFY2(dialog.ui->filtersListWidget->item(1)->text() == filterRule4.filter(),
            "Wrong text of second filter rule after changing group");

   dialog.ui->filterGroupComboBox->setCurrentIndex(0);

   QVERIFY2(dialog.ui->filterGroupComboBox->currentText() == filterGroup1.name(), "Group wasn't changed");
   QVERIFY2(dialog.ui->filtersListWidget->count(), "No item count after changing filter group");
   QVERIFY2(dialog.ui->filtersListWidget->count() == 2, "Wrong item count after changing filter group");
   QVERIFY2(dialog.ui->filtersListWidget->item(0)->text() == filterRule1.filter(),
            "Wrong text of first filter rule after changing group");
   QVERIFY2(dialog.ui->filtersListWidget->item(1)->text() == filterRule2.filter(),
            "Wrong text of second filter rule after changing group");
}

void FilterDialogTest::testAddFilterRuleItem()
{
   QList<FilterGroup> filterGroups;
   FilterGroup filterGroup1("Filter group 1");
   FilterRule filterRule1("FilterRule 1");
   filterGroup1.setFilterRules({filterRule1});
   filterGroups << filterGroup1;

   FilterDialog dialog;
   dialog.setFilterGroups(filterGroups);
   Q_ASSERT(dialog.ui->filterGroupComboBox->currentText() == filterGroup1.name());
   Q_ASSERT(dialog.ui->filtersListWidget->count() == 1);

   FilterRule testRule;
   testRule.setFilter("test test test");

   dialog.addFilterRuleItem(testRule);
   QVERIFY2(dialog.ui->filtersListWidget->count() == 2, "Rule wasn't added to filter list widget");
   QVERIFY2(dialog.ui->filtersListWidget->currentItem()->text() == testRule.filter(),
            "New rule isn't set as current item");
}

void FilterDialogTest::teston_addFilterButton_clicked()
{
   QList<FilterGroup> filterGroups;
   FilterGroup filterGroup1("Filter group 1");
   FilterRule filterRule1("FilterRule 1");
   filterGroup1.setFilterRules({filterRule1});
   filterGroups << filterGroup1;

   FilterDialog dialog;
   dialog.setFilterGroups(filterGroups);

   Q_ASSERT(dialog.ui->filterGroupComboBox->currentText() == filterGroup1.name());
   Q_ASSERT(dialog.ui->filtersListWidget->count() == 1);

   FilterRule testRule;
   testRule.setFilter("test test test");

   dialog.ui->regexLineEdit->setText(testRule.filter());
   dialog.on_addFilterButton_clicked();

   QVERIFY2(dialog.ui->filtersListWidget->count() == 2, "New rule item wasn't added.");

   QVariant filterGroupData = dialog.ui->filterGroupComboBox->currentData();
   Q_ASSERT(filterGroupData.canConvert<FilterGroup>());
   FilterGroup groupFromCombobox = filterGroupData.value<FilterGroup>();
   QVERIFY2(groupFromCombobox.name() == filterGroup1.name(), "Wrong filter group from combobox");

   QVERIFY2(groupFromCombobox.filterRules().count(), "Filter group from combo box has no filter rules");
   QVERIFY2(groupFromCombobox.filterRules().count() == 2,
            "New filter rule wasn't added to group from combo box");

   filterGroup1.setFilterRules({filterRule1, testRule});
   QVERIFY2(groupFromCombobox.filterRules() == filterGroup1.filterRules(),
            "Filter rules don't match between group from combo box and test group");
}

QTEST_MAIN(FilterDialogTest)

#include "tst_FilterDialogTest.moc"
