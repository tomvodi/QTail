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
class QAbstractButton;

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

private slots:
   void on_buttonBox_clicked(QAbstractButton *button);
   void dialogAccepted();
   void dialogRejected();

private:
   void initUpdateIntervalComboBox();
   bool textViewSettingsHaveBeenModified() const;
   void writeTextViewSettings();
   Ui::PreferencesDialog *ui;
   ApplicationSettings m_settings;
};

#endif // PREFERENCESDIALOG_H
