#include "consolelogger.h"

#include <QDateTime>


void ConsoleLogger::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QTextStream out(stdout);

    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    switch (type) {
        case QtInfoMsg:     out << "INF "; break;
        case QtDebugMsg:    out << "DBG "; break;
        case QtWarningMsg:  out << "WRN "; break;
        case QtCriticalMsg: out << "CRT "; break;
        case QtFatalMsg:    out << "FTL "; break;
    }
    out << context.category << ": " << msg << Qt::endl;

    out.flush();
}

ConsoleLogger::ConsoleLogger()
{
    qInstallMessageHandler(messageHandler);
}

void ConsoleLogger::debug(const QString &msg)
{
    qDebug(logDebug()) << msg;
}

void ConsoleLogger::info(const QString &msg)
{
    qInfo(logInfo()) << msg;
}

void ConsoleLogger::warning(const QString &msg)
{
    qWarning(logWarning()) << msg;
}

void ConsoleLogger::critical(const QString &msg)
{
    qCritical(logCritical()) << msg;
}
