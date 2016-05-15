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

HighlightingDialog::HighlightingDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::HighlightingDialog)
{
   ui->setupUi(this);

   ui->wordRulesListWidget->setItemDelegate(new HighlightListItemDelegate);
   ui->lineRulesListWidget->setItemDelegate(new HighlightListItemDelegate);

   connect(ui->wordRulesListWidget, &QListWidget::itemSelectionChanged,
           [this] {
      if (ui->wordRulesListWidget->selectedItems().count()) {
         ui->lineRulesListWidget->selectionModel()->clear();
      }
   });
   connect(ui->lineRulesListWidget, &QListWidget::itemSelectionChanged,
           [this] {
      if (ui->lineRulesListWidget->selectedItems().count()) {
         ui->wordRulesListWidget->selectionModel()->clear();
      }
   });
}

HighlightingDialog::~HighlightingDialog()
{
   delete ui;
}

void HighlightingDialog::on_addRuleButton_clicked()
{
   addNewRuleToListWidget(ui->wordRulesListWidget);
}

void HighlightingDialog::on_deleteRuleButton_clicked()
{
   deleteCurrentSelectedRule();
}

void HighlightingDialog::addNewRuleToListWidget(QListWidget *listWidget)
{
   QListWidgetItem *listItem = new QListWidgetItem;
   listItem->setBackground(ui->backgroundColorPicker->currentColor());
   listItem->setForeground(ui->foregroundColorPicker->currentColor());
   listItem->setFont(ui->fontPicker->currentFont());
   listItem->setText(ui->regexLineEdit->text());
   listWidget->addItem(listItem);
}

void HighlightingDialog::deleteCurrentSelectedRule()
{
   QListWidgetItem *selectedItem = currentSelectedItem();
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
