/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */
#ifndef TESTCOMMON_H
#define TESTCOMMON_H

#include <QString>

class TestCommon
{
public:
    TestCommon();

    static QString generateExistingFilePath(const QString &fileName);
};

#endif // TESTCOMMON_H
