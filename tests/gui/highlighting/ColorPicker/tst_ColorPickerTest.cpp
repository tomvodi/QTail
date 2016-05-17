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

#include <highlighting/ColorPicker.h>
#include <ui_ColorPicker.h>

class ColorPickerTest : public QObject
{
   Q_OBJECT

public:
   ColorPickerTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testSetup();
   void testSetGetCurrentColor();
};

ColorPickerTest::ColorPickerTest()
{
}

void ColorPickerTest::initTestCase()
{
}

void ColorPickerTest::cleanupTestCase()
{
}

void ColorPickerTest::testSetup()
{
   ColorPicker colorPicker;
   QVERIFY2(colorPicker.ui->colorComboBox->count(), "No colors in combobox");
}

void ColorPickerTest::testSetGetCurrentColor()
{
   ColorPicker colorPicker;

   int limeGreenIndex = colorPicker.ui->colorComboBox->findData(QColor("limegreen"));
   QVERIFY2(limeGreenIndex != -1, "Failed to find test data in combobox");

   colorPicker.setCurrentColor("limegreen");

   QVERIFY2(colorPicker.currentColor() == QColor("limegreen"), "Failed settings/getting current color");
}

QTEST_MAIN(ColorPickerTest)

#include "tst_ColorPickerTest.moc"
