#include <iostream>
#include "Program.h"

#include <fstream>
#include <chrono>
#include <string>

using namespace std;
using hclock = std::chrono::high_resolution_clock;
using timePoint = hclock::time_point;
using ms = std::chrono::milliseconds;


int main(){
    timePoint start;
    timePoint stop;
    std::chrono::duration<double> duration;


cout << "WELCOME TO COP3503 IMAGE PROCESSOR! :)" << endl;
    cout << endl;

    start = hclock::now();

    Program program;

    cout << "Task01......";
    program.Task1();
    cout << " Completed!" << endl;

    cout << "Task02......";
    program.Task2();
    cout << " Completed!" << endl;

    cout << "Task03......";
    program.Task3();
    cout << " Completed!" << endl;

    cout << "Task04......";
    program.Task4();
    cout << " Completed!" << endl;

    cout << "Task05......";
    program.Task5();
    cout << " Completed!" << endl;

    cout << "Tas0k6......";
    program.Task6();
    cout << " Completed!" << endl;

    cout << "Task07......";
    program.Task7();
    cout << " Completed!" << endl;

    cout << "Task08......";
    program.Task8();
    cout << " Completed!" << endl;

    cout << "Task09......";
    program.Task9();
    cout << " Completed!" << endl;

    cout << "Task10......";
    program.Task10();
    cout << " Completed!" << endl;
    cout << endl;

    cout << "Extra Credit......";
    program.Task11();
    cout << " Completed!" << endl;

    stop = hclock::now();
    duration = stop - start;

    cout << endl;
    cout << "Time to complete: " << std::chrono::duration_cast<ms>(duration).count() << " ms" << endl;
}

