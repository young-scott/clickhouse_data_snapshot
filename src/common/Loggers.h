#pragma once

#include <optional>
#include <string>
#include "config/Context.h"

class Loggers
{
public:
    void buildLoggers(ContextPtr& context_ptr, Poco::Logger & logger);

};
