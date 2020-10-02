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

#include <sxe/logging/LogSquelch.hpp>

#include <sxe/logging/Log.hpp>

using std::string;
using std::thread;

namespace sxe { namespace logging {

LogSquelch::LogSquelch(thread::id tid, int level, const string& tag, const string& why)
    : mThreadId(tid)
    , mLevel(level)
    , mTag(tag)
    , mWhy(why)
{
    sxe::logging::Log::log(mLevel, mTag, "Constructing LogSquelch: " + mWhy);
    sxe::logging::Log::squelchThreadId(mThreadId);
}

LogSquelch::~LogSquelch()
{
    sxe::logging::Log::log(mLevel, mTag, "Destroying LogSquelch: " + mWhy);
    sxe::logging::Log::unsquelchThreadId(mThreadId);
}

} }
