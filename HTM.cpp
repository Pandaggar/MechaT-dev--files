#include "HTM.h"

void HTM::HipVec(double L1,double L2,double A,double B, double L, double M, double K, int* vx, int* vy, int* vz){
        //LMK is origin values, L1 length of rod 1, L2 length of rod 2, A,B is angles of pot a,b, vx vy and vz are output vector
        double x1 = 0;
        double y1 = 0;
        double z1 = 0;
        double x1r = 0;
        double x3 = 0;
        double y3 = 0;
        double z3 = 0;
        double x2 = 0;
        double y2 = 0;
        double Jh = 0;
        double Ih = 0;

        //endpoint one:
        x1r = (L1* cos(Rad(A)));
        x1 = ((ceil((L1* cos(Rad(A))) * 100) / 100)+L);
        y1 = M;
        z1 = ((ceil((L1* sin(Rad(A))) * 100) / 100)+K);
        // endpoint 2 on plane 2:
        x2 = ceil((L2* sin(Rad(B)) + L1) * 100) / 100;
        y2 = ceil((L2* cos(Rad(B))) * 100) / 100;
        //conversion from planes:
        Ih = (x1 / L2);
        Jh = (1);
        // Z3
        z3 = ceil((x2* sin(Rad(A))) * 100) / 100;
        // printing
        x3 = (((Ih * x2)  * 100) / 100);
        y3 = (((Jh * y2)  * 100) / 100);
        *vx = x3;
        *vy = y3;
        *vz = z3;
}

float HTM::floatmap(float x, float in_min, float in_max, float out_min, float out_max){
      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void HTM::PTMRead(int P1,int P2,int P3,int* A1, int*A2, int*A3, int*A4){
    float angle1 = 0;
    float angle2 = 0;
    float angle3 = 0;
    float angle4 = 0;

    // read the input on analog pins:
    int analogValue1 = analogRead(P1);
    int analogValue2 = analogRead(P2);
    int analogValue3 = analogRead(P3);
    int analogValue4 = analogRead(P4);

    // Rescale to potentiometer's voltage (from 0V to 3.3V):
    angle1 = floatmap(analogValue1, 0, 4095, 0, 180);
    angle2 = floatmap(analogValue2, 0, 4095, 0, 180);
    angle3 = floatmap(analogValue3, 0, 4095, 0, 180);
    angle4 = floatmap(analogValue4, 0, 4095, 0, 180);

    *A1 = angle1;
    *A2 = angle2;
    *A3 = angle3;
    *A4 = angle4;

}

