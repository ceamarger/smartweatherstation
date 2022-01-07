#include "scriptlauncher.h"

#include <QFile>
#include <QtDebug>

const QString ScriptLauncher::ScriptsPath = "simulator/scripts";
const QString ScriptLauncher::RegisterScriptPath = ScriptsPath + "/register.sh";
const QString ScriptLauncher::SetTemperatureScriptPath = ScriptsPath + "/send_temperature.sh";

ScriptLauncher::ScriptLauncher(QObject* parent)
    : QObject(parent)
    , m_process(new QProcess(this))
    , m_lastScriptLaunched(NoScript)
{
    connect(m_process, &QProcess::started, this, &ScriptLauncher::scriptStarted);
    connect(m_process, &QProcess::errorOccurred, this,
        [](QProcess::ProcessError error) { qDebug() << "New state:" << error; });
    connect(m_process, &QProcess::readyReadStandardError, this,
        [&]() { qDebug() << "Standard error" << m_process->readAllStandardError(); });
    connect(m_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
        &ScriptLauncher::onScriptFinished);
}

bool ScriptLauncher::generateUUID()
{
    if (!m_process || m_process->state() != QProcess::ProcessState::NotRunning)
        return false;

    qDebug() << "Generate UUID";

    setLastScriptLaunched(ScriptType::UUIDGeneration);

    m_process->start("uuidgen", QStringList() << "-r");

    return true;
}

bool ScriptLauncher::sendRegisterCommand(const QByteArray& sensorUUID)
{
    if (!m_process || m_process->state() != QProcess::ProcessState::NotRunning)
        return false;

    qDebug() << "Send Register Command";

    setLastScriptLaunched(ScriptType::RegisterCommand);

    if (QFile::exists(RegisterScriptPath))
        m_process->start("/bin/sh", QStringList() << RegisterScriptPath << sensorUUID);
    else
        qDebug() << "Script does not exist :" << RegisterScriptPath;

    return true;
}

/**
 * @brief ScriptLauncher::sendSetTemperatureCommand
 * @param sensorUUID
 * @param temperatureCK temperature in CentiKelvin (Kelvin * 100)
 * @return
 */
bool ScriptLauncher::sendSetTemperatureCommand(const QByteArray& sensorUUID, int temperatureCK)
{
    if (!m_process || m_process->state() != QProcess::ProcessState::NotRunning)
        return false;

    qDebug() << "Send Set Temperature Command. Temperature : " << temperatureCK / 100. << "K";

    setLastScriptLaunched(ScriptType::SetTemperatureCommand);

    if (QFile::exists(SetTemperatureScriptPath))
        m_process->start("/bin/sh",
            QStringList() << SetTemperatureScriptPath << sensorUUID
                          << QString::number(temperatureCK));
    else
        qDebug() << "Script does not exist :" << SetTemperatureScriptPath;

    return true;
}

QByteArray ScriptLauncher::readScriptOutput() const
{
    if (!m_process || m_process->state() != QProcess::ProcessState::NotRunning)
        return "";

    return m_process->readAll();
}

void ScriptLauncher::onScriptFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << lastScriptLaunched() << "finished. Exit :" << exitCode << exitStatus;

    if (exitStatus == QProcess::CrashExit) {
        qDebug() << "Script Failed";
        emit scriptFailed(lastScriptLaunched());
        return;
    }

    QByteArray scriptOutput = readScriptOutput().trimmed();
    switch (lastScriptLaunched()) {
    case UUIDGeneration:
        emit uuidGenerationFinished(scriptOutput);
        break;
    case RegisterCommand:
        emit registerCommandFinished(scriptOutput);
        break;
    default:
        break;
    }
}

void ScriptLauncher::setLastScriptLaunched(ScriptLauncher::ScriptType lastScriptLaunched)
{
    if (m_lastScriptLaunched == lastScriptLaunched)
        return;

    m_lastScriptLaunched = lastScriptLaunched;
    emit lastScriptLaunchedChanged();
}
