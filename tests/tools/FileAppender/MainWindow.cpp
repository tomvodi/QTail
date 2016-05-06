/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QListWidget>
#include <QFileDialog>

#include <TailEngine.h>

#include "views/FileListItemWidget.h"
#include "views/FileConfigPage.h"

#include "MainWindow.h"
#include "ui_MainWindow.h"

FilAppenderMainWindow::FilAppenderMainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   createConnections();
}

FilAppenderMainWindow::~FilAppenderMainWindow()
{
   delete ui;
}

void FilAppenderMainWindow::on_actionOpen_triggered()
{
   QStringList filePaths = QFileDialog::getOpenFileNames(this, tr("Open file"), m_settings.lastOpenDir().absolutePath(),
                                                         QStringLiteral("All files *.*"));

   if (filePaths.isEmpty()) {
      return;
   }

   foreach (const QString &filePath, filePaths) {
      openFile(filePath);
   }
}

void FilAppenderMainWindow::createConnections()
{
   connect(ui->fileListWidget, &QListWidget::currentItemChanged,
           [this] (QListWidgetItem *item, QListWidgetItem *) {
      if (!item) {
         return;
      }

      QString filePath = item->data(FilePathDataRole).toString();
      showFile(filePath);
   });
}

void FilAppenderMainWindow::showFile(const QString &filePath)
{
   FileConfigPage *configPage = m_fileConfigPages.value(filePath);

   if (configPage) {
      ui->stackedWidget->setCurrentWidget(configPage);
   }
}

void FilAppenderMainWindow::openFile(const QString &filePath)
{
   QFileInfo fileInfo(filePath);
   QString insertPath = fileInfo.absoluteFilePath();

   if (!fileInfo.exists() ||
       m_fileConfigPages.contains(insertPath)) {
      return;
   }

   FileConfigPage *configPage = new FileConfigPage;
   configPage->setFile(fileInfo);
   QListWidgetItem *item = new QListWidgetItem(ui->fileListWidget);

   ui->stackedWidget->addWidget(configPage);
   m_fileConfigPages.insert(insertPath, configPage);

   item->setData(FilePathDataRole, fileInfo.absoluteFilePath());
   ui->fileListWidget->addItem(item);
   FileListItemWidget *itemWidget = new FileListItemWidget;
   connect(itemWidget, &FileListItemWidget::closeFileRequested,
           [this, item] {
      closeFileItem(item);
   });
   itemWidget->setFileName(fileInfo.fileName());
   item->setSizeHint(itemWidget->sizeHint());
   ui->fileListWidget->setItemWidget(item, itemWidget);
   ui->fileListWidget->setCurrentRow(ui->fileListWidget->row(item));
}

void FilAppenderMainWindow::closeFileItem(QListWidgetItem *listItem)
{
   QString filePath = listItem->data(FilePathDataRole).toString();

   int itemRow = ui->fileListWidget->row(listItem);
   ui->fileListWidget->takeItem(itemRow);
   delete listItem;

   FileConfigPage *configPage = m_fileConfigPages.take(filePath);
   delete configPage;
}
