#ifndef LOGGER_H
#define LOGGER_H

#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(logDebug)
Q_DECLARE_LOGGING_CATEGORY(logInfo)
Q_DECLARE_LOGGING_CATEGORY(logWarning)
Q_DECLARE_LOGGING_CATEGORY(logCritical)

Q_LOGGING_CATEGORY(logDebug,    "Debug")
Q_LOGGING_CATEGORY(logInfo,     "Info")
Q_LOGGING_CATEGORY(logWarning,  "Warning")
Q_LOGGING_CATEGORY(logCritical, "Critical")

class ILogger
{
public:
    virtual ~ILogger() = default;
    virtual void debug(const QString &msg) = 0;
    virtual void info(const QString &msg) = 0;
    virtual void warning(const QString &msg) = 0;
    virtual void critical(const QString &msg) = 0;
};

#endif // LOGGER_H
