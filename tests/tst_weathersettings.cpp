#include <QtTest>

#include "../src/weather/weathersettings.h"

class weathersettings_test : public QObject {
    Q_OBJECT

public:
    weathersettings_test();
    ~weathersettings_test();

private slots:
    void checkSettingsGetter_data();
    void checkSettingsGetter();

private:
    WeatherSettings settings;
};

weathersettings_test::weathersettings_test()
    : settings("test_weathersettings")
{
    settings.setValue("group1", "key1", 1);
    settings.setValue("group2", "key1", 0.5);
    settings.setValue("group2", "key2", "stringValueG2K2");
    settings.setValue("group2", "key3", false);
}

weathersettings_test::~weathersettings_test() {}

void weathersettings_test::checkSettingsGetter_data()
{
    QTest::addColumn<QString>("group");
    QTest::addColumn<QString>("key");
    QTest::addColumn<QVariant>("value");

    QTest::newRow("unknownGroupAndKey") << "unknownGroup"
                                        << "unknownKey" << QVariant();
    QTest::newRow("unknownGroup") << "unknownGroup"
                                  << "key3" << QVariant();
    QTest::newRow("unknownKey") << "group1"
                                << "unknownKey" << QVariant();
    QTest::newRow("keyInOtherGroup") << "group1"
                                     << "key2" << QVariant();
    QTest::newRow("integer") << "group1"
                             << "key1" << QVariant(1);
    QTest::newRow("float") << "group2"
                           << "key1" << QVariant(0.5);
    QTest::newRow("string") << "group2"
                            << "key2" << QVariant("stringValueG2K2");
    QTest::newRow("bool") << "group2"
                          << "key3" << QVariant(false);
}

void weathersettings_test::checkSettingsGetter()
{
    QFETCH(QString, group);
    QFETCH(QString, key);
    QFETCH(QVariant, value);

    QCOMPARE(settings.value(group, key), value);
}

QTEST_APPLESS_MAIN(weathersettings_test)

#include "tst_weathersettings.moc"
