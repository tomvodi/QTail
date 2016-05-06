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
   m_file = fileinfo;
   ui->fileNameLabel->setText(m_file.fileName());

   QFile file(m_file.absoluteFilePath());
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
   QFile appendFile(m_file.absoluteFilePath());
   if (!appendFile.open(QIODevice::Append | QIODevice::Text)) {
      qWarning() << "Failed opening file for appending lines";
      return;
   }

   QString appendText = ui->appendTextEdit->toPlainText();
   if (!appendText.endsWith('\n') ||
       appendText.endsWith('\r')) {
      appendText.append('\n');
   }

   QTextStream stream(&appendFile);
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
