/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef VIEWAPPLICATION_H
#define VIEWAPPLICATION_H

#include <include/ApplicationInterface.h>

#include <QPointer>

class HighlightingDialog;

/*!
 * \brief The ViewApplication class
 * Is the implementation for the ApplicationInterface that is used by the views to communicate
 * with the application.
 */
class ViewApplication : public ApplicationInterface
{
public:
   ViewApplication();

   // ApplicationInterface interface
public:
   void addWordHighlightingRule(const HighlightingRule &rule) override;
   void addLineHighlightingRule(const HighlightingRule &rule) override;

   QPointer<HighlightingDialog> highlightingDialog() const;
   void setHighlightingDialog(const QPointer<HighlightingDialog> &highlightingDialog);

private:
   QPointer<HighlightingDialog> m_highlightingDialog;
};

#endif // VIEWAPPLICATION_H
