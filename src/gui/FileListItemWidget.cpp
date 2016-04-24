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
    setFileState(FileState::FileError);

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
    ui->lineCountLabel->setText(QString::number(lineCount));
}

void FileListItemWidget::setFileState(FileListItemWidget::FileState state)
{
    m_fileState = state;

    switch (state) {
    case FileState::FileError:
        ui->emblemLabel->setPixmap(QStringLiteral("://resources/icons/emblems/emblem-important.png"));
        break;
    case FileState::FileHasNewLines:
        ui->emblemLabel->setPixmap(QStringLiteral("://resources/icons/emblems/emblem-generic.png"));
        break;
    case FileState::FileInSync:
        ui->emblemLabel->setPixmap(QStringLiteral("://resources/icons/emblems/emblem-default.png"));
        break;
    }
}

FileListItemWidget::FileState FileListItemWidget::fileState() const
{
    return m_fileState;
}
