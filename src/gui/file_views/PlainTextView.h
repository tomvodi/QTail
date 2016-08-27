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
#include <include/FilterRule.h>

class PlainTextViewWidget;
class SyntaxHighlighter;
class QTextDocument;

class PlainTextView : public FileViewInterface
{
   friend class PlainTextViewTest;

public:
   PlainTextView(QObject *parent=0);

   // FileViewInterface interface
   void setApplicationInterface(const Application &app) override;
   FileViewInterface::Features viewFeatures() const override;
   void appendLine(const QString &line) override;
   void appendLines(const QStringList &lines) override;
   void clearTextView() override;
   void readCompleteFileUntil(qint64 maxLength) override;
   QPointer<QWidget> widget() const override;
   void setTextViewSettings(const TextViewSettings &settings) override;
   void setActiveFilters(const QList<FilterRule> &filters);
   QTextDocument *textDocument() const override;

public slots:
   void setHighlightingRules(const QList<HighlightingRule> &lineRules,
                             const QList<HighlightingRule> &wordRules) override;

private:
   QPointer<QTextDocument> m_textDocument;
   QPointer<PlainTextViewWidget> m_textEdit;
   QPointer<SyntaxHighlighter> m_syntaxHighlighter;
   QList<FilterRule> m_activeFilters;
   inline bool lineMatchesAtLeastOneFilter(const QString &line) const;
};

#endif // PLAINTEXTVIEW_H
