/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "HighlightingDialog.h"
#include "ui_HighlightingDialog.h"

HighlightingDialog::HighlightingDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::HighlightingDialog)
{
   ui->setupUi(this);
}

HighlightingDialog::~HighlightingDialog()
{
   delete ui;
}

void HighlightingDialog::on_addRuleButton_clicked()
{
   addNewRuleToListWidget(ui->wordRulesListWidget);
}

void HighlightingDialog::addNewRuleToListWidget(QListWidget *listWidget)
{
   QListWidgetItem *listItem = new QListWidgetItem;
   listItem->setBackground(ui->backgroundColorPicker->currentColor());
   listItem->setForeground(ui->foregroundColorPicker->currentColor());
//   listItem->setFont(ui->fontPicker->currentFont());
   listItem->setText(ui->regexLineEdit->text());
   listWidget->addItem(listItem);

}
