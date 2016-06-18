/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QSettings>

#include <TestCommon.h>

#include <gui/PreferencesDialog.h>
#include <ui_PreferencesDialog.h>

class PreferencesDialogTest : public QObject
{
   Q_OBJECT

public:
   PreferencesDialogTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testTextViewSettingsChange();
   void testSetSettings();

private:
   Settings::SettingCategory valueTypeFromSignal(const QVariantList &signal);
};

PreferencesDialogTest::PreferencesDialogTest()
{
   qRegisterMetaType<Settings::SettingCategory>("Settings::SettingCategory");
}

void PreferencesDialogTest::initTestCase()
{
   QCoreApplication::setOrganizationName("PreferencesDialogTest");
   QCoreApplication::setApplicationName("PreferencesDialogTest");
}

void PreferencesDialogTest::cleanupTestCase()
{
}

void PreferencesDialogTest::testTextViewSettingsChange()
{
   PreferencesDialog dialog;
   ApplicationSettings settings(new Settings);
   settings->setTextViewFont(QFont());
   dialog.setSettings(settings);

   QSignalSpy spy(&dialog, SIGNAL(settingsHaveChanged(Settings::SettingCategory)));

   QFont testFont = TestCommon::testFont();
   Q_ASSERT(settings->textViewFont() != dialog.ui->textViewFontPicker->currentFont());
   dialog.ui->textViewFontPicker->setCurrentFont(testFont);
   dialog.dialogAccepted();

   QVERIFY2(spy.count(), "Setting changed signal wasn't emitted");
   Settings::SettingCategory parameterValue = valueTypeFromSignal(spy.first());
   QVERIFY2(parameterValue == Settings::TextViewSettings, "Wrong value type returned.");
   QVERIFY2(settings->textViewFont() == testFont, "Font wasn't set in settings.");

   spy.clear();
   bool lineWrapOn = !dialog.ui->lineWrapCheckBox->isChecked();
   dialog.ui->lineWrapCheckBox->setChecked(lineWrapOn);
   dialog.dialogAccepted();
   QVERIFY2(spy.count(), "Setting changed signal wasn't emitted");
   parameterValue = valueTypeFromSignal(spy.first());
   QVERIFY2(parameterValue == Settings::TextViewSettings, "Wrong value type returned.");
   QVERIFY2(settings->textViewLineWrap() == lineWrapOn, "Line wrap value wasn't set in settings.");

   spy.clear();
   int currentUpdateIntervalIndex = dialog.ui->updateIntervalComboBox->currentIndex();
   if (currentUpdateIntervalIndex == 0) {
      currentUpdateIntervalIndex = 1;
   } else {
      currentUpdateIntervalIndex = 0;
   }

   dialog.ui->updateIntervalComboBox->setCurrentIndex(currentUpdateIntervalIndex);
   dialog.dialogAccepted();
   int currentSelectedIntervalData = dialog.ui->updateIntervalComboBox->currentData().toInt();
   QVERIFY2(spy.count(), "Setting changed signal wasn't emitted");
   parameterValue = valueTypeFromSignal(spy.first());
   QVERIFY2(parameterValue == Settings::TextViewSettings, "Wrong value type returned.");
   QVERIFY2(settings->textViewUpdateIntervalMs() == currentSelectedIntervalData, "Update interval value wasn't set in settings.");
}

void PreferencesDialogTest::testSetSettings()
{
   // Force dialog to use other settings
   QCoreApplication::setOrganizationName(QUuid::createUuid().toString());
   QCoreApplication::setApplicationName(QUuid::createUuid().toString());
   PreferencesDialog dialog;

   // Set right settings name for this test
   QCoreApplication::setOrganizationName("testSetSettings");
   QCoreApplication::setApplicationName("testSetSettings");
   ApplicationSettings settings(new Settings);

   // Set dialog ui to other values than stored in settings
   QFont testFont = settings->textViewFont();
   testFont.setPointSize(testFont.pointSize() + 4);
   testFont.setBold(!testFont.bold());
   dialog.ui->textViewFontPicker->setCurrentFont(testFont);

   bool lineWrapOn = !settings->textViewLineWrap();
   dialog.ui->lineWrapCheckBox->setChecked(lineWrapOn);

   int testUpdateInterval = 500;
   settings->setTextViewUpdateIntervalMs(testUpdateInterval);

   dialog.setSettings(settings);

   QVERIFY2(dialog.ui->textViewFontPicker->currentFont() == settings->textViewFont(),
            "Font wasn't set from settings");
   QVERIFY2(dialog.ui->lineWrapCheckBox->isChecked() == settings->textViewLineWrap(),
            "Text wrap wasn't set from settings");
   QVERIFY2(dialog.ui->updateIntervalComboBox->currentData().toInt() == settings->textViewUpdateIntervalMs(),
            "Update interval wasn't set from settings");
}

Settings::SettingCategory PreferencesDialogTest::valueTypeFromSignal(const QVariantList &signal)
{
   if (!signal.count()) {
      qCritical() << "No parameter in signal";
      return Settings::NoValue;
   }

   Settings::SettingCategory value = signal.first().value<Settings::SettingCategory>();

   return value;
}

QTEST_MAIN(PreferencesDialogTest)

#include "tst_PreferencesDialogTest.moc"
