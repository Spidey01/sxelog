/** spam [level] [limit] [ms]
 * - sets default log to [level].
 * - prints a message to each log level every [ms], [limit] times.
 */

#include <sxe/logging/Log.hpp>
#include <sxe/logging/TextLogSink.hpp>

#include <iostream>
#include <memory>
#include <string>

using namespace std;
using sxe::logging::Log;

int main(int argc, char* argv[])
{
    string tag = __FILE__;
    string message;
    int level = sxe::logging::TextLogSink::DEFAULT_LOG_LEVEL;
    if (argc > 1)
        level = Log::stringToLevel(argv[1]);
    size_t limit = 10;
    if (argc > 2)
        limit = stoi(argv[2]);
    auto interval = std::chrono::milliseconds::zero();
    if (argc > 3)
        interval = std::chrono::milliseconds(stoi(argv[3]));

    Log::add(make_shared<sxe::logging::TextLogSink>(__FILE__, level, &std::cout, false));

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

    for (size_t i = 0; i < limit; ++i) {
        for (int level : levels) {
            Log::log(level, tag, "message " + to_string(i));
        }
        this_thread::sleep_for(interval);
    }

    return 0;
}
