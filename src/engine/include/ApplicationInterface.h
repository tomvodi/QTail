/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef APPLICATIONINTERFACE_H
#define APPLICATIONINTERFACE_H

#include <QSharedPointer>

#include "HighlightingRule.h"

/*!
 * \brief The ApplicationInterface class
 * This interface is used for communication from the views (FileViewInterface) to the application.
 */
class ApplicationInterface
{
public:
   ApplicationInterface();
   virtual ~ApplicationInterface();

   virtual void addWordHighlightingRule(const HighlightingRule &rule) = 0;
   virtual void addLineHighlightingRule(const HighlightingRule &rule) = 0;
};

typedef QSharedPointer<ApplicationInterface> Application;

#endif // APPLICATIONINTERFACE_H
