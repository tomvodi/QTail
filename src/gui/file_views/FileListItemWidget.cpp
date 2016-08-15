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

   setFileName("");
   setLineCount(0);
   setFileState(FileState::FileInSync);

   connect(ui->closeButton, &QToolButton::clicked,
           this, &FileListItemWidget::closeFileRequested);
}

FileListItemWidget::~FileListItemWidget()
{
   delete ui;
}

void FileListItemWidget::setFileName(const QString &fileName)
{
   ui->fileNameLabel->setText(fileName);
}

QString FileListItemWidget::fileName() const
{
   return ui->fileNameLabel->text();
}

void FileListItemWidget::setLineCount(quint64 lineCount)
{
   m_lineCount = lineCount;
   QString lineCountText;
   if (lineCount > 0) {
      lineCountText = QString::number(lineCount);
   }
   ui->lineCountLabel->setVisible(lineCount > 0);

   ui->lineCountLabel->setText(lineCountText);
}

void FileListItemWidget::addLineCount(quint64 lineCount)
{
   m_lineCount += lineCount;
   setLineCount(m_lineCount);
}

void FileListItemWidget::setFileState(FileState state)
{
   m_fileState = state;

   ui->emblemLabel->setVisible(true);

   switch (state) {
   case FileState::FileError:
      ui->emblemLabel->setPixmap(QStringLiteral("://resources/icons/emblems/emblem-important.png"));
      break;
   case FileState::FileHasChanged:
      ui->emblemLabel->setPixmap(QStringLiteral("://resources/icons/emblems/emblem-generic.png"));
      break;
   case FileState::FileInSync:
      ui->emblemLabel->setVisible(false);
      ui->emblemLabel->setPixmap(QStringLiteral("://resources/icons/emblems/emblem-placeholder.png"));
      break;
   }
}

FileState FileListItemWidget::fileState() const
{
   return m_fileState;
}

void FileListItemWidget::changeEvent(QEvent *e)
{
   QFrame::changeEvent(e);
   switch (e->type()) {
   case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
   default:
      break;
   }
}

qint64 FileListItemWidget::lineCount() const
{
   return m_lineCount;
}
