/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef PLAINTEXTVIEW_H
#define PLAINTEXTVIEW_H

#include <QPointer>

#include <include/FileViewInterface.h>

class PlainTextViewWidget;

class PlainTextView : public FileViewInterface
{
   friend class PlainTextViewTest;

public:
   PlainTextView(QObject *parent=0);

   // FileViewInterface interface
   FileViewInterface::Features viewFeatures() const override;
   void appendLine(const QString &line) override;
   void appendLines(const QStringList &lines) override;
   void clearTextView() override;
   QPointer<QWidget> widget() const override;

   void setHighlightingRules(const QList<HighlightingRule> &lineRules,
                             const QList<HighlightingRule> &wordRules) override;

private:
   QPointer<PlainTextViewWidget> m_textEdit;
};

#endif // PLAINTEXTVIEW_H
