/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef FILEFILTERWIDGET_H
#define FILEFILTERWIDGET_H

#include <QFrame>

#include <include/FilterGroup.h>

namespace Ui {
class FileFilterWidget;
}

/*!
 * \brief The FileFilterWidget class
 * Apart from the FilterDialog which lets add/edit/delete filters and filter groups,
 * this widget shows the activated filters for a specific open file.
 */
class FileFilterWidget : public QFrame
{
   Q_OBJECT
   friend class FileFilterWidgetTest;

public:
   explicit FileFilterWidget(QWidget *parent = 0);
   ~FileFilterWidget();

   void setFilterGroups(const QList<FilterGroup> &groups);

private:
   enum TreeItemType {
      FilterGroupType,
      FilterRuleType
   };
   void setUiForFilterGroups(const QList<FilterGroup> &groups);
   Ui::FileFilterWidget *ui;
   QList<FilterGroup> m_filterGroups;
};

#endif // FILEFILTERWIDGET_H
