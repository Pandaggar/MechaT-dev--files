#include "MechMath.h"

//htm
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

void HTM::PTMRead(int P1,int* A1,int map){
    float angle1 = 0;
    // read the input on analog pins:
    int analogValue1 = analogRead(P1);
    // Rescale to potentiometer's voltage (from 0V to 3.3V):
    angle1 = floatmap(analogValue1, 0, 4095, 0, map);
    *A1 = angle1;
}

//nerot

int Eular::ABV(double x, double y, double z, double w) {
    double B = ((180/3.14159265359)*(acos(((x*y)+(z*w))/((sqrt((x*x)+(y*y)))*(sqrt((z*z)+(w*w)))))));
    // std::cout << B;
    return B;
}

int Eular::QuadXY(double x, double y)
{
    double B = 0;

    if(x>0 and y>0 and y > x){
        B = 7;
    }
    else if (x>0 and y>0 and x > y){
        B = 8;
    }
    else if (x>0 and y<0 and x > abs(y)){ 
        B = 1;
    }
    else if (x>0 and y<0 and x < abs(y)){
        B = 2;
    }
    else if (x<0 and y<0 and abs(x) < abs(y)){
        B = 3;
    }
    else if (x<0 and y<0 and abs(x) > abs(y)){
        B = 4;
    }
    else if (x<0 and y>0 and abs(x) > y){
        B = 5;
    }
    else if (x<0 and y>0 and abs(x) < y){
        B = 6;
    }
    else if (x == 0){
        if(y>0){
            B = 10;
        }
        else if(y<0){
            B = 30;
        }
        else{
            B = 0;
        }
    }
    else if (y == 0){
        if(x>0){
            B = 20;
        }
        else if(x<0){
            B = 40;
        }
        else{
            B = 0;
        }
    }
    else if (abs(y) == abs(x)){
        if(x>0 and y>0){
            B = 15;
        }
        else if(x<0 and y<0){
            B = 35;
        }
        else if(x>0 and y<0){
            B = 25;
        }
        else if (x<0 and y>0){
            B = 45;
        }
        else{
            B = 0;
        }
    }
    return B;
    //std::cout << B;
}

int Eular::ABVS(double x,double y,double z,double w){
    double B = 0;
    double Q1 = QuadXY(x,y);
    double Q2 = QuadXY(z,w);
    if (x!=0 and z!=0 and y!=0 and w!=0){
        double m1 = (y-0)/(x-0);
        double m2 = (w-0)/(z-0);
        B = ((180/3.14159265359)*atan((abs(((m1-m2)/(1+(m1*m2)))))));
    }
    else{
        B= 0;
    }
    return B;
}

int Eular::AngleXY(double x, double y){
    Eular O;
    double BX = O.QuadXY(x,y);
    double B = 0;

  
    if (BX == 1){
        B = abs(45-(O.ABVS(x,y,1,-1)));
    }  
    else if(BX == 2){
        B = (O.ABVS(x,y,1,-1))+45;
    }
    else if(BX == 3){
        B = abs(45-(O.ABVS(x,y,-1,-1)))+90;
    }
    else if(BX == 4){
        B = (O.ABVS(x,y,1,-1))+135;
    }
    else if(BX == 5){
        B = abs(45-(O.ABVS(x,y,-1,1)))+180;
    }
    else if (BX == 6){
        B = (O.ABVS(x,y,-1,1))+225;
    }
    else if (BX == 7){
        B = abs(45-(O.ABVS(x,y,1,1)))+270;
    }
    else if (BX == 8){
        B = O.ABVS(x,y,1,1)+315;
    }
    else if (BX == 10){
        B = 270;
    }
    else if (BX == 20){
        B = 0;
    }
    else if (BX == 30){
        B = 90;
    }
    else if (BX == 40){
        B = 180;
    }
    else if (BX == 15){
        B = 315;
    }
    else if (BX == 25){
        B = 45;
    }
    else if (BX == 35){
        B = 135;
    }
    else if (BX == 45){
        B = 225;
    }
    else{
        B = 0;
    }
    return B;
}


//quat + imu