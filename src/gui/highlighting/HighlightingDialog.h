/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef HIGHLIGHTINGDIALOG_H
#define HIGHLIGHTINGDIALOG_H

#include <QDialog>

namespace Ui {
class HighlightingDialog;
}

class HighlightingDialog : public QDialog
{
   Q_OBJECT

public:
   explicit HighlightingDialog(QWidget *parent = 0);
   ~HighlightingDialog();

private:
   Ui::HighlightingDialog *ui;
};

#endif // HIGHLIGHTINGDIALOG_H
