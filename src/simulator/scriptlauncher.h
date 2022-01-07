#ifndef SCRIPTLAUNCHER_H
#define SCRIPTLAUNCHER_H

#include <QObject>
#include <QProcess>

class ScriptLauncher : public QObject {
    Q_OBJECT

    Q_PROPERTY(ScriptType lastScriptLaunched READ lastScriptLaunched WRITE setLastScriptLaunched
            NOTIFY lastScriptLaunchedChanged)

public:
    enum ScriptType { NoScript, UUIDGeneration, RegisterCommand, SetTemperatureCommand };
    Q_ENUM(ScriptType)

    explicit ScriptLauncher(QObject* parent = nullptr);

    Q_INVOKABLE bool generateUUID();
    Q_INVOKABLE bool sendRegisterCommand(const QByteArray& sensorUUID);
    Q_INVOKABLE bool sendSetTemperatureCommand(const QByteArray& sensorUUID, int temperatureCK);
    Q_INVOKABLE QByteArray readScriptOutput() const;

    ScriptType lastScriptLaunched() const { return m_lastScriptLaunched; }

private slots:
    void onScriptFinished(int exitCode, QProcess::ExitStatus exitStatus);

signals:
    void lastScriptLaunchedChanged() const;

    void scriptStarted() const;
    void scriptFailed(ScriptType type) const;
    void uuidGenerationFinished(const QByteArray& uuid) const;
    void registerCommandFinished(const QByteArray& output) const;

private:
    void setLastScriptLaunched(ScriptType lastScriptLaunched);

    QProcess* m_process;
    ScriptType m_lastScriptLaunched;

    static const QString ScriptsPath;
    static const QString RegisterScriptPath;
    static const QString SetTemperatureScriptPath;
};

#endif // SCRIPTLAUNCHER_H
