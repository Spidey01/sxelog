/** squelch [true | false]
 * - prints messages while squelched or not.
 */

#include <sxe/logging/Log.hpp>
#include <sxe/logging/LogSquelch.hpp>

#include <cstring>
#include <iostream>
#include <string>
#include <memory>
#include <thread>

using sxe::logging::Log;
using sxe::logging::LogSquelch;

void run(bool squelch)
{
    Log::i(__func__, "starting.");

    {
        std::unique_ptr<LogSquelch> silence = nullptr;

        if (squelch)
            silence = std::make_unique<LogSquelch>(std::this_thread::get_id(), Log::WARN, __func__, "from run()");

        for (int i = 0; i < 10; ++i) {
            Log::w(__func__, "run(): message " + std::to_string(i));
        }
    }

    Log::i(__func__, "exiting.");
}

int main(int argc, char* argv[])
{
    Log::autovivification(true);
    Log::i(__func__, "starting");

    if (argc == 1) {
        std::cout << "usage: squelch [true | false]" << std::endl;
        return 0;
    }

    bool squelch = false;
    if (std::strcmp(argv[1], "true") == 0)
        squelch = true;
    else if (std::strcmp(argv[1], "false") == 0)
        squelch = false;
    else
        Log::w(__func__, "bad argv[1]: " + std::string(argv[1]));
    Log::i(__func__, "squelch = " + std::string(argv[1]));


    Log::i(__func__, "Spawning thread.");
    std::thread job(&run, squelch);

    Log::i(__func__, "Joining thread.");
    job.join();

    Log::i(__func__, "returning");
    return 0;
}
