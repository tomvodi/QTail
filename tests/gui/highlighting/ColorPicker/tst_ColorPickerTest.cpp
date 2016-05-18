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
   void testCurrentColorChangedSignal();
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

void ColorPickerTest::testCurrentColorChangedSignal()
{
   ColorPicker colorPicker;
   QSignalSpy spy(&colorPicker, SIGNAL(currentColorChanged(QColor)));

   colorPicker.setCurrentColor(Qt::blue);
   QVERIFY2(spy.count() == 1, "Color changed signal wasn't emitted.");

   spy.clear();
   colorPicker.ui->colorComboBox->setCurrentIndex( colorPicker.ui->colorComboBox->count() - 2 );
   QVERIFY2(spy.count() == 1, "Color changed signal wasn't emitted for changed color in combobox.");
}

QTEST_MAIN(ColorPickerTest)

#include "tst_ColorPickerTest.moc"
