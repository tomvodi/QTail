/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "include/columnize/TextConfiguration.h"

class TextConfigurationData : public QSharedData
{
public:

};

TextConfiguration::TextConfiguration()
    : data(new TextConfigurationData)
{
   setType(ColumnType::Text);
}

TextConfiguration::TextConfiguration(const TextConfiguration &rhs)
    : data(rhs.data)
{

}

TextConfiguration &TextConfiguration::operator=(const TextConfiguration &rhs)
{
   if (this != &rhs)
      data.operator=(rhs.data);
   return *this;
}

TextConfiguration::~TextConfiguration()
{

}
