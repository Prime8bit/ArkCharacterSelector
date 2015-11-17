#ifndef LOGGER_H
#define LOGGER_H

#include <QFile>
#include <QTextStream>

class Logger
{
public:
    Logger(const QString &fileName)
        : _logFile(fileName)
    {}

    void WriteLine(const QString &message);
private:
    QFile _logFile;
};

#endif // LOGGER_H
