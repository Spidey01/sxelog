/** customsink [message]
 * - prints [message] to each log level.
 * - Format is very different from TextLogSink.
 */

#include <sxe/logging/Log.hpp>
#include <sxe/logging/LogSink.hpp>

#include <iostream>
#include <memory>
#include <string>

using namespace std;
using sxe::logging::Log;

/** Outputs to cout with a custom format.
 */
class CustomSink : public sxe::logging::LogSink
{
  public:
    CustomSink(int level)
        : LogSink(__FILE__, level)
    {
    }

    CustomSink()
        : LogSink(__FILE__, LogSink::DEFAULT_LOG_LEVEL)
    {
    }

    /** Prints the header.
     * 
     *     {sink name}    {translated tag}
     *         thread id xxx
     *         {year}-{month}-{day}T{hour}:{minutes}:{seconds}
     */
    void onHeader(int level, const string_type& tag) override
    {
        cout << getName() << '\t' << translate(level) << '\t' << tag;

        if (getDisplayThreadId()) {
            cout << endl
                 << '\t' << "thread id " << std::this_thread::get_id();
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
            cout << endl
                 << '\t' << std::put_time(&now, "%Y-%m-%d");
        }

        if (getDisplayTime()) {
            if (getDisplayDate())
                cout << 'T';
            else
                cout << endl
                     << '\t';
            cout << std::put_time(&now, "%h:%M:%S");
        }
    }

    void onWrite(const string_type& message) override
    {
        cout << endl
             << '\t' << '\t' << message << std::endl;
    }
};

int main(int argc, char* argv[])
{
    if (argc == 1) {
        cout << "usage: customsink [options]" << endl;
        return 0;
    }

    string tag = "customsink.cpp";
    string message;

    for (int i=1; i < argc; ++i) {
        if (!message.empty())
            message += ' ';

        message.append(argv[i]);
    }

    Log::add(make_shared<CustomSink>(Log::TEST));

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
