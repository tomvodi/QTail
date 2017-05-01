/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "include/columnize/ColumnConfiguration.h"

static const QString ColumnTypeKey("column type");

class ColumnConfigurationData : public QSharedData
{
public:
   QJsonObject configuration;
};

ColumnConfiguration::ColumnConfiguration()
   : data(new ColumnConfigurationData)
{

}

ColumnConfiguration::ColumnConfiguration(ColumnType type)
   : data(new ColumnConfigurationData)
{
   setType(type);
}

ColumnConfiguration::ColumnConfiguration(const ColumnConfiguration &rhs)
   : data(rhs.data)
{

}

ColumnConfiguration &ColumnConfiguration::operator=(const ColumnConfiguration &rhs)
{
   if (this != &rhs)
      data.operator=(rhs.data);
   return *this;
}

ColumnConfiguration::~ColumnConfiguration()
{

}

ColumnType ColumnConfiguration::type() const
{
   int value = data->configuration.value(ColumnTypeKey).toInt(static_cast<int>(ColumnType::None));
   return static_cast<ColumnType>(value);
}

void ColumnConfiguration::setType(const ColumnType &type)
{
   data->configuration.insert(ColumnTypeKey, static_cast<int>(type));
}

QJsonObject ColumnConfiguration::configuration() const
{
   return data->configuration;
}

void ColumnConfiguration::setConfiguration(const QJsonObject &configuration)
{
   data->configuration = configuration;
}

/*!
 * \brief ColumnConfiguration::insert
 * A convenience function for inserting values to the json object.
 */
void ColumnConfiguration::insert(const QString &key, const QJsonValue &value)
{
   data->configuration.insert(key, value);
}

/*!
 * \brief ColumnConfiguration::value
 * A convenience function for getting a value from the json object.
 */
QJsonValue ColumnConfiguration::value(const QString &key) const
{
   return data->configuration.value(key);
}
