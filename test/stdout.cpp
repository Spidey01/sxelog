/** stdout [message]
 * - prints [message] to each log level.
 */

#include <sxe/logging/Log.hpp>

#include <iostream>
#include <memory>
#include <string>

using namespace std;
using sxe::logging::Log;

int main(int argc, char* argv[])
{
    if (argc == 1) {
        cout << "usage: stdout [options]" << endl;
        return 0;
    }

    string tag = __FILE__;
    string message;

    for (int i=1; i < argc; ++i) {
        if (!message.empty())
            message += ' ';

        message.append(argv[i]);
    }

    Log::add(make_shared<sxe::logging::LogSink>(__FILE__, Log::TEST, &std::cout, false));

    int levels[] = {
        Log::TEST,
        Log::TRACE,
        Log::VERBOSE,
        Log::DEBUG,
        Log::INFO,
        Log::WARN,
        Log::ERROR,
        Log::ASSERT,
    };

    for (int level : levels) {
        Log::log(level, tag, message);
    }

    return 0;
}
