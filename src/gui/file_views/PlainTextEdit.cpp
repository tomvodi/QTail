/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "PlainTextEdit.h"
#include "ui_PlainTextEdit.h"

PlainTextEdit::PlainTextEdit(QWidget *parent) :
   QFrame(parent),
   ui(new Ui::PlainTextEdit)
{
   ui->setupUi(this);

   ui->plainTextEdit->setCenterOnScroll(true);

   connect(ui->followTailCheckBox, &QCheckBox::toggled,
           this, &PlainTextEdit::setFollowTailEnabled);
}

PlainTextEdit::~PlainTextEdit()
{
   delete ui;
}

void PlainTextEdit::appendPlainText(const QString &text)
{
   ui->plainTextEdit->appendPlainText(text);
}

QString PlainTextEdit::toPlainText() const
{
   return ui->plainTextEdit->toPlainText();
}

void PlainTextEdit::clear()
{
   ui->plainTextEdit->clear();
}

void PlainTextEdit::setFollowTailEnabled(bool enabled)
{
}
