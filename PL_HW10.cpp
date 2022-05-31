#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <string>
#include <thread>
#include <ctime>

using namespace std;
clock_t tSTART;
clock_t tEND;

string exec(const char *cmd);

int main() {

    cout << "start trace" << endl;
    // #1 trace
    tSTART = clock();
    exec("traceroute 1.1.1.1");
    tEND = clock();
    cout << "#1 trace " << (tEND - tSTART) / CLOCKS_PER_SEC << " sec" << endl;
    // #2
    tSTART = clock();
    exec("traceroute 8.8.8.8");
    tEND = clock();
    cout << "#2 trace " << (tEND - tSTART) / CLOCKS_PER_SEC << " sec" << endl;
    // #3
    tSTART = clock();
    exec("traceroute 168.95.1.1");
    tEND = clock();
    cout << "#3 trace " << (tEND - tSTART) / CLOCKS_PER_SEC << " sec" << endl;


    cout << endl;
    tSTART = clock();
    // thread
    auto ping1 = thread(exec, "traceroute 1.1.1.1");
    auto ping2 = thread(exec, "traceroute 8.8.8.8");
    auto ping3 = thread(exec, "traceroute 168.95.1.1");
    ping1.join();
    ping2.join();
    ping3.join();
    tEND = clock();
    cout << "using thead " << (tEND - tSTART) / CLOCKS_PER_SEC << " sec" << endl;

    return 0;
}

string exec(const char *cmd) {
    char buffer[128];
    string result;
    FILE *pipe = popen(cmd, "r");

    if (!pipe) throw runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);

    cout << "task {" << cmd << "} finish!" << endl;
    return result;
}