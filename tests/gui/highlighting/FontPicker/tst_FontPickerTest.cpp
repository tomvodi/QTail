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
#include <QFontDatabase>

#include <TestCommon.h>
#include <highlighting/FontPicker.h>
#include <ui_FontPicker.h>

class FontPickerTest : public QObject
{
   Q_OBJECT

public:
   FontPickerTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testSetGetFont();
   void testSetGetFontWithModifiers();
   void testCurrentFontChangedSignal();
   void testFontFilters();
};

FontPickerTest::FontPickerTest()
{
}

void FontPickerTest::initTestCase()
{
}

void FontPickerTest::cleanupTestCase()
{
}

void FontPickerTest::testSetGetFont()
{
   FontPicker fontPicker;
   QFont font = TestCommon::testFont();

   fontPicker.setCurrentFont(font);

   QVERIFY2(fontPicker.ui->fontComboBox->currentFont() == font, "Font wasn't selected in combobox.");

   // Modify testfont for ui state
   font.setPointSize(fontPicker.ui->fontSizeSpinBox->value());

   QVERIFY2(fontPicker.currentFont() == font, "Returned font isn't the same as the one that was set.");
}

/*!
 * \brief FontPickerTest::testSetGetFontWithModifiers
 * Test setting/getting with modifiers such as bold, italic, ...
 */
void FontPickerTest::testSetGetFontWithModifiers()
{
   int fontPointSize = 16;
   FontPicker fontPicker;
   fontPicker.ui->fontSizeSpinBox->setValue(fontPointSize);
   fontPicker.ui->boldButton->setChecked(true);
   fontPicker.ui->italicButton->setChecked(true);
   fontPicker.ui->underlineButton->setChecked(true);
   fontPicker.ui->strikeoutButton->setChecked(true);

   QFont font = TestCommon::testFont();
   // Modify testfont for ui state
   font.setPointSize(fontPointSize + 2);
   font.setBold(false);
   font.setItalic(false);
   font.setUnderline(false);
   font.setStrikeOut(false);

   fontPicker.setCurrentFont(font);

   QVERIFY2(fontPicker.ui->fontSizeSpinBox->value() == font.pointSize(), "Font size wasn't set in ui from font.");
   QVERIFY2(fontPicker.ui->boldButton->isChecked() == font.bold(), "Bold button wasn't set checked.");
   QVERIFY2(fontPicker.ui->italicButton->isChecked() == font.italic(), "Italic button wasn't set checked.");
   QVERIFY2(fontPicker.ui->underlineButton->isChecked() == font.underline(), "Underline button wasn't set checked.");
   QVERIFY2(fontPicker.ui->strikeoutButton->isChecked() == font.strikeOut(), "Strike out button wasn't set checked.");

   QVERIFY2(fontPicker.currentFont() == font, "Returned font isn't the same as the one that was set.");
}

void FontPickerTest::testCurrentFontChangedSignal()
{
   FontPicker fontPicker;
   QSignalSpy spy(&fontPicker, SIGNAL(currentFontChanged(QFont)));

   fontPicker.setCurrentFont(TestCommon::testFont());
   QVERIFY2(spy.count(), "Font changed signal wasn't emitted");

   spy.clear();
   int currentIndex = fontPicker.ui->fontComboBox->currentIndex();
   int newIndex = currentIndex + 1;
   if (newIndex >= fontPicker.ui->fontComboBox->count() - 1) {
      newIndex = currentIndex - 1;
   }

   Q_ASSERT(newIndex >= 0);
   fontPicker.ui->fontComboBox->setCurrentIndex(newIndex);
   QVERIFY2(spy.count(), "Font changed signal wasn't emitted on font change.");

   spy.clear();
   fontPicker.ui->boldButton->toggle();
   QVERIFY2(spy.count(), "Font changed signal wasn't emitted on bold button change.");

   spy.clear();
   fontPicker.ui->italicButton->toggle();
   QVERIFY2(spy.count(), "Font changed signal wasn't emitted on italic button change.");

   spy.clear();
   fontPicker.ui->underlineButton->toggle();
   QVERIFY2(spy.count(), "Font changed signal wasn't emitted on underline button change.");

   spy.clear();
   fontPicker.ui->strikeoutButton->toggle();
   QVERIFY2(spy.count(), "Font changed signal wasn't emitted on strike button change.");

   spy.clear();
   fontPicker.ui->fontSizeSpinBox->setValue(18);
   QVERIFY2(spy.count(), "Font changed signal wasn't emitted on changed size in font size spin box.");
}

void FontPickerTest::testFontFilters()
{
   FontPicker fontPicker;

   QVERIFY2(fontPicker.fontFilters() == QFontComboBox::AllFonts, "Wrong default filter");

   fontPicker.setFontFilters(QFontComboBox::MonospacedFonts);
   QVERIFY2(fontPicker.fontFilters() == QFontComboBox::MonospacedFonts, "Failed setting/getting font filters");
}

QTEST_MAIN(FontPickerTest)

#include "tst_FontPickerTest.moc"
