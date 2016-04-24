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

#include "AboutDialog.h"
#include "PlainTextEdit.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "FileListItemWidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_textEdit = new PlainTextEdit;
    ui->centralLayout->addWidget(m_textEdit);

    createConnections();
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
       QString filePath = item->data(Qt::UserRole + 1).toString();
       showFile(filePath);
    });
}

void MainWindow::openFile(const QString &filePath)
{
    QFileInfo fileInfo(filePath);

    if (!fileInfo.exists() ||
            listWidgetContainsFile(filePath)) {
        return;
    }

    QListWidgetItem *item = new QListWidgetItem(ui->fileListWidget);
    item->setData(Qt::UserRole + 1, fileInfo.absoluteFilePath());
    ui->fileListWidget->addItem(item);
    FileListItemWidget *itemWidget = new FileListItemWidget;
    itemWidget->setFileName(fileInfo.fileName());
    item->setSizeHint(itemWidget->sizeHint());
    ui->fileListWidget->setItemWidget(item, itemWidget);
    ui->fileListWidget->setCurrentRow(0);
}

void MainWindow::showFile(const QString &filePath)
{
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);

    QString fileText = stream.readAll();
    m_textEdit->setPlainText(fileText);
}

bool MainWindow::listWidgetContainsFile(const QString &filePath)
{
    for (int i=0; i<ui->fileListWidget->count(); ++i) {
        QString listFilePath = ui->fileListWidget->item(i)->data(Qt::UserRole + 1).toString();
        if (listFilePath == filePath) {
            return true;
        }
    }

    return false;
}

