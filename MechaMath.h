#include <math.h>
#include <arduino.h>

#define Rad(deg) (deg*M_PI/180.0)

class HVec{
  private:
    float floatmap(float x, float in_min, float in_max, float out_min, float out_max);
  public:
    void HipVec(double L1,double L2,double A,double B, double L, double M, double K, int* vx, int* vy, int* vz);
    void PTM4Read(int P1,int P2,int P3,int P4,int* A1, int*A2, int*A3, int*A4);
};

class Nerot{
    public:
    int ABV(double x, double y, double z, double w);
    int QuadXY(double x, double y);
    int ABVS(double x,double y,double z,double w);
    void BaseXY(double x,double y,int * c,int * d);
    int AngleXY(double x, double y);
};



