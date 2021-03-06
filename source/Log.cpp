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

#include <sxe/logging/Log.hpp>
#include <sxe/logging/StandardOutputLogSink.hpp>

using std::string;
using std::exception;

namespace sxe {  namespace logging {

using LogSinkListPrivate = std::list<LogSink::shared_ptr>;
static LogSinkListPrivate sSinks;

Log::lock_guard::mutex_type Log::sMutex;
bool Log::sAutovivification = false;
bool Log::sWtfCallsTerminate = false;

static const std::unordered_map<std::string, int> sStringToLevelTable = {
    { "ASSERT", Log::ASSERT },
    { "ERROR", Log::ERROR },
    { "WARN", Log::WARN },
    { "INFO", Log::INFO },
    { "DEBUG", Log::DEBUG },
    { "VERBOSE", Log::VERBOSE },
    { "TRACE", Log::TRACE },
    { "TEST", Log::TEST },
};

void Log::autovivification(bool enabled)
{
    sAutovivification = enabled;
}

void Log::wtfCallsTerminate(bool enabled)
{
    sWtfCallsTerminate = false;
}

std::string Log::levelToString(int level)
{
    for (const auto& pair : sStringToLevelTable) {
        if (pair.second == level)
            return pair.first;
    }

    return "";
}


int Log::stringToLevel(const std::string& level)
{
    auto it = sStringToLevelTable.find(level);

    if (it != sStringToLevelTable.cend())
        return it->second;

    /*
     * Before giving up: try stoi and treating it the same as levelToString().
     * This is done in order to make it ease to use either string or numeric
     * value, in command line arguments and settings files.
     */
    try {
        int maybe = std::stoi(level);
        if (maybe >= Log::ASSERT && maybe <= Log::TEST)
            return stringToLevel(levelToString(maybe));
    } catch (std::invalid_argument& unknown) {
        (void)unknown;
    }

    return Log::ASSERT;
}


void Log::wtf(const string& tag, const string& message)
{
    log(ASSERT, tag, message);

    static const char* msg = "What a Terrible Failure Report we has here";
    assert(msg == nullptr);

    if (sWtfCallsTerminate)
        std::terminate();
}

void Log::wtf(const string& tag, const string& message, const exception& error)
{
    log(ASSERT, tag, message, error);

    static const char* msg = "What a Terrible Failure Report we has here";
    assert(msg == nullptr);

    if (sWtfCallsTerminate)
        std::terminate();
}


void Log::e(const string& tag, const string& message)
{
    log(ERROR, tag, message);
}


void Log::e(const string& tag, const string& message, const exception& error)
{
    log(ERROR, tag, message, error);
}


void Log::w(const string& tag, const string& message)
{
    log(WARN, tag, message);
}


void Log::w(const string& tag, const string& message, const exception& error)
{
    log(WARN, tag, message, error);
}


void Log::i(const string& tag, const string& message)
{
    log(INFO, tag, message);
}


void Log::i(const string& tag, const string& message, const exception& error)
{
    log(INFO, tag, message, error);
}


void Log::d(const string& tag, const string& message)
{
    log(DEBUG, tag, message);
}


void Log::d(const string& tag, const string& message, const exception& error)
{
    log(DEBUG, tag, message, error);
}


void Log::v(const string& tag, const string& message)
{
    log(VERBOSE, tag, message);
}


void Log::v(const string& tag, const string& message, const exception& error)
{
    log(VERBOSE, tag, message, error);
}


void Log::xtrace(const string& tag, const string& message)
{
    log(TRACE, tag, message);
}


void Log::xtrace(const string& tag, const string& message, const exception& error)
{
    log(TRACE, tag, message, error);
}


void Log::test(const string& tag, const string& message)
{
    log(TEST, tag, message);
}


void Log::test(const string& tag, const string& message, const exception& error)
{
    log(TEST, tag, message, error);
}


void Log::log(int level, const string& tag, const string& message)
{
    lock_guard synchronized(sMutex);

    if (sAutovivification && sSinks.empty()) {
        setDefaultLogSink(std::make_shared<StandardOutputLogSink>());
    }

    for (auto sink : sSinks) {
        sink->log(level, tag, message);
    }
}


void Log::log(int level, const string& tag, const string& message, const exception& error)
{
    log(level, tag, message + string(": exception: ") + error.what());
}


void Log::add(LogSink::shared_ptr sink)
{
    if (!sink) return;

    lock_guard synchronized(sMutex);

    sSinks.push_back(sink);
}


void Log::remove(LogSink::shared_ptr sink)
{
    lock_guard synchronized(sMutex);

    sSinks.remove(sink);
}


Log::LogSinkList Log::getSinks()
{
    lock_guard synchronized(sMutex);
    LogSinkList list;

    for (auto shared : sSinks) {
        list.push_back(shared);
    }

    return list;
}


LogSink::shared_ptr Log::getLogSink(const string& name)
{
    lock_guard synchronized(sMutex);

    for (auto shared : sSinks) {
        if (shared->getName() == name)
            return shared;
    }

    return nullptr;
}


LogSink::shared_ptr Log::getDefaultLogSink()
{
    return getLogSink("default");
}


void Log::setDefaultLogSink(LogSink::shared_ptr sink)
{
    lock_guard synchronized(sMutex);

    LogSink::shared_ptr old = getDefaultLogSink();

    if (old)
        remove(old);

    sink->setName("default");

    add(sink);
}


bool Log::isLoggable(const string& tag, int level)
{
    lock_guard synchronized(sMutex);

    for (auto sink : sSinks) {
        if (sink->isLoggable(tag, level)) {
            return true;
        }
    }

    return false;
}


void Log::setLevel(const string& tag, int level)
{
    lock_guard synchronized(sMutex);

    for (auto sink : sSinks) {
        sink->setLevel(tag, level);
    }
}


void Log::squelchThreadId(std::thread::id tid)
{
    lock_guard synchronized(sMutex);

    for (auto sink : sSinks) {
        sink->squelchThreadId(tid);
    }
}


void Log::unsquelchThreadId(std::thread::id tid)
{
    lock_guard synchronized(sMutex);

    for (auto sink : sSinks) {
        sink->unsquelchThreadId(tid);
    }
}


Log::Log(const string& tag)
    : mTag(tag)
{
}


void Log::setInstanceTag(const string& tag)
{
    mTag = tag;
}


string Log::getInstanceTag() const
{
    return mTag;
}


void Log::log(int level, const string& message)
{
    log(level, mTag, message);
}


void Log::log(int level, const string& message, const exception& error)
{
    log(level, mTag, message, error);
}


void Log::wtf(const std::string& message)
{
    Log::wtf(mTag, message);
}


void Log::wtf(const std::string& message, const std::exception& error)
{
    Log::wtf(mTag, message, error);
}


void Log::e(const std::string& message)
{
    Log::e(mTag, message);
}


void Log::e(const std::string& message, const std::exception& error)
{
    Log::e(mTag, message, error);
}


void Log::w(const std::string& message)
{
    Log::w(mTag, message);
}


void Log::w(const std::string& message, const std::exception& error)
{
    Log::w(mTag, message, error);
}


void Log::i(const std::string& message)
{
    Log::i(mTag, message);
}


void Log::i(const std::string& message, const std::exception& error)
{
    Log::i(mTag, message, error);
}


void Log::d(const std::string& message)
{
    Log::d(mTag, message);
}


void Log::d(const std::string& message, const std::exception& error)
{
    Log::d(mTag, message, error);
}


void Log::v(const std::string& message)
{
    Log::v(mTag, message);
}


void Log::v(const std::string& message, const std::exception& error)
{
    Log::v(mTag, message, error);
}


void Log::xtrace(const std::string& message)
{
    Log::xtrace(mTag, message);
}


void Log::xtrace(const std::string& message, const std::exception& error)
{
    Log::xtrace(mTag, message, error);
}


void Log::test(const std::string& message)
{
    Log::test(mTag, message);
}


void Log::test(const std::string& message, const std::exception& error)
{
    Log::test(mTag, message, error);
}


} }
