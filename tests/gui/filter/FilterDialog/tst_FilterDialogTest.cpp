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
   void testFilterGroups();
   void testSetCurrentGroupName();
   void testAddGroupWithName();
   void testAddFilter();
   void testEditCurrentItem();
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

void FilterDialogTest::testFilterGroups()
{
   QList<FilterGroup> filterGroups;
   filterGroups.append(FilterGroup("Filter group 1"));
   filterGroups.append(FilterGroup("Filter groups 2"));

   FilterDialog dialog;
   dialog.setFilterGroups(filterGroups);

   QVERIFY2(dialog.ui->filterGroupComboBox->count() == filterGroups.count(),
            "Not all filter groups were added to list");
   QVERIFY2(dialog.ui->filterGroupComboBox->currentText() == "Filter group 1",
            "Wrong selected filter group");
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
    dialog.addGroupWithName(newGroupName);

    QVERIFY2(dialog.ui->filterGroupComboBox->count() == 3, "New group wasn't added.");
    QVERIFY2(dialog.ui->filterGroupComboBox->currentText() == newGroupName,
             "New group isn't current item");

    // Check if it is possible to add groups with the same name
    dialog.addGroupWithName(newGroupName);
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

   bool currentItemCaseSensitive = currentItem->data(FilterDialog::CaseSensitiveRole).toBool();
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
   dialog.ui->caseSensitiveCheckBox->setChecked(newCaseValue);

   QListWidgetItem *currentItem = dialog.ui->filtersListWidget->currentItem();
   Q_ASSERT(currentItem);

   QVERIFY2(currentItem->text() == testText, "Text wasn't set from line edit to list item");

   bool currentItemCaseSensitive = currentItem->data(FilterDialog::CaseSensitiveRole).toBool();
   QVERIFY2(currentItemCaseSensitive == newCaseValue, "Case sensitive wasn't set in list item");

   // Edit the item text directly should result in changing the text in regex line edit
   QString newText("new new new");
   currentItem->setText(newText);
   QVERIFY2(dialog.ui->regexLineEdit->text() == newText,
            "Editing item text doesn't change regex line edit text");
}

QTEST_MAIN(FilterDialogTest)

#include "tst_FilterDialogTest.moc"
