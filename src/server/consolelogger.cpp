#include "consolelogger.h"

#include <QDateTime>

ConsoleLogger::ConsoleLogger()
    :out(stdout)
{}

void ConsoleLogger::log(const QLoggingCategory &category, const QString &msg)
{
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    out << &category << ":" << msg << Qt::endl;
    out.flush();
}
