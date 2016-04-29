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

class MocFileView : public FileViewInterface
{
public:
   MocFileView();

   // FileViewInterface interface
   FileViewInterface::Features viewFeatures() const override;
   void setFileState(FileState state) override;
   void appendLine(const QString &line) override;
   void appendLines(const QStringList &lines) override;
   void clearTextView() override;

   QStringList textViewLines() const;
   void setViewFeatures(const FileViewInterface::Features &viewFeatures);
   FileState fileState() const;
   bool fileStateWasSetByInterfaceMethod() const;

private:
   void setTextViewLines(const QStringList &textViewLines);
   QStringList m_textViewLines;
   FileViewInterface::Features m_viewFeatures = FileViewInterface::NoFeature;
   FileState m_fileState = FileState::FileInSync;
   bool m_fileStateWasSetByInterfaceMethod = false;
};

#endif // MOCFILEVIEW_H
