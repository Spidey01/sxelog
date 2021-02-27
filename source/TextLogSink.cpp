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


#include <sxe/logging/TextLogSink.hpp>

namespace sxe { namespace logging {

TextLogSink::TextLogSink()
    : TextLogSink(LogSink::DEFAULT_LOG_NAME, LogSink::DEFAULT_LOG_LEVEL, std::clog)
{
}

#if SXELOG_CXX17
TextLogSink::TextLogSink(const string_type& name, int level, const path_type& path)
    : TextLogSink(name, level, new std::fstream(path.string(), std::ios::app), true)
{
}
#endif

TextLogSink::TextLogSink(const string_type& name, int level, std::ostream& stream)
    : TextLogSink(name, level, &stream, false)
{
}

TextLogSink::TextLogSink(const string_type& name, int level, std::ostream* stream, bool deleteMe)
    : LogSink(name, level)
    , mOutput(stream)
    , mDeleteMe(deleteMe)
{
}

TextLogSink::~TextLogSink()
{
    if (mDeleteMe && mOutput != nullptr)
        delete mOutput;
}

std::ostream& TextLogSink::stream()
{
    assert(mOutput != nullptr);
    return *mOutput;
}

void TextLogSink::onHeader(int level, const string_type& tag)
{
    *mOutput << translate(level) << '/' << tag;
    *mOutput << '(';

    bool prefixComma = false;

    if (getDisplayThreadId()) {
        *mOutput << " tid=" << std::this_thread::get_id();
        prefixComma = true;
    }

    auto t_now = std::time(nullptr);
    std::tm now;

#if defined(_MSC_VER)
    gmtime_s(&now, &t_now);
#elif defined(__unix__)
    gmtime_r(&t_now, &now);
#else
    now = *std::gmtime(&t_now);
#endif

    if (getDisplayDate()) {
        if (prefixComma)
            *mOutput << ',';
        else
            prefixComma = true;

        static const char* format = "%Y-%m-%d";
        *mOutput << " date=" << std::put_time(&now, format);
    }

    if (getDisplayTime()) {
        if (prefixComma)
            *mOutput << ',';
        else
            prefixComma = true;

        static const char* format = "%H:%M:%S";
        *mOutput << " time=" << std::put_time(&now, format);
    }

    *mOutput << " ): ";
}

void TextLogSink::onWrite(const string_type& message)
{
    *mOutput << message << std::endl;
}

} }
