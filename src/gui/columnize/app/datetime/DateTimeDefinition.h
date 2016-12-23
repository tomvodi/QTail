/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef DATETIMEDEFINITION_H
#define DATETIMEDEFINITION_H

#include <QPointer>
#include <ColumnDefinitionInterface.h>

class DateTimeConfigWidget;

class DateTimeDefinition : public ColumnDefinitionInterface
{
public:
   DateTimeDefinition();
   ~DateTimeDefinition();

   // ColumnDefinitionInterface interface
public:
   QString name() const override;
   QString description() const override;
   QWidget *configWidget() const override;

private:
   QPointer<QWidget> m_configWidget;
};

#endif // DATETIMEDEFINITION_H
