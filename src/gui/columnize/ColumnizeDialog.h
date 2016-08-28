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

namespace Ui {
class ColumnizeDialog;
}

class ColumnizeDialog : public QDialog
{
   Q_OBJECT

public:
   explicit ColumnizeDialog(QWidget *parent = 0);
   ~ColumnizeDialog();

private slots:
   void on_testTextEdit_textChanged();
   void on_testColumnizeButton_clicked();

private:
   Ui::ColumnizeDialog *ui;
};

#endif // COLUMNIZEDIALOG_H
