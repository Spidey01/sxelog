#ifndef SXE_LOGGING_LOGSINK__HPP
#define SXE_LOGGING_LOGSINK__HPP
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

namespace sxe { namespace logging {

    /** Sink for consuming statements from Log.
     *
     * The default implementation simply works with a std::ostream. Like std::cout or std::clog.
     */
    class LogSink
        : public sxe::logging::stdtypedefs<LogSink>
    {
      public:

        /** Default log level set in ctors without a level param. */
        SXELOG_EXPORT static const int DEFAULT_LOG_LEVEL;

        /** Default log name in ctors without a name param. */
        SXELOG_EXPORT static const char* DEFAULT_LOG_NAME;

        /** Uses default constants.
         */
        SXELOG_EXPORT LogSink();

        /* Create a base log sink.
         *
         * @param name the base name of the log sink itself.
         * @param level the default level.
         */
        SXELOG_EXPORT LogSink(const string_type& name, int level);

        SXELOG_EXPORT virtual ~LogSink();

        SXELOG_EXPORT void log(int level, const string_type& tag, const string_type& message);

        /** Test if tag loggable.
         *
         * @returns true if messages for tag/level would be written.
         */
        SXELOG_EXPORT bool isLoggable(const string_type& tag, int level) const;

        /* Returns log level for tag.
         */
        SXELOG_EXPORT int getLevel(const string_type& tag) const;

        /* Sets log level for tag.
         */
        SXELOG_EXPORT void setLevel(const string_type& tag, int level);

        SXELOG_EXPORT int getDefaultLevel() const;

        /** Sets the default log level.
         *
         * This is comparable to setting the level in the constructor but does not
         * modify any levels already set.
         */
        SXELOG_EXPORT void setDefaultLevel(int level);

        /** Returns the name of the log.
         *
         * This doesn't mean filename or pathname, it's just the 'name' param
         * from the ctor.
         */
        SXELOG_EXPORT const string_type& getName() const;

        /** Rename the log sink.
         * 
         * Default implementation changes the value returned by getName().
         */
        SXELOG_EXPORT virtual void setName(const string_type& name);

        SXELOG_EXPORT bool getDisplayThreadId() const;
        SXELOG_EXPORT void setDisplayThreadId(bool x);

        SXELOG_EXPORT bool getDisplayDate() const;
        SXELOG_EXPORT void setDisplayDate(bool x);

        SXELOG_EXPORT bool getDisplayTime() const;
        SXELOG_EXPORT void setDisplayTime(bool x);

        /** Squelch messages from thread.
         * 
         * @param tid the thread id.
         */
        SXELOG_EXPORT void squelchThreadId(std::thread::id tid);

        /** Unsquelch messages from thread.
         * 
         * @param tid the thread id.
         */
        SXELOG_EXPORT void unsquelchThreadId(std::thread::id tid);

      protected:

        /** Translates log level to word for header().
         * 
         * Default implementation returns either a super short string like 'v'
         * for VERBOSE level or 'xtrace' for TRACE level.
         * 
         * Unknown levels are mapped to "UNKNOWN".
         */
        SXELOG_EXPORT virtual string_type translate(int level) const;

        /** Writes the log header to the sink.
         *
         * Default implementation does nothing. Override this to prefix log
         * messages with a header.
         * 
         * @param level the log level for incoming message.
         * @param tag the logging tag for incoming message.
         */
        SXELOG_EXPORT virtual void onHeader(int level, const string_type& tag);

        /** Writes the log message to the sink.
         * 
         * Default implementation does nothing. Implement this to make the
         * magic happen. E.g. write to a file, socket, database, etc.
         * 
         * @param message the log message to write.
         */
        SXELOG_EXPORT virtual void onWrite(const string_type& message);

      private:

        /** Name of the log sink.
         */
        string_type mName;

        /** Default logging level for the sink. */
        int mDefaultLevel;

        /** Map of log tag -> log level.
         */
        using Filters = std::map<string_type, int>;
        Filters mFilters;


        using ThreadIdList = std::vector<std::thread::id>;

        /* List of squelched thread IDs.
         */
        ThreadIdList mSquelchedThreadIdList;

        /** Whether or not std::this_thread::get_id() should be included in onHeader().
         */
        bool mDisplayThreadId;

        /** Whether or not the current date should be included in onHeader().
         */
        bool mDisplayDate;

        /** Whether or not the current time should be included in onHeader().
         */
        bool mDisplayTime;

    };

} }

#endif // SXE_LOGGING_LOGSINK__HPP
