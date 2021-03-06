/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "ColumnDefinitionDelegate.h"
#include "ColumnDefinitionDialog.h"
#include "ui_ColumnDefinitionDialog.h"

ColumnDefinitionDialog::ColumnDefinitionDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::ColumnDefinitionDialog)
{
   ui->setupUi(this);
   ui->definitionsListWidget->setItemDelegate(new ColumnDefinitionDelegate);
}

ColumnDefinitionDialog::~ColumnDefinitionDialog()
{
   delete ui;
}

ColumnFactory ColumnDefinitionDialog::columnFactory() const
{
   return m_columnFactory;
}

void ColumnDefinitionDialog::setColumnFactory(const ColumnFactory &columnFactory)
{
   m_columnFactory = columnFactory;
   updateDefinitionList();
}

ColumnDefinition ColumnDefinitionDialog::selectedDefinition() const
{
   ColumnDefinition definition;

   QListWidgetItem *currentItem = ui->definitionsListWidget->currentItem();
   if (!currentItem) {
      return definition;
   }

   ColumnType type = currentItem->data(ColumnTypeDataRole).value<ColumnType>();

   if (!m_columnFactory) {
      return definition;
   }

   return m_columnFactory->getDefinition(type);
}

void ColumnDefinitionDialog::updateDefinitionList()
{
   if (!m_columnFactory) {
      return;
   }

   ui->definitionsListWidget->clear();

   for (ColumnType type: m_columnFactory->supportedTypes()) {
      ColumnDefinition definition = m_columnFactory->getDefinition(type);
      addDefinitionToList(definition);
   }
}

void ColumnDefinitionDialog::addDefinitionToList(const ColumnDefinition &definition)
{
   QListWidgetItem *item = new QListWidgetItem(ui->definitionsListWidget);
   item->setData(ColumnDefinitionDataRole, QVariant::fromValue<ColumnDefinition>(definition));
   item->setData(ColumnTypeDataRole, QVariant::fromValue<ColumnType>(definition->type()));
}
