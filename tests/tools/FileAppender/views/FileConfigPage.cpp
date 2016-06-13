/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QTimer>
#include <QDebug>

#include "FileConfigPage.h"
#include "ui_FileConfigPage.h"

FileConfigPage::FileConfigPage(QWidget *parent) :
   QFrame(parent),
   ui(new Ui::FileConfigPage),
   m_appendLinesTimer(new QTimer(this))
{
   ui->setupUi(this);
   checkEnabledStateOfStartStopButton();
   setStartStopButtonTextForState(true);
   connect(m_appendLinesTimer, &QTimer::timeout,
           this, &FileConfigPage::appendLinesToFile);
}

FileConfigPage::~FileConfigPage()
{
   delete ui;
}

void FileConfigPage::setFile(const QFileInfo &fileinfo)
{
   m_fileInfo = fileinfo;
   ui->fileNameLabel->setText(m_fileInfo.fileName());

   if (m_file) {
      delete m_file;
      m_file = nullptr;
   }

   m_file = new QFile(m_fileInfo.absoluteFilePath(), this);
   m_file->open(QIODevice::Append);

   QFile file(m_fileInfo.absoluteFilePath());
   file.open(QIODevice::ReadOnly);
   setFileContent(file.readAll());
}

void FileConfigPage::setFileContent(const QString &fileContent)
{
   ui->fileContentTextEdit->setPlainText(fileContent);
}

void FileConfigPage::on_appendTextEdit_textChanged()
{
   checkEnabledStateOfStartStopButton();
}

void FileConfigPage::on_startStopAppendButton_clicked()
{
   if (m_appendLinesTimer->isActive()) {
      m_appendLinesTimer->stop();
      setStartStopButtonTextForState(true);
      ui->appendTextEdit->setReadOnly(false);
   } else {
      m_appendLinesTimer->start(ui->appendIntervalSpinBox->value());
      setStartStopButtonTextForState(false);
      ui->appendTextEdit->setReadOnly(true);
   }
}

void FileConfigPage::appendLinesToFile()
{
   if (!m_file) {
      return;
   }

   QString appendText = ui->appendTextEdit->toPlainText();
   ui->fileContentTextEdit->appendPlainText(appendText);

   if (!appendText.endsWith('\n') ||
       appendText.endsWith('\r')) {
      appendText.append('\n');
   }

   QTextStream stream(m_file);
   stream << appendText;
   stream.flush();
}

void FileConfigPage::checkEnabledStateOfStartStopButton()
{
   bool buttonEnabled = true;
   if (ui->appendTextEdit->toPlainText().isEmpty()) {
      buttonEnabled = false;
   }

   ui->startStopAppendButton->setEnabled(buttonEnabled);
}

void FileConfigPage::setStartStopButtonTextForState(bool startable)
{
   if (startable) {
      ui->startStopAppendButton->setText(tr("Start Appending Lines"));
   } else {
      ui->startStopAppendButton->setText(tr("Stop Appending Lines"));
   }
}
