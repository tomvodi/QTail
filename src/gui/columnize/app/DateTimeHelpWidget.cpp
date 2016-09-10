/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "DateTimeHelpWidget.h"
#include "ui_DateTimeHelpWidget.h"

DateTimeHelpWidget::DateTimeHelpWidget(QWidget *parent) :
   QFrame(parent),
   ui(new Ui::DateTimeHelpWidget)
{
   ui->setupUi(this);
   connect(ui->dateFormatButton, &QPushButton::toggled,
           [this] (bool checked) {
      if (checked) {
         ui->timeFormatButton->setChecked(false);
         ui->stackedWidget->setCurrentWidget(ui->datePage);
      }
   });

   connect(ui->timeFormatButton, &QPushButton::toggled,
           [this] (bool checked) {
      if (checked) {
         ui->dateFormatButton->setChecked(false);
         ui->stackedWidget->setCurrentWidget(ui->timePage);
      }
   });
   ui->dateFormatButton->setChecked(true);
}

DateTimeHelpWidget::~DateTimeHelpWidget()
{
   delete ui;
}
