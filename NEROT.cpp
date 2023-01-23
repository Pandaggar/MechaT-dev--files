#include "NEROT.h"


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

void Eular::BaseXY(double x,double y,int * c,int * d){
    double Q = QuadXY(x,y);
    double BX = 0;
    double BY = 0; 
    if(Q == 1){
        BX = 0;
        BY = 1;  
    } 
    else if(Q == 2){
        BX = 1;
        BY = 0; 
    }
    else if(Q == 3){
        BX = 0;
        BY = -1; 
    }
    else if(Q == 4){
        BX = -1;
        BY = 0; 
    }
    else{
        BX = 0;
        BY = 0; 
    }
    // std::cout << BX;
    // std::cout << BY;
    *c = BX;
    *d = BY;
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

//int main(){
//    double vx1 = 1.6792;
//    double vy1 = 1;
//    double vz1 = 1;
//
//    double vx2 = sqrt(((vx1*vx1)+(vy1*vy1)));
//    double vy2 = vz1;
//    std::cout << AngleB(vx1,vy1);
//    std::cout << AngleB(vx2,vy2);
//    return 0;
//}

