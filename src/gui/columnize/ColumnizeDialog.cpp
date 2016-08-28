/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "ColumnizeDialog.h"
#include "ui_ColumnizeDialog.h"

ColumnizeDialog::ColumnizeDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::ColumnizeDialog)
{
   ui->setupUi(this);
   on_testTextEdit_textChanged();
}

ColumnizeDialog::~ColumnizeDialog()
{
   delete ui;
}

void ColumnizeDialog::on_testTextEdit_textChanged()
{
   ui->testColumnizeButton->setEnabled(!ui->testTextEdit->toPlainText().isEmpty());
}

void ColumnizeDialog::on_testColumnizeButton_clicked()
{
   QString testText = ui->testTextEdit->toPlainText();
   QString delimiter = ui->delimiterLineEdit->text();

   QStringList columns;
   if (delimiter.isEmpty()) {
      columns << testText;
   } else {
      columns = testText.split(delimiter);
   }

   ui->testOutputTableWidget->clear();
   ui->testOutputTableWidget->setRowCount(1);
   ui->testOutputTableWidget->setColumnCount(columns.count());

   for (int i = 0; i < columns.count(); ++i) {
      QTableWidgetItem *headerItem = new QTableWidgetItem;
      headerItem->setText(tr("Text"));
      ui->testOutputTableWidget->setHorizontalHeaderItem(i, headerItem);

      QString columnText = columns.at(i);
      QTableWidgetItem *item = new QTableWidgetItem;
      item->setText(columnText);
      ui->testOutputTableWidget->setItem(0, i, item);
   }
}
