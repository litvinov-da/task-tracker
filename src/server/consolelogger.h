#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "logger.h"

class ConsoleLogger : public ILogger
{
    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
public:
    ConsoleLogger();

    void debug(const QString &msg) override;
    void info(const QString &msg) override;
    void warning(const QString &msg) override;
    void critical(const QString &msg) override;
};

#endif // CONSOLELOGGER_H
