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
   void testTextViewFontChange();

private:
   Settings::SettingValue valueTypeFromSignal(const QVariantList &signal);
};

PreferencesDialogTest::PreferencesDialogTest()
{
   qRegisterMetaType<Settings::SettingValue>("Settings::SettingValue");
}

void PreferencesDialogTest::initTestCase()
{
   QCoreApplication::setOrganizationName("PreferencesDialogTest");
   QCoreApplication::setApplicationName("PreferencesDialogTest");
}

void PreferencesDialogTest::cleanupTestCase()
{
}

void PreferencesDialogTest::testTextViewFontChange()
{
   PreferencesDialog dialog;
   ApplicationSettings settings(new Settings);
   dialog.setSettings(settings);

   QSignalSpy spy(&dialog, SIGNAL(settingsHaveChanged(Settings::SettingValue)));

   QFont testFont = TestCommon::testFont();
   dialog.ui->textViewFontPicker->currentFontChanged(testFont);

   QVERIFY2(spy.count(), "Setting changed signal wasn't emitted");
   Settings::SettingValue parameterValue = valueTypeFromSignal(spy.first());
   QVERIFY2(parameterValue == Settings::TextViewSettings, "Wrong value type returned.");
   QVERIFY2(settings->textViewFont() == testFont, "Font wasn't set in settings.");
}

Settings::SettingValue PreferencesDialogTest::valueTypeFromSignal(const QVariantList &signal)
{
   if (!signal.count()) {
      qCritical() << "No parameter in signal";
      return Settings::NoValue;
   }

   Settings::SettingValue value = signal.first().value<Settings::SettingValue>();

   return value;
}

QTEST_MAIN(PreferencesDialogTest)

#include "tst_PreferencesDialogTest.moc"
