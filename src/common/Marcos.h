// Note(yangchao. 2021-05-13):公共头文件， 不允许在h中添加自己编写的头文件
#pragma once

#include <memory>

#include "fmt/format.h"
#include "Poco/Logger.h"
#include "Poco/Message.h"

using namespace std;

#define DECLARE_CLASS_POINT_TYPE(T) typedef shared_ptr<T> T##Ptr

#define DECLARE_CLASS_LOGGER(T) Poco::Logger * log;
#define DEFINED_CLASS_LOGGER(T) T::log = Poco::Logger::get(""#T"");

namespace
{
    template <typename... Ts> constexpr size_t numArgs(Ts &&...) { return sizeof...(Ts); }
    template <typename T, typename... Ts> constexpr auto firstArg(T && x, Ts &&...) { return std::forward<T>(x); }
}


/// Logs a message to a specified logger with that level.
/// If more than one argument is provided,
///  the first argument is interpreted as template with {}-substitutions
///  and the latter arguments treat as values to substitute.
/// If only one argument is provided, it is threat as message without substitutions.

#define LOG_IMPL(logger, PRIORITY, ...) do                              \
{                                                                                 \
    if ((logger)->is((PRIORITY)))                                                 \
    {                                                                             \
        std::string formatted_message = numArgs(__VA_ARGS__) > 1 ? fmt::format(__VA_ARGS__) : firstArg(__VA_ARGS__); \
        if (auto channel = (logger)->getChannel())                                \
        {                                                                         \
            Poco::Message poco_message((logger)->name(), formatted_message, (PRIORITY), __FILE__, __LINE__);    \
            channel->log(poco_message);                                           \
        }                                                                         \
    }                                                                             \
} while (false)


#define LOG_TRACE(logger, ...)   LOG_IMPL(logger, Poco::Message::PRIO_TRACE, __VA_ARGS__)
#define LOG_DEBUG(logger, ...)   LOG_IMPL(logger, Poco::Message::PRIO_DEBUG, __VA_ARGS__)
#define LOG_INFO(logger, ...)    LOG_IMPL(logger, Poco::Message::PRIO_INFORMATION, __VA_ARGS__)
#define LOG_WARNING(logger, ...) LOG_IMPL(logger, Poco::Message::PRIO_WARNING, __VA_ARGS__)
#define LOG_ERROR(logger, ...)   LOG_IMPL(logger, Poco::Message::PRIO_ERROR, __VA_ARGS__)
#define LOG_FATAL(logger, ...)   LOG_IMPL(logger, Poco::Message::PRIO_FATAL, __VA_ARGS__)


/// Compatibility for external projects.
#if defined(ARCADIA_BUILD)
    using Poco::Logger;
    using Poco::Message;
#endif
