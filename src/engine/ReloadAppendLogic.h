/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef RELOADAPPENDLOGIC_H
#define RELOADAPPENDLOGIC_H

#include <QFileInfo>

/*!
 * \brief The ReloadAppendLogic class
 * This class handles when to completely reload a file and when to simply append text to a file view.
 */
class ReloadAppendLogic
{
public:
   ReloadAppendLogic();

   QFileInfo file() const;
   void setFile(const QFileInfo &file);

   bool shouldReload() const;

   void setNewSize(qint64 newSize);

   qint64 oldSize() const;

private:
   QFileInfo m_file;
   qint64 m_oldSize = 0;
};

#endif // RELOADAPPENDLOGIC_H
