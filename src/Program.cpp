#include <iostream>

#include "Program.h"
#include "Image.h"
#include "Header.h"
#include "Pixel.h"

using namespace std;

/* ~~~~~~~~ Tasks ~~~~~~~~ */
void Program::Task1(){
    // Use the Multiply blending mode to combine “layer1.tga” (top layer) with “pattern1.tga” (bottom layer).
    Image A("./input/layer1.tga");
    Image B("./input/pattern1.tga");
    Image C(A.GetHeader());

    BlendMode::Multiply(A,B,C);
    C.Write("./output/part1.tga");
}

void Program::Task2(){
    // Use the Subtract blending mode to combine “layer2.tga” (top layer) with “car.tga” (bottom layer). This mode subtracts the top layer from the bottom layer.
    Image A("./input/layer2.tga");
    Image B("./input/car.tga");
    Image C(A.GetHeader());

    BlendMode::Subtract(A,B,C);
    C.Write("./output/part2.tga"); 
}

void Program::Task3(){
    // Use the Multiply blending mode to combine “layer1.tga” with “pattern2.tga”, and store the results temporarily. 
    // Load the image “text.tga” and, using that as the top layer, combine it with the previous results of layer1/pattern2 using the Screen blending mode.
    Image A("./input/layer1.tga");
    Image B("./input/pattern2.tga");
    Image C(A.GetHeader());

    BlendMode::Multiply(A,B,C);

    Image D("./input/text.tga");
    Image E(D.GetHeader());

    BlendMode::Screen(D,C,E);

    E.Write("./output/part3.tga"); 
}

void Program::Task4(){
    // Multiply “layer2.tga” with “circles.tga”, and store it. 
    // Load “pattern2.tga” and, using that as the top layer, combine it with the previous result using the Subtract blending mode.
    Image A("./input/layer2.tga");
    Image B("./input/circles.tga");
    Image C(A.GetHeader());

    Image D("./input/pattern2.tga");
    Image E(D.GetHeader());

    BlendMode::Multiply(A,B,C);
    BlendMode::Subtract(D,C,E);

    E.Write("./output/part4.tga"); 
}

void Program::Task5(){
    // Combine “layer1.tga” (as the top layer) with “pattern1.tga” using the Overlay blending mode.
    Image A("./input/layer1.tga");
    Image B("./input/pattern1.tga");
    Image C(A.GetHeader());

    BlendMode::Overlay(A,B,C);
    C.Write("./output/part5.tga");
}

void Program::Task6(){
    // Load “car.tga” and add 200 to the green channel.
    Image A("./input/car.tga");
    Image B(A.GetHeader());

    BlendMode::Greenify(A,B);
    B.Write("./output/part6.tga");
}

void Program::Task7(){
    // Load “car.tga” and scale the red channel by 4, and the blue channel by 0. 
    // This will increase the intensity of any red in the image, while negating any blue it may have.
    Image A("./input/car.tga");
    Image B(A.GetHeader());

    BlendMode::ScaleRB(A,B);
    B.Write("./output/part7.tga"); 
}

void Program::Task8(){
    // Load “car.tga” and write each RGB channel to a separate file.
    Image RGB("./input/car.tga");
    Image R(RGB.GetHeader());
    Image G(RGB.GetHeader());
    Image B(RGB.GetHeader());

    BlendMode::SplitColorChannels(RGB,R,G,B);
    R.Write("./output/part8_r.tga");
    G.Write("./output/part8_g.tga"); 
    B.Write("./output/part8_b.tga");  
}

void Program::Task9(){
    // Load “layer_red.tga”, “layer_green.tga” and “layer_blue.tga”, and combine the three files into one file.
    Image R("./input/layer_red.tga");
    Image G("./input/layer_green.tga"); 
    Image B("./input/layer_blue.tga");  
    Image RGB(R.GetHeader());

    BlendMode::CombineColorChannels(R,G,B,RGB);
    RGB.Write("./output/part9.tga");
}

void Program::Task10(){
    // Load “text2.tga”, and rotate it 180 degrees, flipping it upside down.
    Image A("./input/text2.tga");
    Image B(A.GetHeader());

    BlendMode::Rotate180(A,B);
    B.Write("./output/part10.tga"); 
}

void Program::Task11(){
    // Create a new file that is the combination of car.tga, circles.tga, pattern1.tga, and text.tga. 
    Image A("./input/car.tga");
    Image B("./input/circles.tga");
    Image C("./input/text.tga");
    Image D("./input/pattern1.tga");
    Image E;

    int width = A.GetHeader().width * 2;
    int height = A.GetHeader().height * 2;
    E.SetDimensions(height, width);

    BlendMode::CombineImages(A,B,C,D,E);
    E.Write("./output/extracredit.tga"); 
}