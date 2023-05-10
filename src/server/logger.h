#ifndef LOGGER_H
#define LOGGER_H

#include "loggingcategories.h"

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
