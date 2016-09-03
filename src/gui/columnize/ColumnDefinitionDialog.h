/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef COLUMNDEFINITIONDIALOG_H
#define COLUMNDEFINITIONDIALOG_H

#include <QDialog>

#include "ColumnDefinitionFactory.h"

namespace Ui {
class ColumnDefinitionDialog;
}

/*!
 * \brief The ColumnDefinitionDialog class
 * This dialog lets the user select/edit one column type.
 */
class ColumnDefinitionDialog : public QDialog
{
   Q_OBJECT

public:
   explicit ColumnDefinitionDialog(QWidget *parent = 0);
   ~ColumnDefinitionDialog();

   ColumnFactory columnFactory() const;
   void setColumnFactory(const ColumnFactory &columnFactory);

   ColumnDefinition selectedDefinition() const;

private:
   void updateDefinitionList();
   void addDefinitionToList(const ColumnDefinition &definition);
   Ui::ColumnDefinitionDialog *ui;
   ColumnFactory m_columnFactory;
};

#endif // COLUMNDEFINITIONDIALOG_H
