/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef TAILENGINE_H
#define TAILENGINE_H

#include <QObject>

/*!
 * \brief The TailEngine class
 * The TailEngine encapsulates the tracking of file changes.
 */
class TailEngine : public QObject
{
    Q_OBJECT
public:
    explicit TailEngine(QObject *parent = 0);

};

#endif // TAILENGINE_H
