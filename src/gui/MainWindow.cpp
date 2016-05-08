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
#include <QVersionNumber>

#include <QTail_version.h>
#include <TailEngine.h>

#include "file_views/PlainTextView.h"
#include "file_views/PlainTextEdit.h"
#include "file_views/FileListItemView.h"
#include "file_views/FileListItemWidget.h"

#include "AboutDialog.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   m_tailEngine = new TailEngine(this);

   createConnections();
   openLastOpenedFiles();
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
   QStringList filePaths = QFileDialog::getOpenFileNames(this, tr("Open file"), m_settings.lastOpenDir().absolutePath(),
                                                         QStringLiteral("All files *.*"));

   if (filePaths.isEmpty()) {
      return;
   }

   m_settings.setLastOpenDir(QFileInfo(filePaths.first()).absoluteDir());

   foreach (const QString &filePath, filePaths) {
      openFile(filePath);
   }
}

void MainWindow::on_actionAbout_triggered()
{
   AboutDialog dialog;
   dialog.setVersion(QVersionNumber(QTAIL_VERSION_MAJOR, QTAIL_VERSION_MINOR, QTAIL_VERSION_PATCH));
   dialog.exec();
}

void MainWindow::createConnections()
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

void MainWindow::openFile(const QString &filePath)
{
   QFileInfo fileInfo(filePath);
   QString insertPath = fileInfo.absoluteFilePath();

   if (!fileInfo.exists() ||
       m_fileViewItems.contains(insertPath)) {
      return;
   }

   FileListItemView *listItemView = new FileListItemView;
   PlainTextView *plainTextView = new PlainTextView;
   QListWidgetItem *item = new QListWidgetItem(ui->fileListWidget);

   FileViewItems viewItems;
   viewItems.setFileListItemWidget(listItemView->listWidget());
   viewItems.setPlainTextEdit(plainTextView->textEdit());

   ui->stackedWidget->addWidget(plainTextView->textEdit());
   m_fileViewItems.insert(insertPath, viewItems);

   item->setData(FilePathDataRole, fileInfo.absoluteFilePath());
   ui->fileListWidget->addItem(item);
   FileListItemWidget *itemWidget = listItemView->listWidget();
   connect(itemWidget, &FileListItemWidget::closeFileRequested,
           [this, item] {
      closeFileItem(item);
   });
   itemWidget->setFileName(fileInfo.fileName());
   item->setSizeHint(itemWidget->sizeHint());
   ui->fileListWidget->setItemWidget(item, itemWidget);
   ui->fileListWidget->setCurrentRow(ui->fileListWidget->row(item));

   m_tailEngine->addFiles(fileInfo, {FileView(listItemView), FileView(plainTextView)});

   saveLastOpenedFiles();
}

void MainWindow::showFile(const QString &filePath)
{
   FileViewItems viewItems = m_fileViewItems.value(filePath);

   if (viewItems.plainTextEdit()) {
      ui->stackedWidget->setCurrentWidget(viewItems.plainTextEdit());
   }
}

void MainWindow::closeFileItem(QListWidgetItem *listItem)
{
   QString filePath = listItem->data(FilePathDataRole).toString();

   int itemRow = ui->fileListWidget->row(listItem);
   ui->fileListWidget->takeItem(itemRow);
   delete listItem;

   FileViewItems viewItems = m_fileViewItems.take(filePath);

   if (viewItems.fileListItemWidget()) {
      delete viewItems.fileListItemWidget();
   }
   if (viewItems.plainTextEdit()) {
      delete viewItems.plainTextEdit();
   }
}

void MainWindow::openLastOpenedFiles()
{
   QStringList lastOpenedFiles = m_settings.lastOpenedFiles();
   foreach (const QString &lastOpenedFile, lastOpenedFiles) {
      openFile(lastOpenedFile);
   }
}

void MainWindow::saveLastOpenedFiles()
{
   QStringList lastOpenFiles;
   for (int i=0; i<ui->fileListWidget->count(); ++i) {
      QString filePath = filePathOfFileListIndex(i);
      if (filePath.isEmpty()) {
         continue;
      }

      lastOpenFiles << filePath;
   }

   m_settings.setLastOpenedFiles(lastOpenFiles);
}

QString MainWindow::filePathOfFileListIndex(int index)
{
   if (index < 0 ||
       index >= ui->fileListWidget->count()) {
      return QStringLiteral("");
   }

   QListWidgetItem *listItem = ui->fileListWidget->item(index);
   if (!listItem) {
      return QStringLiteral("");
   }

   QString itemPath = listItem->data(FilePathDataRole).toString();
   return itemPath;
}

QPointer<PlainTextEdit> MainWindow::FileViewItems::plainTextEdit() const
{
   return m_plainTextEdit;
}

void MainWindow::FileViewItems::setPlainTextEdit(const QPointer<PlainTextEdit> &plainTextEdit)
{
   m_plainTextEdit = plainTextEdit;
}

QPointer<FileListItemWidget> MainWindow::FileViewItems::fileListItemWidget() const
{
   return m_fileListItemWidget;
}

void MainWindow::FileViewItems::setFileListItemWidget(const QPointer<FileListItemWidget> &fileListItemWidget)
{
   m_fileListItemWidget = fileListItemWidget;
}
