/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QListWidget>
#include <QFileDialog>
#include <QVersionNumber>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QTranslator>

#include <QTail_version.h>
#include <TailEngine.h>
#include <include/FilterGroup.h>

#include "file_views/PlainTextView.h"
#include "file_views/FileListItemView.h"
#include "file_views/FileListItemWidget.h"

#include "highlighting/HighlightingDialog.h"

#include "PreferencesDialog.h"
#include "filter/FilterDialog.h"
#include "filter/FileFilterWidget.h"
#include "AboutDialog.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow),
   m_settings(new Settings),
   m_highlightingDialog(new HighlightingDialog(this)),
   m_preferencesDialog(new PreferencesDialog(this)),
   m_filterDialog(new FilterDialog(this)),
   m_fileFilterWidget(new FileFilterWidget(this))
{
   ui->setupUi(this);

   m_preferencesDialog->setSettings(m_settings);
   m_highlightingDialog->setHighlightingRules(m_settings->lineHighlightingRules(),
                                              m_settings->wordHighlightingRules());
   m_filterDialog->setFilterGroups(m_settings->filterGroups());
   m_fileFilterWidget->setFilterGroups(m_settings->filterGroups());
   ui->filterDockWidgetContentLayout->addWidget(m_fileFilterWidget);

   m_tailEngine = new TailEngine(this);
   TextViewSettings textViewSettings;
   textViewSettings.setFont(m_settings->textViewFont());
   textViewSettings.setLineWrapOn(m_settings->textViewLineWrap());
   textViewSettings.setUpdateInterval(m_settings->textViewUpdateIntervalMs());
   m_tailEngine->setTextViewSettings(textViewSettings);

   setGuiLanguage(m_settings->guiLanguage());
   createConnections();
   openLastOpenedFiles();
   initRecentlyOpenedFilesMenu();

   restoreGeometry(m_settings->mainWindowGeometry());
   restoreState(m_settings->mainWindowState());
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
   QStringList filePaths = QFileDialog::getOpenFileNames(this, tr("Open file"), m_settings->lastOpenDir().absolutePath(),
                                                         QStringLiteral("All files *.*"));

   if (filePaths.isEmpty()) {
      return;
   }

   m_settings->setLastOpenDir(QFileInfo(filePaths.first()).absoluteDir());

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

void MainWindow::on_actionHighlighting_triggered()
{
   m_highlightingDialog->show();
}

void MainWindow::on_actionPreferences_triggered()
{
   m_preferencesDialog->show();
}

void MainWindow::on_actionFilter_triggered()
{
   m_filterDialog->show();
}

void MainWindow::settingsValueHasChanged(Settings::SettingCategory valueType)
{
   switch (valueType) {
   case Settings::NoValue:
      break;
   case Settings::TextViewSettings:
      TextViewSettings textViewSettings;
      textViewSettings.setFont(m_settings->textViewFont());
      textViewSettings.setLineWrapOn(m_settings->textViewLineWrap());
      textViewSettings.setUpdateInterval(m_settings->textViewUpdateIntervalMs());

      foreach (const FileViewItems &fileView, m_fileViewItems) {
         if (fileView.listWidget()) {
            m_tailEngine->setTextViewSettings(textViewSettings);
         }
      }
      break;
   }
}

void MainWindow::changeActiveFileFiltersOfCurrentFile(const QList<FilterRule> &filterRules)
{
   QListWidgetItem *currentItem = ui->fileListWidget->currentItem();
   if (!currentItem) {
      return;
   }

   QString filePath = currentItem->data(FilePathDataRole).toString();
   if (filePath.isEmpty()) {
      return;
   }

   m_tailEngine->setActiveFiltersForFile(filePath, filterRules);

   QList<QUuid> filterIds;
   foreach (const FilterRule &rule, filterRules) {
      filterIds.append(rule.id());
   }

   OpenFileSettings fileSettings = m_settings->openFileSettingsForFile(filePath);
   fileSettings.setActiveFilterIds(filterIds);
   m_settings->setOpenFileSettingsForFile(filePath, fileSettings);
}

void MainWindow::on_fileListWidget_currentItemChanged(QListWidgetItem *currentItem, QListWidgetItem *previousItem)
{
   if (!currentItem) {
      return;
   }

   QString filePath = currentItem->data(FilePathDataRole).toString();
   showFile(filePath);
   m_tailEngine->setFileActive(filePath, true);

   OpenFileSettings fileSettings = m_settings->openFileSettingsForFile(filePath);
   m_fileFilterWidget->setActiveFilterIds(fileSettings.activeFilterIds());

   if (previousItem) {
      QString filePath = previousItem->data(FilePathDataRole).toString();
      m_tailEngine->setFileActive(filePath, false);
   }
}

void MainWindow::setSelectedLanguage(const QString &language)
{
   m_settings->setGuiLanguage(language);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
   if (event->mimeData()->hasUrls()) {
      event->acceptProposedAction();
   }
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
   if (event->mimeData()->hasUrls()) {
      event->acceptProposedAction();
   }
}

void MainWindow::dropEvent(QDropEvent *event)
{
   foreach (const QUrl &url, event->mimeData()->urls()) {
      if (!url.isLocalFile()) {
         continue;
      }
      QString filePath = url.toString(QUrl::PreferLocalFile);
      QFileInfo fileInfo(filePath);

      if (fileInfo.isFile()) {
         openFile(fileInfo.absoluteFilePath());
      }
      if (fileInfo.isDir()) {
         openDir(fileInfo.absoluteFilePath());
      }
   }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
   m_settings->setMainWindowGeometry(saveGeometry());
   m_settings->setMainWindowState(saveState());
   QMainWindow::closeEvent(event);
}

void MainWindow::changeEvent(QEvent *event)
{
   if (event->type() == QEvent::LanguageChange) {
      ui->retranslateUi(this);
   }

   QMainWindow::changeEvent(event);
}

void MainWindow::createConnections()
{
   connect(m_highlightingDialog, &HighlightingDialog::highlightingRulesChanged,
           [this] (const QList<HighlightingRule> &lineRules, const QList<HighlightingRule> &wordRules) {
      m_settings->setHighlightingRules(lineRules, wordRules);
   });

   connect(m_preferencesDialog, &PreferencesDialog::settingsHaveChanged,
           this, &MainWindow::settingsValueHasChanged);
   connect(m_filterDialog, &FilterDialog::filterGroupsChanged,
           [this] (const QList<FilterGroup> &filterGroups) {
      m_settings->setFilterGroups(filterGroups);
      m_fileFilterWidget->setFilterGroups(filterGroups);
   });

   connect(m_fileFilterWidget, &FileFilterWidget::activeFilterRulesChanged,
           this, &MainWindow::changeActiveFileFiltersOfCurrentFile);
   connect(m_preferencesDialog, &PreferencesDialog::selectedLanguageChanged,
           this, &MainWindow::setSelectedLanguage);
}

/*!
 * \brief MainWindow::openFile
 * \param filePath The path to the file to open.
 * \param justOpenFile If set to true, opening the file won't save the last opened files
 * or the recently opened files.
 */
void MainWindow::openFile(const QString &filePath, bool justOpenFile)
{
   QFileInfo fileInfo(filePath);
   QString insertPath = fileInfo.absoluteFilePath();

   if (!fileInfo.exists() ||
       m_fileViewItems.contains(insertPath)) {
      return;
   }

   FileListItemView *listItemView = new FileListItemView(this);
   PlainTextView *plainTextView = new PlainTextView(this);
   OpenFileSettings fileSettings = m_settings->openFileSettingsForFile(fileInfo.absoluteFilePath());
   QList<FilterRule> activeFilterRules = FilterGroup::activeRulesForIds(m_settings->filterGroups(),
                                                                        fileSettings.activeFilterIds());
   m_tailEngine->setActiveFiltersForFile(fileInfo, activeFilterRules);
   m_tailEngine->addFiles(fileInfo, {FileView(listItemView), FileView(plainTextView)});

   plainTextView->setHighlightingRules(m_settings->lineHighlightingRules(), m_settings->wordHighlightingRules());
   connect(m_highlightingDialog, &HighlightingDialog::highlightingRulesChanged,
           plainTextView, &PlainTextView::setHighlightingRules);
   QListWidgetItem *item = new QListWidgetItem(ui->fileListWidget);

   FileViewItems viewItems;
   viewItems.setListWidget(listItemView->widget());
   viewItems.setViewWidget(plainTextView->widget());

   ui->stackedWidget->addWidget(plainTextView->widget());
   m_fileViewItems.insert(insertPath, viewItems);

   item->setData(FilePathDataRole, fileInfo.absoluteFilePath());
   item->setData(Qt::ToolTipRole, fileInfo.absoluteFilePath());
   ui->fileListWidget->addItem(item);
   QWidget *itemWidget = listItemView->widget();
   connect(listItemView, &FileListItemView::requestCloseFile,
           [this, item] {
      closeFileItem(item);
   });
   item->setSizeHint(itemWidget->sizeHint());
   ui->fileListWidget->setItemWidget(item, itemWidget);
   ui->fileListWidget->setCurrentRow(ui->fileListWidget->row(item));

   if (!justOpenFile) {
      saveLastOpenedFiles();
      addRecentlyOpenedFile(fileInfo);
   }
}

void MainWindow::openDir(const QString &dirPath)
{
   QDir dir(dirPath);
   foreach (const QFileInfo &fileInfo, dir.entryInfoList()) {
      if (!fileInfo.isFile()) {
         continue;
      }

      openFile(fileInfo.absoluteFilePath());
   }
}

void MainWindow::showFile(const QString &filePath)
{
   statusBar()->showMessage(filePath);
   FileViewItems viewItems = m_fileViewItems.value(filePath);

   if (viewItems.viewWidget()) {
      ui->stackedWidget->setCurrentWidget(viewItems.viewWidget());
   }
}

void MainWindow::closeFileItem(QListWidgetItem *listItem)
{
   QString filePath = listItem->data(FilePathDataRole).toString();

   m_tailEngine->removeFile(filePath);

   int itemRow = ui->fileListWidget->row(listItem);
   ui->fileListWidget->takeItem(itemRow);
   delete listItem;

   FileViewItems viewItems = m_fileViewItems.take(filePath);

   if (viewItems.listWidget()) {
      delete viewItems.listWidget();
   }
   if (viewItems.viewWidget()) {
      delete viewItems.viewWidget();
   }

   saveLastOpenedFiles();
}

void MainWindow::openLastOpenedFiles()
{
   QStringList lastOpenedFiles = m_settings->lastOpenedFiles();
   foreach (const QString &lastOpenedFile, lastOpenedFiles) {
      openFile(lastOpenedFile, true);
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

   m_settings->setLastOpenedFiles(lastOpenFiles);
}

void MainWindow::saveRecentlyOpenedFiles()
{
   QStringList recentlyOpenedFiles;
   foreach (QAction *action, ui->menuRecentFiles->actions()) {
      QString filePath = action->data().toString();
      if (filePath.isEmpty()) {
         continue;
      }

      recentlyOpenedFiles << filePath;
   }

   m_settings->setRecentlyOpenedFiles(recentlyOpenedFiles);
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

void MainWindow::addRecentlyOpenedFile(const QFileInfo &fileInfo)
{
   QAction *mostRecentAction = new QAction(fileInfo.fileName(), this);
   mostRecentAction->setData(fileInfo.absoluteFilePath());
   connect(mostRecentAction, &QAction::triggered,
           [this, fileInfo] {
      openFile(fileInfo.absoluteFilePath());
   });

   QList<QAction*> actions = ui->menuRecentFiles->actions();
   QList<QAction*> newActions;
   foreach (QAction *action, actions) {
      ui->menuRecentFiles->removeAction(action);

      // Add to new actions list only if it doesn't point to same file as the one
      // that should be added.
      if (action->data().toString() != fileInfo.absoluteFilePath()) {
         newActions.append(action);
      }
   }

   newActions.prepend(mostRecentAction);
   ui->menuRecentFiles->addActions(newActions);

   saveRecentlyOpenedFiles();
}

void MainWindow::initRecentlyOpenedFilesMenu()
{
   foreach (const QString &recentFile, m_settings->recentlyOpenedFiles()) {
      if (recentFile.isEmpty()) {
         continue;
      }

      QFileInfo fileInfo(recentFile);
      addRecentlyOpenedFile(fileInfo);
   }
}

void MainWindow::setGuiLanguage(const QString &language)
{
   QStringList availableTranslations;
   QString selectedTranslation("en");

   QDir translationsDir(":/translations");
   foreach (const QFileInfo &translationFile, translationsDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot)) {
      QString fileName = translationFile.baseName();
      QStringList fileParts = fileName.split('_');
      if (fileParts.count() != 2) {
         continue;
      }
      QString fileLanguage = fileParts.at(1);
      availableTranslations << fileLanguage;

      if (fileLanguage == language) {
         selectedTranslation = language;
         QTranslator *translator = new QTranslator(this);
         translator->load(translationFile.absoluteFilePath());
         qApp->installTranslator(translator);
      }
   }

   m_preferencesDialog->setAvailableTranslations(availableTranslations);
   m_preferencesDialog->setSelectedTranslation(selectedTranslation);

   QLocale defaultLocale(language);
   QLocale::setDefault(defaultLocale);
}

QPointer<FileListItemWidget> MainWindow::FileViewItems::fileListItemWidget() const
{
   return m_fileListItemWidget;
}

void MainWindow::FileViewItems::setFileListItemWidget(const QPointer<FileListItemWidget> &fileListItemWidget)
{
   m_fileListItemWidget = fileListItemWidget;
}

QPointer<QWidget> MainWindow::FileViewItems::viewWidget() const
{
   return m_viewWidget;
}

void MainWindow::FileViewItems::setViewWidget(const QPointer<QWidget> &viewWidget)
{
   m_viewWidget = viewWidget;
}

QPointer<QWidget> MainWindow::FileViewItems::listWidget() const
{
   return m_listWidget;
}

void MainWindow::FileViewItems::setListWidget(const QPointer<QWidget> &listWidget)
{
   m_listWidget = listWidget;
}
