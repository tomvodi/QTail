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
#include <QPushButton>

#include <TestCommon.h>
#include <highlighting/HighlightingDialog.h>
#include <ui_HighlightingDialog.h>

class HighlightingDialogTest : public QObject
{
   Q_OBJECT

public:
   HighlightingDialogTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testExclusiveSelection();
   void testAddHighlightingRuleToListWidget();
   void testAddRuleButtonclicked();
   void testAddMultipleHighlightingRules();
   void testDeleteHighlighingRule();
   void testDeleteRuleWithMultipleRulesInList();
   void testChangeSelectedRule();
   void testChangingSelectedRule();
   void testHighlightingRulesChanged();
   void testSetHighlightingRules();
   void testMoveDownWordHighlightItem();
   void testMoveUpWordHighlightItem();
   void testMoveBottomWordHighlightItem();
   void testMoveTopWordHighlightItem();
   void testAddRuleIfListWidgetsAreEmpty();
};

HighlightingDialogTest::HighlightingDialogTest()
{
}

void HighlightingDialogTest::initTestCase()
{
}

void HighlightingDialogTest::cleanupTestCase()
{
}

void HighlightingDialogTest::testExclusiveSelection()
{
   HighlightingDialog dialog;

   dialog.ui->wordRulesListWidget->addItem("Word rule item 1");
   dialog.ui->lineRulesListWidget->addItem("Line rule item 1");

   QAbstractItemModel *wordListModel = dialog.ui->wordRulesListWidget->model();
   QAbstractItemModel *lineListModel = dialog.ui->lineRulesListWidget->model();
   dialog.ui->wordRulesListWidget->selectionModel()->select(wordListModel->index(0, 0), QItemSelectionModel::Select);
   QVERIFY2(dialog.ui->wordRulesListWidget->selectedItems().count(), "No items selected");

   dialog.ui->lineRulesListWidget->selectionModel()->select(lineListModel->index(0, 0), QItemSelectionModel::Select);
   QVERIFY2(dialog.ui->wordRulesListWidget->selectedItems().count() == 0, "Word list item wasn't unselected.");
   QVERIFY2(dialog.ui->lineRulesListWidget->selectedItems().count(), "Line item wasn't selected.");
}

void HighlightingDialogTest::testAddHighlightingRuleToListWidget()
{
   HighlightingDialog dialog;

   QFont testFont = TestCommon::testFont();
   HighlightingRule rule;
   rule.setBackgroundColor(Qt::lightGray);
   rule.setForegroundColor(Qt::yellow);
   rule.setFont(testFont);
   rule.setText("Blablalbla");

   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, rule);

   QVERIFY2(dialog.ui->wordRulesListWidget->selectedItems().count(), "Added rule wasn't selected");

   QListWidgetItem *listItem = dialog.ui->wordRulesListWidget->item(0);

   QVERIFY2(listItem != 0, "No list item was added for new rule");
   QVERIFY2(listItem->background() == rule.backgroundColor(), "Background color wasn't set in list item");
   QVERIFY2(listItem->foreground() == rule.foregroundColor(), "Foreground color wasn't set in list item");
   QVERIFY2(listItem->text() == rule.text(), "Text wasn't set in list item");
   qDebug() << "List item font: " << listItem->font();
   qDebug() << "rule font     : " << rule.font();
   QVERIFY2(listItem->font() == rule.font(), "Font wasn't set in list item");

   QVERIFY2(listItem->data(HighlightingDialog::HighlightRuleDataRole).canConvert<HighlightingRule>(),
            "Highlighting rule data wasn't set in list item");
   HighlightingRule listItemDataRule = listItem->data(HighlightingDialog::HighlightRuleDataRole).value<HighlightingRule>();
   QVERIFY2(listItemDataRule == rule, "Rule in list item isn't the same that was set");
}

/*!
 * \brief HighlightingDialogTest::testAddRuleButtonclicked
 * If a rule is selected in a list widget, the new rule should be added after this selected rule
 * with the same highlighting values.
 */
void HighlightingDialogTest::testAddRuleButtonclicked()
{
   HighlightingDialog dialog;

   HighlightingRule wordRule1;
   wordRule1.setText("word rule 1 text");

   HighlightingRule wordRule2;
   wordRule2.setText("word rule 2 text");

   HighlightingRule wordRule3;
   wordRule3.setText("word rule 3 text");

   QListWidget *listWidget = dialog.ui->lineRulesListWidget;
   dialog.addNewRuleToListWidget(listWidget, wordRule1);
   dialog.addNewRuleToListWidget(listWidget, wordRule2);
   dialog.addNewRuleToListWidget(listWidget, wordRule3);

   int selectedRuleIndex = 1;

   // Select second item
   QAbstractItemModel *listModel = listWidget->model();
   listWidget->selectionModel()->clear();
   listWidget->selectionModel()->select(listModel->index(selectedRuleIndex, 0),
                                        QItemSelectionModel::Select);

   dialog.on_addRuleButton_clicked();
   QVERIFY2(listWidget->count() == 4, "No rule was added to list widget.");
   QVERIFY2(listWidget->item(selectedRuleIndex + 1)->text() == wordRule2.text(),
            "The rule item after the copied rule hasn't the same text");
}

void HighlightingDialogTest::testAddMultipleHighlightingRules()
{
   HighlightingDialog dialog;

   HighlightingRule rule1;
   rule1.setText("Blablalbla");
   HighlightingRule rule2;
   rule2.setText("Rule 2");

   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, rule1);
   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, rule2);

   QVERIFY2(dialog.ui->wordRulesListWidget->selectedItems().count() == 1, "Adding second rule selected more than one item.");
}

/*!
 * \brief HighlightingDialogTest::testDeleteHighlighingRule
 * Test deleting rule. After deleting rule in the middle of the list, the selected rule index
 * should be the same as before deleting the item.
 */
void HighlightingDialogTest::testDeleteHighlighingRule()
{
   HighlightingDialog dialog;

   HighlightingRule rule1;
   rule1.setText("Rule 1");
   HighlightingRule rule2;
   rule2.setText("Rule 2");
   HighlightingRule rule3;
   rule3.setText("Rule 3");

   int deleteItemRowIndex = 1;
   QListWidget *listWidget = dialog.ui->wordRulesListWidget;
   dialog.addNewRuleToListWidget(listWidget, rule1);
   dialog.addNewRuleToListWidget(listWidget, rule2);
   dialog.addNewRuleToListWidget(listWidget, rule3);
   Q_ASSERT(listWidget->count() == 3);

   // Select second item
   QAbstractItemModel *wordListModel = dialog.ui->wordRulesListWidget->model();
   listWidget->selectionModel()->clear();
   listWidget->selectionModel()->select(wordListModel->index(deleteItemRowIndex, 0),
                                        QItemSelectionModel::Select);

   dialog.deleteCurrentSelectedRule();
   QVERIFY2(listWidget->count() == 2, "Selected rule wasn't deleted");
   QVERIFY2(listWidget->row(dialog.currentSelectedItem()) == deleteItemRowIndex,
            "Wrong selected rule after deleting rule");
}

void HighlightingDialogTest::testDeleteRuleWithMultipleRulesInList()
{
   HighlightingDialog dialog;

   QFont testFont = TestCommon::testFont();
   HighlightingRule rule1;
   rule1.setText("Blablalbla");
   rule1.setFont(testFont);

   HighlightingRule rule2;
   rule2.setText("Test text 2");
   rule2.setFont(testFont);

   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, rule1);
   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, rule2);

   Q_ASSERT(dialog.ui->wordRulesListWidget->selectedItems().count());

   QListWidgetItem *selectedItem = dialog.ui->wordRulesListWidget->selectedItems().at(0);
   QVariant selectedRuleData = selectedItem->data(HighlightingDialog::HighlightRuleDataRole);
   HighlightingRule selectedRule = selectedRuleData.value<HighlightingRule>();
   QVERIFY2(selectedRule == rule2, "Wrong selected rule");

   dialog.deleteCurrentSelectedRule();

   QVERIFY2(dialog.ui->wordRulesListWidget->selectedItems().count(), "No selected rule after deleting one rule");
   selectedItem = dialog.ui->wordRulesListWidget->selectedItems().at(0);
   selectedRuleData = selectedItem->data(HighlightingDialog::HighlightRuleDataRole);
   selectedRule = selectedRuleData.value<HighlightingRule>();
   QVERIFY2(selectedRule == rule1, "Wrong selected rule, probably wrong rule deleted.");
}

/*!
 * \brief HighlightingDialogTest::testChangeSelectedRule
 * Changing the current selected rule should display the rule's setting in ui.
 */
void HighlightingDialogTest::testChangeSelectedRule()
{
   HighlightingDialog dialog;

   QFont testFont = TestCommon::testFont();
   HighlightingRule rule1;
   rule1.setBackgroundColor(Qt::lightGray);
   rule1.setForegroundColor(Qt::yellow);
   rule1.setFont(testFont);
   rule1.setText("Blablalbla");

   HighlightingRule rule2;
   rule2.setBackgroundColor(Qt::black);
   rule2.setForegroundColor(Qt::white);
   rule2.setFont(testFont);
   rule2.setText("Test text 2");

   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, rule1);
   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, rule2);

   Q_ASSERT(dialog.ui->wordRulesListWidget->selectedItems().count());

   QListWidgetItem *selectedItem = dialog.ui->wordRulesListWidget->selectedItems().at(0);
   QVariant selectedRuleData = selectedItem->data(HighlightingDialog::HighlightRuleDataRole);
   HighlightingRule selectedRule = selectedRuleData.value<HighlightingRule>();
   QVERIFY2(selectedRule == rule2, "Wrong selected rule");

   QVERIFY2(dialog.ui->foregroundColorPicker->currentColor() == rule2.foregroundColor(),
            "Foreground color wasn't set from selected rule");
   QVERIFY2(dialog.ui->backgroundColorPicker->currentColor() == rule2.backgroundColor(),
            "Background color wasn't set from selected rule");
   QVERIFY2(dialog.ui->fontPicker->currentFont() == rule2.font(),
            "Font wasn't set from selected rule");
   QVERIFY2(dialog.ui->regexLineEdit->text() == rule2.text(),
            "Text wasn't set from selected rule");
   QVERIFY2(dialog.ui->caseSensitiveCheckBox->isChecked() == (rule2.caseSensitivity() == Qt::CaseSensitive),
            "Case sensitivity wasn't set from selected rule");
}

/*!
 * \brief HighlightingDialogTest::testChangingSelectedRule
 * Changing the ui, should change the current selected rules values.
 */
void HighlightingDialogTest::testChangingSelectedRule()
{
   HighlightingDialog dialog;

   QFont testFont = TestCommon::testFont();
   HighlightingRule rule1;
   rule1.setBackgroundColor(Qt::lightGray);
   rule1.setForegroundColor(Qt::yellow);
   rule1.setFont(testFont);
   rule1.setText("Rule 1 text");

   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, rule1);

   Q_ASSERT(dialog.ui->wordRulesListWidget->selectedItems().count());

   QColor newForegroundColor(Qt::blue);
   QColor newBackgroundColor(Qt::green);
   testFont.setBold(true);
   testFont.setItalic(true);
   QString testText("New text for rule");
   bool newCaseValue = !dialog.ui->caseSensitiveCheckBox->isChecked();

   dialog.ui->foregroundColorPicker->setCurrentColor(newForegroundColor);
   dialog.ui->backgroundColorPicker->setCurrentColor(newBackgroundColor);
   dialog.ui->fontPicker->setCurrentFont(testFont);
   dialog.ui->regexLineEdit->setText(testText);
   dialog.ui->caseSensitiveCheckBox->setChecked(newCaseValue);

   QListWidgetItem *selectedItem = dialog.ui->wordRulesListWidget->selectedItems().at(0);
   QVariant selectedRuleData = selectedItem->data(HighlightingDialog::HighlightRuleDataRole);
   HighlightingRule selectedRule = selectedRuleData.value<HighlightingRule>();

   QVERIFY2(selectedItem->foreground() == newForegroundColor, "Foreground color wasn't set for list item.");
   QVERIFY2(selectedRule.foregroundColor() == newForegroundColor, "Foreground color wasn't set for selected rule");

   QVERIFY2(selectedItem->backgroundColor() == newBackgroundColor, "Background color wasn't set for list item.");
   QVERIFY2(selectedRule.backgroundColor() == newBackgroundColor, "Background color wasn't set for selected rule");

   QVERIFY2(selectedItem->font() == testFont, "Font wasn't set for list item.");
   QVERIFY2(selectedRule.font() == testFont, "Font wasn't set for selected rule");

   QVERIFY2(selectedItem->text() == testText, "Text wasn't set for list item.");
   QVERIFY2(selectedRule.text() == testText, "Text wasn't set for selected rule");

   QVERIFY2(selectedRule.caseSensitivity() == (newCaseValue ? Qt::CaseSensitive : Qt::CaseInsensitive),
            "Case sensitivity wasn't set for selected rule");
}

void HighlightingDialogTest::testHighlightingRulesChanged()
{
   HighlightingDialog dialog;

   QFont testFont = TestCommon::testFont();
   HighlightingRule wordRule1;
   wordRule1.setBackgroundColor(Qt::lightGray);
   wordRule1.setForegroundColor(Qt::yellow);
   wordRule1.setFont(testFont);
   wordRule1.setText("word rule 1 text");

   HighlightingRule wordRule2;
   wordRule2.setBackgroundColor(Qt::black);
   wordRule2.setForegroundColor(Qt::white);
   wordRule2.setFont(testFont);
   wordRule2.setText("word rule 2 text 2");

   HighlightingRule lineRule1;
   lineRule1.setBackgroundColor(Qt::yellow);
   lineRule1.setForegroundColor(Qt::white);
   lineRule1.setFont(testFont);
   lineRule1.setText("line rule 1 text");

   HighlightingRule lineRule2;
   lineRule2.setBackgroundColor(Qt::green);
   lineRule2.setForegroundColor(Qt::blue);
   lineRule2.setFont(testFont);
   lineRule2.setText("line rule 2 text 2");

   dialog.addNewRuleToListWidget(dialog.ui->lineRulesListWidget, lineRule1);
   dialog.addNewRuleToListWidget(dialog.ui->lineRulesListWidget, lineRule2);

   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, wordRule1);
   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, wordRule2);

   QSignalSpy ruleChangedSpy(&dialog, SIGNAL(highlightingRulesChanged(QList<HighlightingRule>,QList<HighlightingRule>)));

   QPushButton *applyButton = dialog.ui->buttonBox->button(QDialogButtonBox::Apply);
   Q_ASSERT(applyButton);

   applyButton->click();

   QVERIFY2(ruleChangedSpy.count(), "Highlighting rules changed signal wasn't emitted on apply button.");

   QVariant lineHighlightRulesData = ruleChangedSpy.at(0).at(0);
   Q_ASSERT(lineHighlightRulesData.canConvert<QList<HighlightingRule>>());

   QVariant wordHighlightRulesData = ruleChangedSpy.at(0).at(1);

   QList<HighlightingRule> lineRules = lineHighlightRulesData.value<QList<HighlightingRule>>();
   QVERIFY2(lineRules.count() == 2, "The changed signal had no line rules.");
   QVERIFY2(lineRules.at(0) == lineRule1, "Wrong line rule at first position");
   QVERIFY2(lineRules.at(1) == lineRule2, "Wrong line rule at second position");

   QList<HighlightingRule> wordRules = wordHighlightRulesData.value<QList<HighlightingRule>>();
   QVERIFY2(wordRules.count() == 2, "The changed signal had no word rules.");
   QVERIFY2(wordRules.at(0) == wordRule1, "Wrong word rule at first position");
   QVERIFY2(wordRules.at(1) == wordRule2, "Wrong word rule at second position");

   ruleChangedSpy.clear();
   QPushButton *okButton = dialog.ui->buttonBox->button(QDialogButtonBox::Ok);
   Q_ASSERT(okButton);

   okButton->click();

   QVERIFY2(ruleChangedSpy.count(), "Line highlighting rules changed signal wasn't emitted on Ok button");

   lineHighlightRulesData = ruleChangedSpy.at(0).at(0);
   Q_ASSERT(lineHighlightRulesData.canConvert<QList<HighlightingRule>>());

   wordHighlightRulesData = ruleChangedSpy.at(0).at(1);

   lineRules = lineHighlightRulesData.value<QList<HighlightingRule>>();
   QVERIFY2(lineRules.count() == 2, "The changed signal had no line rules.");
   QVERIFY2(lineRules.at(0) == lineRule1, "Wrong line rule at first position");
   QVERIFY2(lineRules.at(1) == lineRule2, "Wrong line rule at second position");

   wordRules = wordHighlightRulesData.value<QList<HighlightingRule>>();
   QVERIFY2(wordRules.count() == 2, "The changed signal had no word rules.");
   QVERIFY2(wordRules.at(0) == wordRule1, "Wrong word rule at first position");
   QVERIFY2(wordRules.at(1) == wordRule2, "Wrong word rule at second position");
}

void HighlightingDialogTest::testSetHighlightingRules()
{
   HighlightingDialog dialog;

   QFont testFont = TestCommon::testFont();
   HighlightingRule wordRule1;
   wordRule1.setBackgroundColor(Qt::lightGray);
   wordRule1.setForegroundColor(Qt::yellow);
   wordRule1.setFont(testFont);
   wordRule1.setText("word rule 1 text");

   HighlightingRule wordRule2;
   wordRule2.setBackgroundColor(Qt::black);
   wordRule2.setForegroundColor(Qt::white);
   wordRule2.setFont(testFont);
   wordRule2.setText("word rule 2 text 2");

   HighlightingRule lineRule1;
   lineRule1.setBackgroundColor(Qt::yellow);
   lineRule1.setForegroundColor(Qt::white);
   lineRule1.setFont(testFont);
   lineRule1.setText("line rule 1 text");

   HighlightingRule lineRule2;
   lineRule2.setBackgroundColor(Qt::green);
   lineRule2.setForegroundColor(Qt::blue);
   lineRule2.setFont(testFont);
   lineRule2.setText("line rule 2 text 2");

   QList<HighlightingRule> wordHighlightingRules({wordRule1, wordRule2});
   QList<HighlightingRule> lineHighlightingRules({lineRule1, lineRule2});

   dialog.setHighlightingRules(lineHighlightingRules, wordHighlightingRules);

   QVERIFY2(dialog.ui->lineRulesListWidget->count() == 2, "Line rules weren't added to list");
   QVERIFY2(dialog.ui->wordRulesListWidget->count() == 2, "Word rules weren't added to list");

   QVERIFY2(dialog.wordHighlightingRules() == wordHighlightingRules, "Wrong word highlighting rules were added to list");
   QVERIFY2(dialog.lineHighlightingRules() == lineHighlightingRules, "Wrong line highlighting rules were added to list");
}

void HighlightingDialogTest::testMoveDownWordHighlightItem()
{
   HighlightingDialog dialog;

   HighlightingRule wordRule1;
   wordRule1.setText("word rule 1 text");

   HighlightingRule wordRule2;
   wordRule2.setText("word rule 2 text 2");

   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, wordRule1);
   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, wordRule2);

   // Select first item
   QAbstractItemModel *wordListModel = dialog.ui->wordRulesListWidget->model();
   dialog.ui->wordRulesListWidget->selectionModel()->clear();
   dialog.ui->wordRulesListWidget->selectionModel()->select(wordListModel->index(0, 0), QItemSelectionModel::Select);

   dialog.ui->downButton->clicked();

   QListWidgetItem *firstWordItem = dialog.ui->wordRulesListWidget->item(0);
   Q_ASSERT(firstWordItem);

   QVERIFY2(firstWordItem->text() == wordRule2.text(),
            "Second rule isn't at first position after moving first rule down");
   QListWidgetItem *selectedItem = dialog.currentSelectedItem();
   QVERIFY2(selectedItem, "No selected item after moving item down.");
   QVERIFY2(selectedItem->text() == wordRule1.text(), "The moved item isn't selected after moving");
}

void HighlightingDialogTest::testMoveUpWordHighlightItem()
{
   HighlightingDialog dialog;

   HighlightingRule wordRule1;
   wordRule1.setText("word rule 1 text");

   HighlightingRule wordRule2;
   wordRule2.setText("word rule 2 text 2");

   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, wordRule1);
   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, wordRule2);

   // Select second item
   QAbstractItemModel *wordListModel = dialog.ui->wordRulesListWidget->model();
   dialog.ui->wordRulesListWidget->selectionModel()->clear();
   dialog.ui->wordRulesListWidget->selectionModel()->select(wordListModel->index(1, 0), QItemSelectionModel::Select);

   dialog.ui->upButton->clicked();

   QListWidgetItem *secondWordItem = dialog.ui->wordRulesListWidget->item(1);
   Q_ASSERT(secondWordItem);

   QVERIFY2(secondWordItem->text() == wordRule1.text(),
            "First rule isn't at second position after moving second rule up");
   QListWidgetItem *selectedItem = dialog.currentSelectedItem();
   QVERIFY2(selectedItem, "No selected item after moving item down.");
   QVERIFY2(selectedItem->text() == wordRule2.text(), "The moved item isn't selected after moving");
}

void HighlightingDialogTest::testMoveBottomWordHighlightItem()
{
   HighlightingDialog dialog;

   HighlightingRule wordRule1;
   wordRule1.setText("word rule 1 text");

   HighlightingRule wordRule2;
   wordRule2.setText("word rule 2 text");

   HighlightingRule wordRule3;
   wordRule3.setText("word rule 3 text");

   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, wordRule1);
   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, wordRule2);
   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, wordRule3);

   // Select first item
   QAbstractItemModel *wordListModel = dialog.ui->wordRulesListWidget->model();
   dialog.ui->wordRulesListWidget->selectionModel()->clear();
   dialog.ui->wordRulesListWidget->selectionModel()->select(wordListModel->index(0, 0), QItemSelectionModel::Select);

   dialog.ui->bottomButton->clicked();

   QListWidgetItem *lastWordItem = dialog.ui->wordRulesListWidget->item(dialog.ui->wordRulesListWidget->count() - 1);
   Q_ASSERT(lastWordItem);

   QVERIFY2(lastWordItem->text() == wordRule1.text(),
            "First rule isn't at last position after moving to bottom");
   QListWidgetItem *selectedItem = dialog.currentSelectedItem();
   QVERIFY2(selectedItem, "No selected item after moving item to bottom.");
   QVERIFY2(selectedItem->text() == wordRule1.text(), "The moved item isn't selected after moving");
}

void HighlightingDialogTest::testMoveTopWordHighlightItem()
{
   HighlightingDialog dialog;

   HighlightingRule wordRule1;
   wordRule1.setText("word rule 1 text");

   HighlightingRule wordRule2;
   wordRule2.setText("word rule 2 text");

   HighlightingRule wordRule3;
   wordRule3.setText("word rule 3 text");

   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, wordRule1);
   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, wordRule2);
   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, wordRule3);

   // Select first item
   QAbstractItemModel *wordListModel = dialog.ui->wordRulesListWidget->model();
   dialog.ui->wordRulesListWidget->selectionModel()->clear();
   dialog.ui->wordRulesListWidget->selectionModel()->select(wordListModel->index(2, 0), QItemSelectionModel::Select);

   dialog.ui->topButton->clicked();

   QListWidgetItem *firstWordItem = dialog.ui->wordRulesListWidget->item(0);
   Q_ASSERT(firstWordItem);

   QVERIFY2(firstWordItem->text() == wordRule3.text(),
            "Last rule isn't at first position after moving to top");
   QListWidgetItem *selectedItem = dialog.currentSelectedItem();
   QVERIFY2(selectedItem, "No selected item after moving item to top.");
   QVERIFY2(selectedItem->text() == wordRule3.text(), "The moved item isn't selected after moving");
}

// See bug #1
void HighlightingDialogTest::testAddRuleIfListWidgetsAreEmpty()
{
   HighlightingDialog dialog;

   Q_ASSERT(dialog.ui->wordRulesListWidget->count() == 0);
   Q_ASSERT(dialog.ui->lineRulesListWidget->count() == 0);

   dialog.ui->regexLineEdit->setText("First rule ever");
   dialog.on_addRuleButton_clicked();

   QVERIFY2(dialog.ui->wordRulesListWidget->count() == 1, "No word rule was added when both lists are empty.");
}

QTEST_MAIN(HighlightingDialogTest)

#include "tst_HighlightingDialogTest.moc"
