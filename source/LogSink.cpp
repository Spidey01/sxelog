/*-
 * Copyright (c) 2012-current, Terry Mathew Poulin <BigBoss1964@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the
 * use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *	1. The origin of this software must not be misrepresented; you must
 *	   not claim that you wrote the original software. If you use this
 *	   software in a product, an acknowledgment in the product
 *	   documentation would be appreciated but is not required.
 *
 *	2. Altered source versions must be plainly marked as such, and must
 *	   not be misrepresented as being the original software.
 *
 *	3. This notice may not be removed or altered from any source
 *	   distribution.
 */

#include <sxe/logging/LogSink.hpp>
#include <sxe/logging/Log.hpp>

namespace sxe {  namespace logging {

const int LogSink::DEFAULT_LOG_LEVEL = Log::INFO;
const char* LogSink::DEFAULT_LOG_NAME = "debug";


LogSink::LogSink(const string_type& name, int level)
    : mName(name)
    , mDefaultLevel(level)
    , mFilters()
    , mSquelchedThreadIdList()
    , mDisplayThreadId(true)
    , mDisplayDate(true)
    , mDisplayTime(true)
{
}

LogSink::LogSink()
    : LogSink(DEFAULT_LOG_NAME, DEFAULT_LOG_LEVEL)
{
}

LogSink::~LogSink()
{
}

void LogSink::log(int level, const string_type& tag, const string_type& message)
{
    if (message.empty())
        return;

    if (level > getLevel(tag))
        return;

    onHeader(level, tag);
    onWrite(message);
}


bool LogSink::isLoggable(const string_type& tag, int level) const
{
    if (!mSquelchedThreadIdList.empty()) {
        auto maybe = std::find(mSquelchedThreadIdList.cbegin(),
                               mSquelchedThreadIdList.cend(),
                               std::this_thread::get_id());
        if (maybe != mSquelchedThreadIdList.cend())
            return false;
    }

    return level == getLevel(tag);
}

int LogSink::getLevel(const string_type& tag) const
{
    auto pair = mFilters.find(tag);

    return (pair == mFilters.cend() ? mDefaultLevel : pair->second);
}


void LogSink::setLevel(const string_type& tag, int level)
{
    mFilters[tag] = level;
}


int LogSink::getDefaultLevel() const
{
    return mDefaultLevel;
}


void LogSink::setDefaultLevel(int level)
{
    mDefaultLevel = level;
}


const LogSink::string_type& LogSink::getName() const
{
    return mName;
}


void LogSink::setName(const string_type& name)
{
    mName = name;
}


bool LogSink::getDisplayThreadId() const
{
    return mDisplayThreadId;
}


void LogSink::setDisplayThreadId(bool x)
{
    mDisplayThreadId = x;
}


bool LogSink::getDisplayDate() const
{
    return mDisplayDate;
}


void LogSink::setDisplayDate(bool x)
{
    mDisplayDate = x;
}


bool LogSink::getDisplayTime() const
{
    return mDisplayTime;
}


void LogSink::setDisplayTime(bool x)
{
    mDisplayTime = x;
}


void LogSink::squelchThreadId(std::thread::id tid)
{
    mSquelchedThreadIdList.push_back(tid);
}


void LogSink::unsquelchThreadId(std::thread::id tid)
{
    auto& l = mSquelchedThreadIdList;

    if (l.empty())
        return;
    
    l.erase(std::remove(l.begin(), l.end(), tid), l.end());
}


LogSink::string_type LogSink::translate(int level) const
{
    switch (level) {
        case Log::ASSERT: return "ASSERT";
        case Log::ERROR: return "e";
        case Log::WARN: return "w";
        case Log::INFO: return "i";
        case Log::DEBUG: return "d";
        case Log::VERBOSE: return "v";
        case Log::TRACE: return "x";
        case Log::TEST: return "TEST";

        default: return "UNKNOWN";
    }
}


void LogSink::onHeader(int level, const string_type& tag)
{
    (void)level;
    (void)tag;
}

void LogSink::onWrite(const string_type& message)
{
    (void)message;
}


} }

