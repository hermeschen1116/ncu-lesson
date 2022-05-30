#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <thread>
#include <ctime>
using namespace std;
clock_t tSTART,tEND;

string exec(const char* cmd) {
    char buffer[128];
    string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);

    cout<<"task {"<<cmd<<"} finish!"<<endl;
    return result;
}

int main(){

    cout<<"start trace\n";
    //#1 trace 
	tSTART=clock(); 
	exec("tracert 1.1.1.1");
	tEND=clock();
  	cout<<"#1 trace "<<  (tEND - tSTART) / CLOCKS_PER_SEC  <<" sec"<<endl;
  	//#2
  	
  	//#3

	
	cout<<endl;
	tSTART=clock();
	//threadª© 
	
	
	tEND=clock();
  	cout<<"using thead "<<  (tEND - tSTART) / CLOCKS_PER_SEC  <<" sec"<<endl;

    return 0;
}
