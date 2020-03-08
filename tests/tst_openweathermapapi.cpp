#include <QCoreApplication>
#include <QtTest>

#include "../src/weather/openweathermapaccess.h"
#include "../src/weather/weathersettings.h"

class openweathermapapi_test : public QObject {
    Q_OBJECT

public:
    openweathermapapi_test();
    ~openweathermapapi_test();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void checkOWMConnection();

private:
    WeatherSettings* mock_settings;
};

openweathermapapi_test::openweathermapapi_test()
{
    QTemporaryFile tmpFile;
    tmpFile.open();

    mock_settings = new WeatherSettings(tmpFile.fileName(), this);
    mock_settings->setValue(OpenWeatherMapSettingsParameters::GroupName,
        OpenWeatherMapSettingsParameters::AppId, "FAK3APP1D");
}

openweathermapapi_test::~openweathermapapi_test() {}

void openweathermapapi_test::initTestCase() {}

void openweathermapapi_test::cleanupTestCase() {}

void openweathermapapi_test::checkOWMConnection()
{
    OpenWeatherMapAccess owmAPI(mock_settings, this);
    owmAPI.setRefreshInterval(std::chrono::seconds(2));
    QSignalSpy spy(&owmAPI, &OpenWeatherMapAccess::dataUpdated);

    for (int waitDelay = 10000; waitDelay > 0 && spy.count() == 0; waitDelay -= 100)
        QTest::qWait(100);

    QVERIFY(spy.count());
}

QTEST_MAIN(openweathermapapi_test)

#include "tst_openweathermapapi.moc"
