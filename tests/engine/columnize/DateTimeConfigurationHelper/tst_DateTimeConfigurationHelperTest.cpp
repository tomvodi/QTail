/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QString>
#include <QtTest>

#include <engine/include/columnize/DateTimeConfigurationHelper.h>

class DateTimeConfigurationHelperTest : public QObject
{
   Q_OBJECT

   ColConfig newColConfig();

public:
   DateTimeConfigurationHelperTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testType();
   void testLocale();
   void testFormat();
};

ColConfig DateTimeConfigurationHelperTest::newColConfig()
{
   ColConfig colConfig(new ColumnConfiguration(ColumnType::DateTime));
   return colConfig;
}

DateTimeConfigurationHelperTest::DateTimeConfigurationHelperTest()
{
}

void DateTimeConfigurationHelperTest::initTestCase()
{
}

void DateTimeConfigurationHelperTest::cleanupTestCase()
{
}

void DateTimeConfigurationHelperTest::testType()
{
   DateTimeConfigurationHelper config(newColConfig());
   QVERIFY(config.type() == ColumnType::DateTime);
}

void DateTimeConfigurationHelperTest::testLocale()
{
   DateTimeConfigurationHelper config(newColConfig());

   QList<QLocale> locals = QLocale::matchingLocales(QLocale::Arabic,
                                                    QLocale::AnyScript,
                                                    QLocale::AnyCountry);
   QVERIFY(locals.count());

   QLocale locale = locals.first();
   QVERIFY(locale != QLocale());

   config.setLocale(locale);
   QVERIFY(config.locale() == locale);
}

void DateTimeConfigurationHelperTest::testFormat()
{
   DateTimeConfigurationHelper config(newColConfig());

}

QTEST_APPLESS_MAIN(DateTimeConfigurationHelperTest)

#include "tst_DateTimeConfigurationHelperTest.moc"
