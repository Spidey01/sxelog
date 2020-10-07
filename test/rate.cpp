/** rate [ms]
 * - prints the rate counter.
 * - updates every [ms].
 */

#include <sxe/logging/Log.hpp>
#include <sxe/logging/RateCounter.hpp>

#include <chrono>
#include <iostream>
#include <string>


using namespace std;
using namespace std::chrono;
using sxe::logging::Log;
using sxe::logging::RateCounter;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << " [ms]" << endl;
        return 0;
    }

    Log::add(make_shared<sxe::logging::LogSink>(__FILE__, Log::TEST, &std::cout, false));

    RateCounter rate("UpdatesPerSecond", true);

    Log::i(__FILE__, "Press control-c to stop.");

    milliseconds limit(stoi(argv[1]));
    Log::d(__FILE__, "Rate is " + to_string(limit.count()) + " ms.");

    while (true) {
        rate.update();

        this_thread::sleep_for(limit);
    }

    return 0;
}
