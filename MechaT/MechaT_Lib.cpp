#include "MechaT_Lib.h"

//htm

void HVec::HipVec(int16_t L1,int16_t L2,int16_t A,int16_t B, int16_t L, int16_t M, int16_t K, int16_t* vx, int16_t* vy, int16_t* vz){
    //LMK is origin values, L1 length of rod 1, L2 length of rod 2, A,B is angles of pot a,b, vx vy and vz are output vector
    int16_t x1 = 0;
    int16_t y1 = 0;
    int16_t z1 = 0;
    int16_t x1r = 0;
    int16_t x3 = 0;
    int16_t y3 = 0;
    int16_t z3 = 0;
    int16_t x2 = 0;
    int16_t y2 = 0;
    int16_t Jh = 0;
    int16_t Ih = 0;

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

float HVec::floatmap(float x, float in_min, float in_max, float out_min, float out_max){
      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void HVec::PTMRead(int16_t P1,int16_t* A1,int16_t map){
    float angle1 = 0;
    // read the input on analog pins:
    int analogValue1 = analogRead(P1);
    // Rescale to potentiometer's voltage (from 0V to 3.3V):
    angle1 = floatmap(analogValue1, 0, 4095, 0, map);
    *A1 = angle1;
}

//nerot

int Nerot::ABV(int16_t x, int16_t y, int16_t z, int16_t w) {
    int16_t B = ((acos(((x*y)+(z*w))/((sqrt((x*x)+(y*y)))*(sqrt((z*z)+(w*w)))))));
    // std::cout << B;
    return B;
}

int Nerot::QuadXY(int16_t x, int16_t y)
{
    int16_t B = 0;

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

int Nerot::ABVS(int16_t x,int16_t y,int16_t z,int16_t w){
    int16_t B = 0;
    int16_t Q1 = QuadXY(x,y);
    int16_t Q2 = QuadXY(z,w);
    if (x!=0 and z!=0 and y!=0 and w!=0){
        int16_t m1 = (y-0)/(x-0);
        int16_t m2 = (w-0)/(z-0);
        B = (atan((abs(((m1-m2)/(1+(m1*m2)))))));
    }
    else{
        B= 0;
    }
    return B;
}

int Nerot::AngleXY(int16_t x, int16_t y){
    Nerot O;
    int16_t BX = O.QuadXY(x,y);
    int16_t B = 0;

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

void MechaLib::EtoQ(int16_t ze,int16_t ye,int16_t xe, int16_t* x, int16_t* y, int16_t* z, int16_t* w){
    Quat Q;
    double c1 = 0;
    double c2 = 0;
    double c3 = 0;
    double s1 = 0;
    double s2 = 0;        
    double s3 = 0;        
    c1 = cos( xe / 2 );
    c2 = cos( ye / 2 );
    c3 = cos( ze / 2 );

    s1 = sin( xe / 2 );
    s2 = sin( ye / 2 );
    s3 = sin( ze / 2 );

double c1c2 = c1*c2;
double s1s2 = s1*s2;
    *w =c1c2*c3 - s1s2*s3;
  	*x =c1c2*s3 + s1s2*c3;
	*y =s1*c2*c3 + c1*s2*s3;
	*z =c1*s2*c3 - s1*c2*s3;
}

Quat MechaLib::getQuat(int16_t k){
    MechaLib mlb;
    MPU6050 imu;
    Nerot rot;
    HVec vec;
    Quat Q;
    int16_t x, y, z, w;
    x = y = z = w = 0;
    int16_t P1,P2,P3;
    int16_t vx1,vy1,vz1,vy2,vx2,vz2;

    int16_t rX, rY, rZ;

    if (k == 1){
        imu.getRotation(&rX,&rY,&rZ);

        vec.PTMRead(39,&P1,270);
        vec.PTMRead(36,&P2,270);

        vec.HipVec(5,5,P1,P2,0,0,0,&vx1,&vy1,&vz1);

        int16_t vx2 = sqrt(((vx1*vx1)+(vy1*vy1)));
        int16_t vy2 = vz1;

        int16_t rZE = rot.AngleXY(vx1,vy1);
        int16_t rXE = rot.AngleXY(vx2,vy2);

        int16_t XE = Rad(rXE);
        int16_t YE =0;
        int16_t ZE = Rad(rZE);


        mlb.EtoQ(1.5708,0,1.5708,&x,&y,&z,&w);

    }
    else if(k == 0){

        vec.PTMRead(39,&P1,270);
        vec.PTMRead(36,&P2,270);
        vec.PTMRead(35,&P3,270);

        vec.HipVec(5,5,P1,P2,0,0,0,&vx1,&vy1,&vz1);

        int16_t vx2 = sqrt(((vx1*vx1)+(vy1*vy1)));
        int16_t vy2 = vz1;

        int16_t rZE = rot.AngleXY(vx1,vy1);
        int16_t rXE = rot.AngleXY(vx2,vy2);

        int16_t XE = rXE+P3;
        int16_t YE =  0;
        int16_t ZE = rZE;

        mlb.EtoQ(ZE,YE,XE,&x,&y,&z,&w);
        
    }

  const int16_t scale = (1.0 / (1 << 14));
  return Quat(0.5,-0.5,0.5,0.5);

}