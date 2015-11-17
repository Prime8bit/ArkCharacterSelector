#include "Logger.h"

void Logger::WriteLine(const QString &message)
{
    if (_logFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream logStream(&_logFile);
        logStream << message << "\n";
        _logFile.close();
    }
}
