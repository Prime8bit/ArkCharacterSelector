#include "Logger.h"

Logger::~Logger()
{
    if (_logFile != 0)
        _logFile.close();
}

bool WriteLine(const QString &message)
{

}

bool Close()
{

}
