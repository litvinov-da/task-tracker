#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "logger.h"

class ConsoleLogger : public ILogger
{
    QTextStream out;
public:
    ConsoleLogger();
    void log(const QLoggingCategory &category, const QString &msg) override;
};

#endif // CONSOLELOGGER_H
