#include <QCommandLineParser>
#include <QCoreApplication>
#include <QLoggingCategory>

#include "mycoordinate.h"

// Create "core" category with all message types enabled
Q_LOGGING_CATEGORY(core, "myapp.core")

// Create "component2" category enabling messages of types Warning
// and higher (regarding severity: Debug < Info < Warning < Critical)
Q_LOGGING_CATEGORY(component2, "myapp.component2", QtWarningMsg)

int main(int argc, char *argv[])
{
   QCoreApplication app {argc, argv};
   QCoreApplication::setApplicationName(QStringLiteral("logging"));
   QCoreApplication::setApplicationVersion(QStringLiteral("1.0"));

   // Parse arguments
   QCommandLineParser parser;
   parser.addHelpOption();
   QCommandLineOption verbosity {
      {QStringLiteral("v"), QStringLiteral("verbosity")},
      QObject::tr("Adjusts verbosity level."),
      QStringLiteral("verbosity"),
      QStringLiteral("0")};
   parser.addOption(verbosity);
   parser.process(app);
   int verbosityLevel = parser.value(verbosity).toInt();

   QLoggingCategory::setFilterRules(QStringLiteral(
                                       "myapp.core.debug=false\n"
                                       "myapp.component1=false\n"
                                       "myapp.*.warning=false"));
   qSetMessagePattern(QStringLiteral(
      "%{pid}:%{appname}:%{file}:%{function}:%{line}:%{category}: "
      "%{message}"));

   // qDebug() basics
   qDebug() << "Debug message using the default category";
   qDebug() << "Items are automatically spaced and quoted:" <<
               QStringLiteral("Qt is awesome!");
   qDebug().nospace().noquote()
         << "Removing_" << "spaces_" << QStringLiteral("and quoting");
   qDebug("Formatting: %d+%d=%d", 2, 3, 5); // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg)

   // Logging using "core" category
   qCDebug(core) << "Debug";
   qCInfo(core) << "Info";
   qCWarning(core) << "Warning";
   qCCritical(core) << "Critical";

   // Using verbosityLevel
   if (verbosityLevel > 0) {
      qDebug() << "Some information";
      if (verbosityLevel > 1) {
         qDebug() << "More detailed information";
         if (verbosityLevel > 2) {
            qDebug() << "Even more detailed information";
         }
      }
   }

   // Checking category configuration
   if (core().isDebugEnabled()) {
      // Execute expensive computation/data generation
      // only used for debugging purposes
   }

   // Using custom types with and category defined elsewhere
   qCInfo(component1) << "MyCoordinate:" <<
                                   MyCoordinate {1.5, 2.5} << "!";

   // Logging using "component2" category
   qCDebug(component2) << "Debug";
   qCInfo(component2) << "Info";
   qCWarning(component2) << "Warning";
   qCCritical(component2) << "Critical";

   return 0;
}
