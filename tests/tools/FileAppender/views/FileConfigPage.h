/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef FILECONFIGPAGE_H
#define FILECONFIGPAGE_H

#include <QFileInfo>
#include <QFrame>

namespace Ui {
class FileConfigPage;
}
class QTimer;
class QFile;

class FileConfigPage : public QFrame
{
   Q_OBJECT

public:
   explicit FileConfigPage(QWidget *parent = 0);
   ~FileConfigPage();

   void setFile(const QFileInfo &fileinfo);

private slots:
   void on_appendTextEdit_textChanged();
   void on_startStopAppendButton_clicked();
   void appendLinesToFile();

private:
   void setFileContent(const QString &fileContent);
   void checkEnabledStateOfStartStopButton();
   void setStartStopButtonTextForState(bool startable);
   QFileInfo m_fileInfo;
   Ui::FileConfigPage *ui;
   QTimer *m_appendLinesTimer = nullptr;
   QFile *m_file = nullptr;
};

#endif // FILECONFIGPAGE_H
