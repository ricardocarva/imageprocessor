#include <iostream>
#include <chrono>

// #include "leaker.h"
#include "Image.h"
#include "Header.h"
#include "Pixel.h"
#include "BlendMode.h" 
#include "Program.h"
#include <fstream>
#include <chrono>
#include <string>

using namespace std;
using hclock = std::chrono::high_resolution_clock;
using timePoint = hclock::time_point;
using ms = std::chrono::milliseconds;

unsigned int BASIC_TESTS = 5; 
unsigned int PGRM_TESTS = 10; 


/* ~~~~ Basic Tests ~~~~ */
bool Test00(); // Asserts error is thrown when passed an invalid filename to Image()
bool Test01(); // Asserts correct Header object construction
bool Test02(); // Asserts correct Pixel object constructon
bool Test03(); // Writing same image to different file 
bool Test04(); // Create a brand new img with a single color

/* ~~~~ Task Tests ~~~~ */
// Asserts the tasks' resulting image saved in the output directory matches its pair in the examples directory
bool Task1(); // Multiply
bool Task2(); // Subtract
bool Task3(); // Multiply and Screen
bool Task4(); // Multiply and Subtract
bool Task5(); // Overlay
bool Task6(); // Add 200G to car.tga
bool Task7(); // Scale R * 4, B * 0
bool Task8(); // Write each RGB channel into a separate file [R,R,R] (each are b&w)
bool Task9(); // Combine 3 channel layer files (b&w) into one (colored)
bool Task10(); // Flip img upside down
bool Task11(); // Combine 4 imgs into one

/* ~~~~ Helper Functions ~~~~ */
unsigned int basicTests();
unsigned int taskTests();
void PrintHeader(Header& _header);
void PrintPx(Pixel& px);

int main(){
    cout << "INITIALIZING TESTS FOR COP3503 IMAGE PROCESSOR" << endl;
    cout << endl;

    unsigned int results;

    timePoint start;
    timePoint stop;
    std::chrono::duration<double> duration;

    start = hclock::now();

    results = basicTests();
    cout << "Test Results: " << results << " / " << BASIC_TESTS << endl;
    cout << endl;

    results = taskTests();
    cout << "Test Results: " << results << " / " << PGRM_TESTS << endl;

    stop = hclock::now();
    duration = stop - start;
    cout << "Time to complete: " << std::chrono::duration_cast<ms>(duration).count() << " ms" << endl;

    return 0;
}
/* ~~~~ Basic Tests ~~~~ */
bool Test00(){
   try{
    Image img("./input/dne.tga");
    return false;
   } catch (runtime_error) {
    return true;
   }
}

bool Test01(){
    Header A = {0,0,2,0,0,0,0,0,512,512,24,0};
    Image img("./input/car.tga");

    Header B = img.GetHeader();

    //PrintHeader(A);
    //PrintHeader(B);

    return A == B;
}

bool Test02(){
    Pixel A = {0,189,236};

    Image img("./input/layer2.tga");
    Pixel B = img.GetPx(0);

    //PrintPx(A);
    //PrintPx(B);

    return A == B;
}

bool Test03(){
    Image A("./input/layer2.tga");

    Image copy(A);
    copy.Write("./output/test-layer2.tga");

    Image B("./output/test-layer2.tga");

    return A == B;
}

bool Test04(){
    Image A;
    A.SetDimensions(500,500);

    for (int i = 0; i < A.GetPxAmount(); i++){
        A.AddPx(216,2, 116);
    }

    A.Write("./output/test-singlecolor.tga");
    Image B("./output/test-singlecolor.tga");

    return A == B;
}

bool Task1(){
    Program program;
    program.Task1();

    Image A("./examples/EXAMPLE_part1.tga");
    Image B("./output/part1.tga");

    return A == B;
}

bool Task2(){
    Program program;
    program.Task2();

    Image A("./examples/EXAMPLE_part2.tga");
    Image B("./output/part2.tga");

    return A == B;
}

bool Task3(){
    Program program;
    program.Task3();

    Image A("./examples/EXAMPLE_part3.tga");
    Image B("./output/part3.tga");

    return A == B;
}

bool Task4(){
    Program program;
    program.Task4();

    Image A("./examples/EXAMPLE_part4.tga");
    Image B("./output/part4.tga");

    return A == B;
}

bool Task5(){
    Program program;
    program.Task5();

    Image A("./examples/EXAMPLE_part5.tga");
    Image B("./output/part5.tga");

    return A == B;
}

bool Task6(){
    Program program;
    program.Task6();

    Image A("./examples/EXAMPLE_part6.tga");
    Image B("./output/part6.tga");

    return A == B;
}

bool Task7(){
    Program program;
    program.Task7();

    Image A("./examples/EXAMPLE_part7.tga");
    Image B("./output/part7.tga");

    return A == B;
}

bool Task8(){
    Program program;
    program.Task8();

    Image A("./examples/EXAMPLE_part8_r.tga");
    Image B("./output/part8_r.tga");

    Image C("./examples/EXAMPLE_part8_g.tga");
    Image D("./output/part8_g.tga");

    Image E("./examples/EXAMPLE_part8_b.tga");
    Image F("./output/part8_b.tga");

    return ((A == B) && (C == D) && (E == F));
}

bool Task9(){
    Program program;
    program.Task9();

    Image A("./examples/EXAMPLE_part9.tga");
    Image B("./output/part9.tga");

    return A == B;
}

bool Task10(){
    Program program;
    program.Task10();

    Image A("./examples/EXAMPLE_part10.tga");
    Image B("./output/part10.tga");

    return A == B;
}

bool Task11(){
    Program program;
    program.Task11();

    Image A("./examples/EXAMPLE_extracredit.tga");
    Image B("./output/extracredit.tga");

    return A == B;
}

/* ~~~~ Helper Functions ~~~~ */
unsigned int basicTests(){
    unsigned int success = 0;

    cout << "Running Basic Tests..." << endl;

    cout << "Test #00............... ";
    if (Test00()){
       cout << "Passed!" << endl;
       success += 1; 
    } else { cout << "Failed!" << endl; }

    cout << "Test #01............... ";
    if (Test01()){ 
        cout << "Passed!" << endl;
        success += 1;
    } else { cout << "Failed!" << endl; }

    cout << "Test #02............... ";
    if (Test02()){ 
        cout << "Passed!" << endl;
        success += 1;
    } else { cout << "Failed!" << endl; }

    cout << "Test #03............... ";
    if (Test03()){ 
        cout << "Passed!" << endl;
        success += 1;
    } else { cout << "Failed!" << endl; }

    cout << "Test #04............... ";
    if (Test04()){ 
        cout << "Passed!" << endl;
        success += 1;
    } else { cout << "Failed!" << endl; }

    cout << endl;
    return success;
}

unsigned int taskTests(){
   unsigned int success = 0;
   cout << "Running Task Tests..." << endl;

    cout << "Test #01............... ";
    if (Task1()){
       cout << "Passed!" << endl;
       success += 1; 
    } else { cout << "Failed!" << endl; }

    cout << "Test #02............... ";
    if (Task2()){
       cout << "Passed!" << endl;
       success += 1; 
    } else { cout << "Failed!" << endl; }

    cout << "Test #03............... ";
    if (Task3()){
       cout << "Passed!" << endl;
       success += 1; 
    } else { cout << "Failed!" << endl; }

    cout << "Test #04............... ";
    if (Task4()){
       cout << "Passed!" << endl;
       success += 1; 
    } else { cout << "Failed!" << endl; }

    cout << "Test #05............... ";
    if (Task5()){
       cout << "Passed!" << endl;
       success += 1; 
    } else { cout << "Failed!" << endl; }

    cout << "Test #06............... ";
    if (Task6()){
       cout << "Passed!" << endl;
       success += 1; 
    } else { cout << "Failed!" << endl; }

    cout << "Test #07............... ";
    if (Task7()){
       cout << "Passed!" << endl;
       success += 1; 
    } else { cout << "Failed!" << endl; }

    cout << "Test #08............... ";
    if (Task8()){
       cout << "Passed!" << endl;
       success += 1; 
    } else { cout << "Failed!" << endl; }

    cout << "Test #09............... ";
    if (Task9()){
       cout << "Passed!" << endl;
       success += 1; 
    } else { cout << "Failed!" << endl; }

    cout << "Test #10............... ";
    if (Task10()){
       cout << "Passed!" << endl;
       success += 1; 
    } else { cout << "Failed!" << endl; }

    cout << "Test #11............... ";
    if (Task11()){
       cout << "Passed!" << endl;
       success += 1; 
    } else { cout << "Failed!" << endl; }

    cout << endl;
    return success; 
}

void PrintHeader(Header& _header){
    cout << "ID Length: " << (int)_header.idLength << endl;
    cout << "Color Map Type: " <<(int)_header.colorMapType << endl;
    cout << "Data Type Code: " << (int)_header.dataTypeCode << endl;
    cout << "Color Map Origin: " << _header.colorMapOrigin << endl;
    cout << "Color Map Length: " << _header.colorMapLength << endl;
    cout << "Color Map Depth: " << (int)_header.colorMapDepth << endl;
    cout << "X Origin: " << _header.xOrigin << endl;
    cout << "Y Origin: " << _header.yOrigin << endl;
    cout << "Width: " << _header.width << endl;
    cout << "Height: " << _header.height << endl;
    cout << "Bits Per Pixel: " << (int)_header.bitsPerPixel << endl;
    cout << "Image Descriptor: " << (int)_header.imageDescriptor << endl;
    cout << endl;
}

void PrintPx(Pixel& px){
    cout << "R: " << (int)px._R << " G: " << (int)px._G << " B: " << (int)px._B << endl;
    cout << endl;
}

