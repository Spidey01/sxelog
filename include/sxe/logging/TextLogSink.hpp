#ifndef SXE_LOGGING_TEXTLOGSINK__HPP
#define SXE_LOGGING_TEXTLOGSINK__HPP
/*-
 * Copyright (c) 2020-current, Terry Mathew Poulin <BigBoss1964@gmail.com>
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

namespace sxe { namespace logging {

    /** LogSink implemented as an ostream for text format.
     *
     * Log format takes the form of:
     * 
     *      Level/TAG(PARAMS): MESSAGE
     * 
     * Where:
     * - Level is string from translate() of the log level.
     * - TAG is the logging tag.
     * - PARAMS is a header based on config. E.g. include date, time, thread, ...
     * - MESSAGE is the log message.
     */
    class TextLogSink
        : public LogSink
    {
      public:

        /** Uses std::clog and the default constants.
         */
        SXELOG_EXPORT TextLogSink();

#if SXELOG_CXX17
        /* Create a log sink from a filesystem path.
         *
         * @param name the base name of the log.
         * @param level the default level.
         * @param path the log file to create.
         */
        SXELOG_EXPORT TextLogSink(const string_type& name, int level, const path_type& path);
#endif

        /* LogSink(name, level, *stream, false);
         */
        SXELOG_EXPORT TextLogSink(const string_type& name, int level, std::ostream& stream);

        /* Create a log sink from an existing ostream.
         *
         * @param name the base name of the log.
         * @param level the default level.
         * @param stream the stream to write to.
         * @param deleteMe if true: delete stream on dtor.
         */
        SXELOG_EXPORT TextLogSink(const string_type& name, int level, std::ostream* stream, bool deleteMe);

        SXELOG_EXPORT virtual ~TextLogSink();

      protected:

        /** Returns a reference to the output stream.
         */
        SXELOG_EXPORT std::ostream& stream();

        /** Writes the log header to the stream.
         *
         * Default implementation is suitable for plain text logging formats.
         *
         *  - "{translate(Level)}/{tag}( tid={thread id}, date={date}, time={time} ): "
         *
         *  Where the various key=value are determined by the associated
         *  methods, like getDisplayTime().
         */
        SXELOG_EXPORT virtual void onHeader(int level, const string_type& tag) override;

        SXELOG_EXPORT virtual void onWrite(const string_type& message) override;

      private:

        string_type mName;
        std::ostream* mOutput;
        bool mDeleteMe;
    };

} }

#endif // SXE_LOGGING_TEXTLOGSINK__HPP