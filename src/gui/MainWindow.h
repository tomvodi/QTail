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

#include "tools/Settings.h"

namespace Ui {
class MainWindow;
}
class TailEngine;
class FileListItemWidget;
class QListWidgetItem;
class HighlightingDialog;
class PreferencesDialog;

class MainWindow : public QMainWindow
{
   Q_OBJECT
   friend class MainWindowTest;

public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

private slots:
   void on_actionOpen_triggered();
   void on_actionAbout_triggered();
   void on_actionHighlighting_triggered();
   void on_actionPreferences_triggered();
   void settingsValueHasChanged(Settings::SettingValue valueType);

protected:
   void dragEnterEvent(QDragEnterEvent *event);
   void dragMoveEvent(QDragMoveEvent *event);
   void dropEvent(QDropEvent *event);

private:
   class FileViewItems {
   public:
      FileViewItems() {}

      QPointer<FileListItemWidget> fileListItemWidget() const;
      void setFileListItemWidget(const QPointer<FileListItemWidget> &fileListItemWidget);

      QPointer<QWidget> viewWidget() const;
      void setViewWidget(const QPointer<QWidget> &viewWidget);

      QPointer<QWidget> listWidget() const;
      void setListWidget(const QPointer<QWidget> &listWidget);

   private:
      QPointer<QWidget> m_viewWidget;
      QPointer<QWidget> m_listWidget;
      QPointer<FileListItemWidget> m_fileListItemWidget;
   };

   static const int FilePathDataRole = Qt::UserRole + 1;

   void createConnections();
   void openFile(const QString &filePath, bool justOpenFile=false);
   void openDir(const QString &dirPath);
   void showFile(const QString &filePath);
   void closeFileItem(QListWidgetItem *listItem);
   void openLastOpenedFiles();
   void saveLastOpenedFiles();
   void saveRecentlyOpenedFiles();
   QString filePathOfFileListIndex(int index);
   void addRecentlyOpenedFile(const QFileInfo &fileInfo);
   void initRecentlyOpenedFilesMenu();
   Ui::MainWindow *ui;
   ApplicationSettings m_settings;
   TailEngine *m_tailEngine = nullptr;
   QHash<QString, FileViewItems> m_fileViewItems;  // Hash for absolute file path -> FileViewItems
   HighlightingDialog *m_highlightingDialog;
   PreferencesDialog *m_preferencesDialog;
};

#endif // MAINWINDOW_H
