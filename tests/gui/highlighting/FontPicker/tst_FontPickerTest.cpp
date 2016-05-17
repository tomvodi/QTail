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

private:
   QFont testFont() const;
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
   QFont font = testFont();

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

   QFont font = testFont();
   // Modify testfont for ui state
   font.setPointSize(fontPointSize);
   font.setBold(true);
   font.setItalic(true);
   font.setUnderline(true);
   font.setStrikeOut(true);

   fontPicker.setCurrentFont(font);

   QVERIFY2(fontPicker.currentFont() == font, "Returned font isn't the same as the one that was set.");
}

QFont FontPickerTest::testFont() const
{
   QFontDatabase database;
   QStringList fonts = database.families();

   if (fonts.count() > 3) {
      return QFont(fonts.at(2));
   }

   return QFont();
}

QTEST_MAIN(FontPickerTest)

#include "tst_FontPickerTest.moc"
