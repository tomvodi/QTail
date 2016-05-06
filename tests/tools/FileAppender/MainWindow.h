/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHash>
#include <QFileInfo>
#include <QPointer>
#include <QMainWindow>

#include <tools/Settings.h>

namespace Ui {
class MainWindow;
}
class FileListItemWidget;
class FileConfigPage;
class QListWidgetItem;

class FilAppenderMainWindow : public QMainWindow
{
   Q_OBJECT
   friend class MainWindowTest;

public:
   explicit FilAppenderMainWindow(QWidget *parent = 0);
   ~FilAppenderMainWindow();

private slots:
   void on_actionOpen_triggered();

private:
   static const int FilePathDataRole = Qt::UserRole + 1;

   void createConnections();
   void openFile(const QString &filePath);
   void closeFileItem(QListWidgetItem *listItem);
   void showFile(const QString &filePath);
   Ui::MainWindow *ui;
   Settings m_settings;
   QHash<QString, FileConfigPage*> m_fileConfigPages;  // Hash for absolute file path -> FileConfigPage
};

#endif // MAINWINDOW_H
