/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "PlainTextViewWidget.h"
#include "ui_PlainTextViewWidget.h"

PlainTextViewWidget::PlainTextViewWidget(QWidget *parent) :
   QFrame(parent),
   ui(new Ui::PlainTextViewWidget)
{
   ui->setupUi(this);

   connect(ui->followTailCheckBox, &QCheckBox::toggled,
           this, &PlainTextViewWidget::setFollowTailEnabled);
   setFollowTailEnabled(ui->followTailCheckBox->isChecked());
}

PlainTextViewWidget::~PlainTextViewWidget()
{
   delete ui;
}

void PlainTextViewWidget::changeEvent(QEvent *e)
{
   QFrame::changeEvent(e);
   switch (e->type()) {
   case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
   default:
      break;
   }
}

void PlainTextViewWidget::appendPlainText(const QString &text)
{
   ui->plainTextEdit->appendPlainText(text);
}

QString PlainTextViewWidget::toPlainText() const
{
   return ui->plainTextEdit->toPlainText();
}

void PlainTextViewWidget::clear()
{
   ui->plainTextEdit->clear();
}

void PlainTextViewWidget::setFollowTailEnabled(bool enabled)
{
   ui->plainTextEdit->setScrollEnabled(enabled);
}
