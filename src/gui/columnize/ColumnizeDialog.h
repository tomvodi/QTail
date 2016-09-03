/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef COLUMNIZEDIALOG_H
#define COLUMNIZEDIALOG_H

#include <QDialog>

#include "ColumnDefinitionFactory.h"

namespace Ui {
class ColumnizeDialog;
}
class ColumnDefinitionDialog;

/*!
 * \brief The ColumnizeDialog class
 * With this dialog, the user is able to define a columnizer. A columnizer defines a set of column
 * definitions which are used to split logfile lines into columns.
 */
class ColumnizeDialog : public QDialog
{
   Q_OBJECT

public:
   explicit ColumnizeDialog(QWidget *parent = 0);
   ~ColumnizeDialog();

   ColumnFactory columnFactory() const;
   void setColumnFactory(const ColumnFactory &columnFactory);

private slots:
   void on_testTextEdit_textChanged();
   void on_testColumnizeButton_clicked();
   void on_addDefinitionButton_clicked();

private:
   Ui::ColumnizeDialog *ui;
   ColumnDefinitionDialog *m_defintionDialog;
   void addDefinitionToList(const ColumnDefinition &definition);
};

#endif // COLUMNIZEDIALOG_H
