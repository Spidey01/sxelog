#ifndef SXE_LOGGING_LOG__HPP
#define SXE_LOGGING_LOG__HPP
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

#include <sxe/logging/api.hpp>
#include <sxe/logging/stdtypedefs.hpp>
#include <sxe/logging/LogSink.hpp>

namespace sxe { namespace logging {

    /** Logging support for SxE.
     *
     * The goal here is to generally do the right thing.
     *
     * Logging is a simple Android inspired API based on log levels. Each log level
     * has a set of related methods.  This is backwards compatable with the Android
     * API, while allowing good freedom for a more specialized logging API.
     *
     * In SxE the destination of log messages can be customized. Everything is
     * logged to a collection LogSink's according to the log levels and tags
     * supplied with the message.  Logging is controlled by a per 'tag' log level.
     * So it is entirely possible to send log data to multiple sources and to
     * configure each source based on tag/level.
     *
     * By default there are no log sinks, which causes all log data to be
     * silenced until sinks are added. Use the autovivification() method if you
     * want a sensible default created out of thin air.
     *
     * There are two ways to use Log:
     *
     *   1. Invoke static methods.
     *     - These are the primary interface to make the magic happen.
     *
     *   2. Create a Log instance.
     *     - Provides a way to do mLog.foo(...).
     *     - Calls the static methods with data filled in from ctor.
     *
     */
    class Log
        : public sxe::logging::stdtypedefs<Log>
    {
      public:

        // Android mimicery: least to most: ERROR, WARN, INFO, DEBUG, VERBOSE.
        enum {
            ASSERT  = 0,
            ERROR   = 1,
            WARN    = 2,
            INFO    = 3,
            DEBUG   = 4,
            VERBOSE = 5,
            TRACE   = 10,
            TEST    = 999,
        };

        /** Enable or disable autovivification.
         * 
         * By default autovivification is disabled.
         * 
         * When enabled:
         * 
         * If no log sinks exist: a StandardOutputLogSink will be created with
         * its default constructor and passed to setDefaultLogSink(). Thus
         * creating a log sink on first use of the interface with the most
         * universal defaults.
         */
        SXELOG_EXPORT static void autovivification(bool enabled);

        /** Controls terrible failure handling.
         * 
         * By default this is disabled.
         * 
         * @see wtf().
         */
        SXELOG_EXPORT static void wtfCallsTerminate(bool enabled);

        /** Returns enum value as string.
         *
         * Unknown values are mapped to "".
         */
        SXELOG_EXPORT static std::string levelToString(int level);

        /** Returns enum value for string.
         *
         * For each enum value, its string form (e.g. "ERROR") and its base-10
         * form (e.g. 1) are supported as input. If the former fails,
         * std::stoi() will be tried before declaring it an unknown value.
         *
         * Unknown values are mapped to Log::ASSERT.
         */
        SXELOG_EXPORT static int stringToLevel(const std::string& level);

        /** Send an ASSERT message.
         *
         * Report a condition that should never happen. A false assertion will also
         * be triggered if assertions are enabled.  Android and the assertion
         * method calls this "What a Terrible Failure" but you may call it by other
         * names if you wish ;).
         * 
         * When NDEBUG is defined this simply logs unless wtfCallsTerminate()
         * has been enabled.
         * 
         * When wtfCallsTerminate() has been enabled: std::terminate() will be
         * called after assert(). Use this if you want wtf() to force the
         * program to abort even when NDEBUG has been defined.
         */
        SXELOG_EXPORT static void wtf(const std::string& tag, const std::string& message);
        SXELOG_EXPORT static void wtf(const std::string& tag, const std::string& message, const std::exception& error);

        /** Send an ERROR message. */
        SXELOG_EXPORT static void e(const std::string& tag, const std::string& message);
        SXELOG_EXPORT static void e(const std::string& tag, const std::string& message, const std::exception& error);

        /** Send an WARN message. */
        SXELOG_EXPORT static void w(const std::string& tag, const std::string& message);
        SXELOG_EXPORT static void w(const std::string& tag, const std::string& message, const std::exception& error);

        /** Send an INFO message. */
        SXELOG_EXPORT static void i(const std::string& tag, const std::string& message);
        SXELOG_EXPORT static void i(const std::string& tag, const std::string& message, const std::exception& error);

        /** Send an DEBUG message. */
        SXELOG_EXPORT static void d(const std::string& tag, const std::string& message);
        SXELOG_EXPORT static void d(const std::string& tag, const std::string& message, const std::exception& error);

        /** Send an VERBOSE message. */
        SXELOG_EXPORT static void v(const std::string& tag, const std::string& message);
        SXELOG_EXPORT static void v(const std::string& tag, const std::string& message, const std::exception& error);

        /** Send an TRACE message. */
        SXELOG_EXPORT static void xtrace(const std::string& tag, const std::string& message);
        SXELOG_EXPORT static void xtrace(const std::string& tag, const std::string& message, const std::exception& error);

        /** Send an TEST message. */
        SXELOG_EXPORT static void test(const std::string& tag, const std::string& message);
        SXELOG_EXPORT static void test(const std::string& tag, const std::string& message, const std::exception& error);

        /** Send a message to all sinks.
        */
        SXELOG_EXPORT static void log(int level, const std::string& tag, const std::string& message);

        /** Adds exception to log message.
         */
        SXELOG_EXPORT static void log(int level, const std::string& tag, const std::string& message, const std::exception& error);

        /** Add log sink.
         */
        SXELOG_EXPORT static void add(LogSink::shared_ptr sink);

        /** Remove log sink.
         */
        SXELOG_EXPORT static void remove(LogSink::shared_ptr sink);

        using LogSinkList = std::list<LogSink::weak_ptr>;

        SXELOG_EXPORT static LogSinkList getSinks();

        /** Get the specified LogSink.
         * @param name which log sink you want.
         * @returns the sink whose LogSink::name() matches.
         */
        SXELOG_EXPORT static LogSink::shared_ptr getLogSink(const std::string& name);

        /** Returns the default log sink.
         * 
         * Quite imaginatively this is equal to getLogSink("default").
         */
        SXELOG_EXPORT static LogSink::shared_ptr getDefaultLogSink();

        /** Sets the default log sink.
         * 
         * Removes the default log sink. Sets sink's name to "default", and adds it.
         */
        SXELOG_EXPORT static void setDefaultLogSink(LogSink::shared_ptr sink);

        /** Return if tag is loggable at level.
         */
        SXELOG_EXPORT static bool isLoggable(const std::string& tag, int level);

        /** Convenience method that sets the level of tag for every sink. */
        SXELOG_EXPORT static void setLevel(const std::string& tag, int level);

        /** Squelch log messages from a thread.
         * 
         * Only LogSinks currently added will be affected. There is no effect
         * on newly created or added LogSinks after this call.
         * 
         * @param tid the thread id to be silenced.
         */
        SXELOG_EXPORT static void squelchThreadId(std::thread::id tid);

        /** Unsquelch log messages from a thread.
         * 
         * @param tid the thread id to be heard.
         */
        SXELOG_EXPORT static void unsquelchThreadId(std::thread::id tid);

        /** Creates a log instance for tag.
         *
         * Use this if you want to do something like mLog.xtrace(msg, ex) instead of Log::xtrace(TAG, msg, ex).
         *
         * Use this if you want to pass an object that other code can log without having to know the tag.
         *
         * You could also inherit this.
         */
        SXELOG_EXPORT Log(const std::string& tag);

        /** Change the logging tag for this instance.
         *
         * @param tag sets mTag.
         */
        SXELOG_EXPORT void setInstanceTag(const std::string& tag);

        /** Returns the tag for this instance.
         */
        SXELOG_EXPORT std::string getInstanceTag() const;

        /** Calls the static version. */
        SXELOG_EXPORT void log(int level, const std::string& message);

        /** Calls the static version. */
        SXELOG_EXPORT void log(int level, const std::string& message, const std::exception& error);

        SXELOG_EXPORT void wtf(const std::string& message);
        SXELOG_EXPORT void wtf(const std::string& message, const std::exception& error);
        SXELOG_EXPORT void e(const std::string& message);
        SXELOG_EXPORT void e(const std::string& message, const std::exception& error);
        SXELOG_EXPORT void w(const std::string& message);
        SXELOG_EXPORT void w(const std::string& message, const std::exception& error);
        SXELOG_EXPORT void i(const std::string& message);
        SXELOG_EXPORT void i(const std::string& message, const std::exception& error);
        SXELOG_EXPORT void d(const std::string& message);
        SXELOG_EXPORT void d(const std::string& message, const std::exception& error);
        SXELOG_EXPORT void v(const std::string& message);
        SXELOG_EXPORT void v(const std::string& message, const std::exception& error);
        SXELOG_EXPORT void xtrace(const std::string& message);
        SXELOG_EXPORT void xtrace(const std::string& message, const std::exception& error);
        SXELOG_EXPORT void test(const std::string& message);
        SXELOG_EXPORT void test(const std::string& message, const std::exception& error);


      private:
        using lock_guard = std::lock_guard<std::recursive_mutex>;

        /* Used for synchronizing access to log sinks.
         */
        SXELOG_EXPORT static lock_guard::mutex_type sMutex;

        SXELOG_EXPORT static bool sAutovivification;

        SXELOG_EXPORT static bool sWtfCallsTerminate;

        /** Instance tag.
         */
        std::string mTag;
    };


} }

#endif // SXE_LOGGING_LOG__HPP
