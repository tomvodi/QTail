/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "HighlightListItemDelegate.h"
#include "HighlightingDialog.h"
#include "ui_HighlightingDialog.h"

int HighlightingDialog::HighlightRuleDataRole = Qt::UserRole + 1;

HighlightingDialog::HighlightingDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::HighlightingDialog)
{
   ui->setupUi(this);

   ui->wordRulesListWidget->setItemDelegate(new HighlightListItemDelegate);
   ui->lineRulesListWidget->setItemDelegate(new HighlightListItemDelegate);

   createConnections();
}

void HighlightingDialog::createConnections()
{
   connect(ui->wordRulesListWidget, &QListWidget::itemSelectionChanged,
           [this] {
      if (ui->wordRulesListWidget->selectedItems().count()) {
         ui->lineRulesListWidget->selectionModel()->clear();
      }
      setUiForCurrentSelectedItem();
   });
   connect(ui->lineRulesListWidget, &QListWidget::itemSelectionChanged,
           [this] {
      if (ui->lineRulesListWidget->selectedItems().count()) {
         ui->wordRulesListWidget->selectionModel()->clear();
      }
      setUiForCurrentSelectedItem();
   });

   connect(ui->foregroundColorPicker, &ColorPicker::currentColorChanged,
           this, &HighlightingDialog::updateCurrentSelectedRuleValues);
   connect(ui->backgroundColorPicker, &ColorPicker::currentColorChanged,
           this, &HighlightingDialog::updateCurrentSelectedRuleValues);
   connect(ui->fontPicker, &FontPicker::currentFontChanged,
           this, &HighlightingDialog::updateCurrentSelectedRuleValues);
   connect(ui->regexLineEdit, &QLineEdit::textChanged,
           this, &HighlightingDialog::updateCurrentSelectedRuleValues);
   connect(ui->caseSensitiveCheckBox, &QCheckBox::toggled,
           this, &HighlightingDialog::updateCurrentSelectedRuleValues);
}

QList<HighlightingRule> HighlightingDialog::rulesFromListWidget(QListWidget *listWidget) const
{
   QList<HighlightingRule> rules;

   for (int i = 0; i < listWidget->count(); ++i) {
      QListWidgetItem *item = listWidget->item(i);
      if (!item) {
         continue;
      }

      QVariant highlightingRuleData = item->data(HighlightRuleDataRole);
      HighlightingRule highlightingRule = highlightingRuleData.value<HighlightingRule>();
      rules << highlightingRule;
   }

   return rules;
}

HighlightingDialog::~HighlightingDialog()
{
   delete ui;
}

void HighlightingDialog::setHighlightingRules(const QList<HighlightingRule> &lineRules,
                                              const QList<HighlightingRule> &wordRules)
{
   foreach (const HighlightingRule &rule, lineRules) {
      addNewRuleToListWidget(ui->lineRulesListWidget, rule);
   }
   foreach (const HighlightingRule &rule, wordRules) {
      addNewRuleToListWidget(ui->wordRulesListWidget, rule);
   }
}

QList<HighlightingRule> HighlightingDialog::wordHighlightingRules() const
{
   return rulesFromListWidget(ui->wordRulesListWidget);
}

QList<HighlightingRule> HighlightingDialog::lineHighlightingRules() const
{
   return rulesFromListWidget(ui->lineRulesListWidget);
}

void HighlightingDialog::on_addRuleButton_clicked()
{
   addNewRuleToListWidget(ui->wordRulesListWidget, highlightingRuleFromGui());
}

void HighlightingDialog::on_deleteRuleButton_clicked()
{
   deleteCurrentSelectedRule();
}

void HighlightingDialog::on_buttonBox_clicked(QAbstractButton *button)
{
   QDialogButtonBox::StandardButton standardButton = ui->buttonBox->standardButton(button);
   if (standardButton == QDialogButtonBox::Apply ||
       standardButton == QDialogButtonBox::Ok) {
      emit highlightingRulesChanged(lineHighlightingRules(), wordHighlightingRules());
   }
}

void HighlightingDialog::updateCurrentSelectedRuleValues()
{
   QListWidgetItem *currentItem = currentSelectedItem();
   if (!currentItem) {
      return;
   }

   HighlightingRule highlightingRule = currentItem->data(HighlightRuleDataRole).value<HighlightingRule>();

   // Foreground color
   highlightingRule.setForegroundColor(ui->foregroundColorPicker->currentColor());
   currentItem->setForeground(ui->foregroundColorPicker->currentColor());

   // Background color
   highlightingRule.setBackgroundColor(ui->backgroundColorPicker->currentColor());
   currentItem->setBackground(ui->backgroundColorPicker->currentColor());

   // Font
   highlightingRule.setFont(ui->fontPicker->currentFont());
   currentItem->setFont(ui->fontPicker->currentFont());

   // Text
   highlightingRule.setText(ui->regexLineEdit->text());
   currentItem->setText(ui->regexLineEdit->text());

   // Case sensitivity
   highlightingRule.setCaseSensitivity((ui->caseSensitiveCheckBox->isChecked() ?
                                           Qt::CaseSensitive : Qt::CaseInsensitive));

   currentItem->setData(HighlightRuleDataRole, QVariant::fromValue<HighlightingRule>(highlightingRule));
}

HighlightingRule HighlightingDialog::highlightingRuleFromGui() const
{
   HighlightingRule rule;
   rule.setBackgroundColor(ui->backgroundColorPicker->currentColor());
   rule.setForegroundColor(ui->foregroundColorPicker->currentColor());
   rule.setFont(ui->fontPicker->currentFont());
   rule.setText(ui->regexLineEdit->text());
   rule.setCaseSensitivity(ui->caseSensitiveCheckBox->isChecked() ?
                              Qt::CaseSensitive :
                              Qt::CaseInsensitive);

   return rule;
}

void HighlightingDialog::addNewRuleToListWidget(QListWidget *listWidget, const HighlightingRule &rule)
{
   QListWidgetItem *listItem = new QListWidgetItem;
   listItem->setBackground(rule.backgroundColor());
   listItem->setForeground(rule.foregroundColor());
   listItem->setFont(rule.font());
   listItem->setText(rule.text());
   listItem->setData(HighlightRuleDataRole, QVariant::fromValue<HighlightingRule>(rule));
   listWidget->addItem(listItem);

   selectListWidgetItem(listItem);
}

void HighlightingDialog::deleteCurrentSelectedRule()
{
   QListWidgetItem *selectedItem = currentSelectedItem();
   int currentSelectedRow = selectedItem->listWidget()->row(selectedItem);

   if (!selectedItem) {
      return;
   }

   QListWidget *listWidget = selectedItem->listWidget();
   if (!listWidget) {
      return;
   }

   QWidget *itemWidget = listWidget->itemWidget(selectedItem);
   listWidget->takeItem(listWidget->row(selectedItem));
   if (itemWidget) {
      delete itemWidget;
   }
   delete selectedItem;

   if (listWidget->count() == 0) {
      return;
   }

   int selectIndex = 0;

   if (currentSelectedRow >= listWidget->count()) {
      selectIndex = listWidget->count() - 1;
   }

   listWidget->selectionModel()->clear();
   QModelIndex itemIndex = listWidget->model()->index(selectIndex, 0);
   listWidget->selectionModel()->select(itemIndex, QItemSelectionModel::Select);
}

void HighlightingDialog::setUiForCurrentSelectedItem()
{
   QListWidgetItem *selectedItem = currentSelectedItem();
   if (!selectedItem) {
      return;
   }

   HighlightingRule highlightingRule = selectedItem->data(HighlightRuleDataRole).value<HighlightingRule>();
   ui->foregroundColorPicker->setCurrentColor(highlightingRule.foregroundColor());
   ui->backgroundColorPicker->setCurrentColor(highlightingRule.backgroundColor());
   ui->fontPicker->setCurrentFont(highlightingRule.font());
   ui->regexLineEdit->setText(highlightingRule.text());
   ui->caseSensitiveCheckBox->setChecked(highlightingRule.caseSensitivity() == Qt::CaseSensitive);
}

QListWidgetItem *HighlightingDialog::currentSelectedItem() const
{
   QListWidgetItem *selectedItem = nullptr;

   if (ui->wordRulesListWidget->selectedItems().count()) {
      selectedItem = ui->wordRulesListWidget->selectedItems().at(0);
   }

   if (ui->lineRulesListWidget->selectedItems().count()) {
      selectedItem = ui->lineRulesListWidget->selectedItems().at(0);
   }

   return selectedItem;
}

void HighlightingDialog::selectListWidgetItem(QListWidgetItem *item)
{
   QListWidget *listWidget = item->listWidget();
   if (!listWidget) {
      return;
   }
   int itemRow = listWidget->row(item);
   QModelIndex itemIndex = listWidget->model()->index(itemRow, 0);

   if (!itemIndex.isValid()) {
      return;
   }

   listWidget->selectionModel()->clear();
   listWidget->selectionModel()->select(itemIndex, QItemSelectionModel::Select);
}
