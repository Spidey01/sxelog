/** file [somefile] [message]
 * - prints [message] to [somefile]
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
    if (argc < 3) {
        cout << "usage: file [path] [message]" << endl;
        return 0;
    }

    string file = argv[1];
    string tag = __FILE__;
    string message;

    for (int i=2; i < argc; ++i) {
        if (!message.empty())
            message += ' ';

        message.append(argv[i]);
    }

    auto sink = make_shared<sxe::logging::TextLogSink>(__FILE__, Log::TEST, new std::ofstream(file), true);
    Log::add(sink);

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

