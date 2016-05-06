/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "FileListItemWidget.h"
#include "ui_FileListItemWidget.h"

FileListItemWidget::FileListItemWidget(QWidget *parent) :
   QFrame(parent),
   ui(new Ui::FileListItemWidget)
{
   ui->setupUi(this);

   setFileName("");

   connect(ui->closeButton, &QToolButton::clicked,
           this, &FileListItemWidget::closeFileRequested);
}

FileListItemWidget::~FileListItemWidget()
{
   delete ui;
}

void FileListItemWidget::setFileName(const QString &fileName)
{
   ui->fileNameLabel->setText(fileName);
}

QString FileListItemWidget::fileName() const
{
   return ui->fileNameLabel->text();
}

