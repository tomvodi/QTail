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


}

QTEST_MAIN(FilterDialogTest)

#include "tst_FilterDialogTest.moc"
