#ifndef SXE_LOGGING_LOGSQUELCH__HPP
#define SXE_LOGGING_LOGSQUELCH__HPP
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

#include <sxe/logging/api.hpp>

namespace sxe { namespace logging {

    /** RAII style class for squelching logging.
     * 
     * This creates logging filters that ignore log messages. On destruction
     * the filters will be cleared.
     */
    class SXELOG_PUBLIC LogSquelch
    {
      public:
        /** Squelch all logging for thread id.
         * 
         * @param tid ID of the thread to be squelched.
         * @param level used to log why.
         * @param tag used to log why.
         * @param why included in log message about squelch/unsquelch.
         */
        LogSquelch(std::thread::id tid, int level, const std::string& tag, const std::string& why);

        /** Unsquelches the logging.
         */
        ~LogSquelch();

      private:
        std::thread::id mThreadId;
        int mLevel;
        std::string mTag;
        std::string mWhy;
    };

} }

#endif // SXE_LOGGING_LOGSQUELCH__HPP