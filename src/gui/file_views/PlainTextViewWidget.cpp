/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QScrollBar>

#include "PlainTextViewWidget.h"
#include "ui_PlainTextViewWidget.h"

PlainTextViewWidget::PlainTextViewWidget(QWidget *parent) :
   QFrame(parent),
   ui(new Ui::PlainTextViewWidget)
{
   ui->setupUi(this);

   connect(ui->navigateBottomButton, &QToolButton::clicked,
           ui->plainTextEdit, &PlainTextEdit::scrollToBottom);
   connect(ui->navigateTopButton, &QToolButton::clicked,
           ui->plainTextEdit, &PlainTextEdit::scrollToTop);
   connect(ui->navigateCursorButton, &QToolButton::clicked,
           ui->plainTextEdit, &PlainTextEdit::scrollToCursor);
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
