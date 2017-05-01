/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QLocale>

#include "include/columnize/DateTimeConfigurationHelper.h"

static const QString LocaleConfigKey("datetime locale");
static const QString FormatConfigKey("format");

DateTimeConfigurationHelper::DateTimeConfigurationHelper(const ColConfig &config)
   : ColumnConfigurationHelper(config)
{
}

void DateTimeConfigurationHelper::setLocale(const QLocale &locale)
{
   insert(LocaleConfigKey, locale.name());
}

QLocale DateTimeConfigurationHelper::locale() const
{
   QString localeString(value(LocaleConfigKey).toString());
   return QLocale(localeString);
}

QString DateTimeConfigurationHelper::format() const
{
   return value(FormatConfigKey).toString();
}

void DateTimeConfigurationHelper::setFormat(const QString &format)
{
   insert(FormatConfigKey, format);
}
