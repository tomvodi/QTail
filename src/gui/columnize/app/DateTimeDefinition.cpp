/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "DateTimeConfigWidget.h"
#include "DateTimeDefinition.h"

DateTimeDefinition::DateTimeDefinition()
   : m_configWidget(new DateTimeConfigWidget)
{
}

DateTimeDefinition::~DateTimeDefinition()
{
   delete m_configWidget;
}

QString DateTimeDefinition::name() const
{
   return QObject::tr("Timestamp");
}

QString DateTimeDefinition::description() const
{
   return QObject::tr("A column with a timestamp in a configurable format.");
}

QWidget *DateTimeDefinition::configWidget() const
{
   return m_configWidget.data();
}
