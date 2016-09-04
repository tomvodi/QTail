/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "ColumnDefinitionDelegate.h"
#include "ColumnDefinitionDialog.h"
#include "ColumnizeDialog.h"
#include "ui_ColumnizeDialog.h"

ColumnizeDialog::ColumnizeDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::ColumnizeDialog),
   m_defintionDialog(new ColumnDefinitionDialog)
{
   ui->setupUi(this);
   ui->columnDefinitionsListWidget->setItemDelegate(new ColumnDefinitionDelegate(this));
   on_testTextEdit_textChanged();
   setColumnDefinitionConfigVisible(false);
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

void ColumnizeDialog::on_addDefinitionButton_clicked()
{
   m_defintionDialog->exec();
   if (m_defintionDialog->result() == QDialog::Accepted) {
      ColumnDefinition definition = m_defintionDialog->selectedDefinition();
      addDefinitionToList(definition);
   }
}

void ColumnizeDialog::on_columnDefinitionsListWidget_currentItemChanged(QListWidgetItem *current,
                                                                        QListWidgetItem *previous)
{
   setColumnDefinitionConfigVisible(false);

   if (!current) {
      return;
   }

   ColumnDefinition definition = current->data(ColumnDefinitionDataRole).value<ColumnDefinition>();
   if (!definition) {
      return;
   }

   QWidget *configWidget = definition->configWidget();
   if (!configWidget) {
      return;
   }

   if (ui->configureDefinitionLayout->count()) {
      ui->configureDefinitionLayout->takeAt(0);
   }

   ui->configureDefinitionLayout->addWidget(configWidget);
   setColumnDefinitionConfigVisible(true);
}

void ColumnizeDialog::addDefinitionToList(const ColumnDefinition &definition)
{
   QListWidgetItem *item = new QListWidgetItem(ui->columnDefinitionsListWidget);
   item->setData(ColumnDefinitionDataRole, QVariant::fromValue<ColumnDefinition>(definition));
   item->setData(ColumnTypeDataRole, QVariant::fromValue<ColumnType>(definition->type()));
}

void ColumnizeDialog::setColumnDefinitionConfigVisible(bool visible)
{
   ui->configureDefinitionWidget->setVisible(visible);
}

ColumnFactory ColumnizeDialog::columnFactory() const
{
   return m_defintionDialog->columnFactory();
}

void ColumnizeDialog::setColumnFactory(const ColumnFactory &columnFactory)
{
   m_defintionDialog->setColumnFactory(columnFactory);
}
