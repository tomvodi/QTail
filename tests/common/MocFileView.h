/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef MOCFILEVIEW_H
#define MOCFILEVIEW_H

#include <include/FileViewInterface.h>
#include <include/FilterGroup.h>
#include <include/TextViewSettings.h>

class MocFileView : public FileViewInterface
{
public:
   MocFileView(QObject *parent=0);

   // FileViewInterface interface
   FileViewInterface::Features viewFeatures() const override;
   void setFileState(FileState state) override;
   void appendLine(const QString &line) override;
   void appendLines(const QStringList &lines) override;
   void clearTextView() override;
   void readCompleteFileUntil(qint64 maxLength) override;
   void setFileInfo(const QFileInfo &fileInfo) override;
   void setFileActive(bool active) override;
   void setTextViewSettings(const TextViewSettings &textViewSettings);
   void setFilterGroups(const QList<FilterGroup> &filterGroups) override;

   QStringList textViewLines() const;
   void setViewFeatures(const FileViewInterface::Features &viewFeatures);
   FileState fileState() const;
   bool fileStateWasSetByInterfaceMethod() const;
   QFileInfo fileInfo() const;

   qint64 readUntilMaxLength() const;
   bool fileActive() const;
   TextViewSettings textViewSettings() const;

   QList<FilterGroup> filterGroups() const;

private:
   void setTextViewLines(const QStringList &textViewLines);
   QStringList m_textViewLines;
   FileViewInterface::Features m_viewFeatures = FileViewInterface::NoFeature;
   FileState m_fileState = FileState::FileInSync;
   bool m_fileStateWasSetByInterfaceMethod = false;
   QFileInfo m_fileInfo;
   qint64 m_readUntilMaxLength = -1;
   bool m_fileActive = false;
   QFont m_textViewFont;
   TextViewSettings m_textViewSettings;
   QList<FilterGroup> m_filterGroups;
};

#endif // MOCFILEVIEW_H
