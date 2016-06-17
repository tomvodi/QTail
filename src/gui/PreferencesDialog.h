/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>

#include <include/TextViewSettings.h>

#include "tools/Settings.h"

namespace Ui {
class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
   Q_OBJECT
   friend class PreferencesDialogTest;

public:
   explicit PreferencesDialog(QWidget *parent = 0);
   ~PreferencesDialog();

   ApplicationSettings settings() const;
   void setSettings(const ApplicationSettings &settings);

signals:
   void settingsHaveChanged(Settings::SettingCategory valueType);

private:
   Ui::PreferencesDialog *ui;
   ApplicationSettings m_settings;
};

#endif // PREFERENCESDIALOG_H
