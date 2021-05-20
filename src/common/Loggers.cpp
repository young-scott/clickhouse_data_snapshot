#include "common/Loggers.h"
#include "config/Context.h"

#include <iostream>
#include "Poco/SyslogChannel.h"
#include "Poco/Util/AbstractConfiguration.h"

#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/File.h"
#include "Poco/Logger.h"
#include "Poco/Path.h"

namespace DB
{
    class SensitiveDataMasker;
}


// TODO: move to libcommon
static std::string createDirectory(const std::string & file)
{
    auto path = Poco::Path(file).makeParent();
    if (path.toString().empty())
        return "";
    Poco::File(path).createDirectories();
    return path.toString();
};

void Loggers::buildLoggers(ContextPtr& context_ptr, Poco::Logger & logger)
{
    /// Split logs to ordinary log, error log, syslog and console.
    /// Use extended interface of Channel for more comprehensive logging.
    // split = new Poco::SplitterChannel();

    auto log_level = context_ptr->logger_level();
    const auto log_path = context_ptr->logger_path();

    createDirectory(log_path);

    Poco::AutoPtr<Poco::ConsoleChannel> console = new Poco::ConsoleChannel;
    Poco::AutoPtr<Poco::FileChannel> log_file = new Poco::FileChannel;

    Poco::AutoPtr<Poco::PatternFormatter> patternFormatter(new Poco::PatternFormatter("[%H:%M:%S] [%U(%u)] %p: %t"));
    patternFormatter->setProperty("times", "local");  // 格式化中的时间显示为本地时间
    Poco::AutoPtr<Poco::FormattingChannel> consoleFmtChannel(new Poco::FormattingChannel(patternFormatter, console));
    Poco::AutoPtr<Poco::FormattingChannel> fileFmtChannel(new Poco::FormattingChannel(patternFormatter, log_file));

    logger.setChannel(consoleFmtChannel);
    logger.close();
    logger.setLevel(log_level);
}