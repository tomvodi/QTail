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
}

QTEST_MAIN(FilterDialogTest)

#include "tst_FilterDialogTest.moc"
