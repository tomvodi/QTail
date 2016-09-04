/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "DateTimeConfigWidget.h"
#include "ui_DateTimeConfigWidget.h"

DateTimeConfigWidget::DateTimeConfigWidget(QWidget *parent) :
   QFrame(parent),
   ui(new Ui::DateTimeConfigWidget)
{
   ui->setupUi(this);
}

DateTimeConfigWidget::~DateTimeConfigWidget()
{
   delete ui;
}
