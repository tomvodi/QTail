/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "ReloadAppendLogic.h"

ReloadAppendLogic::ReloadAppendLogic()
{

}

QFileInfo ReloadAppendLogic::file() const
{
    return m_file;
}

void ReloadAppendLogic::setFile(const QFileInfo &file)
{
    m_file = file;
}

bool ReloadAppendLogic::shouldReload() const
{
   bool reload = false;

   if (m_oldSize == 0) {
      reload = true;
   }

   return reload;
}

void ReloadAppendLogic::setNewSize(qint64 newSize)
{
   m_oldSize = newSize;
}

qint64 ReloadAppendLogic::oldSize() const
{
   return m_oldSize;
}
