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
}

FileListItemWidget::~FileListItemWidget()
{
    delete ui;
}
