#ifndef LOGGER_H
#define LOGGER_H

#include <QFile>
#include <QTextStream>

class Logger
{
public:
    Logger(const QString &fileName);
    ~Logger();

    void WriteLine(const QString &message);
    void Close();
private:
    QFile _logFile;
    QTextStream _logStream;

};

#endif // LOGGER_H
