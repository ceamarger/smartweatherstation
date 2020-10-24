pragma Singleton

import QtQuick 2.15

import sws.weather 1.0
import sws.utils 1.0

Item {

    function settingsUnitToConverterUnit(unit) {
        switch (unit) {
        case TemperatureSettingsGroup.Kelvin:
            return TemperatureConverter.Kelvin
        case TemperatureSettingsGroup.Celsius:
            return TemperatureConverter.Celsius
        case TemperatureSettingsGroup.Fahrenheit:
            return TemperatureConverter.Fahrenheit
        default:
            console.log("Unknown unit")
        }
    }

    function converterUnitToSettingsUnit(unit) {
        switch (unit) {
        case TemperatureConverter.Kelvin:
            return TemperatureSettingsGroup.Kelvin
        case TemperatureConverter.Celsius:
            return TemperatureSettingsGroup.Celsius
        case TemperatureConverter.Fahrenheit:
            return TemperatureSettingsGroup.Fahrenheit
        default:
            console.log("Unknown unit")
        }
    }
}
