#include <vector3.h>
#include <quat.h>
#include <math.h>
#include <arduino.h>

#define Rad(deg) (deg*M_PI/180.0)

class MechaLib{
    public:
    Quat getQuat(int16_t k);//knee = 0, hip = 1
    private:
    void EtoQ(int16_t ze,int16_t ye,int16_t xe, int16_t* x, int16_t* y, int16_t* z, int16_t* w);
};


class HVec{
  private:
    float floatmap(float x, float in_min, float in_max, float out_min, float out_max);
  public:
    void HipVec(int16_t L1,int16_t L2,int16_t A,int16_t B, int16_t L, int16_t M, int16_t K, int16_t* vx, int16_t* vy, int16_t* vz);
    void PTMRead(int16_t P1,int16_t* A1,int16_t map);
};

class Nerot{
    public:
    int ABV(int16_t x, int16_t y, int16_t z, int16_t w);
    int QuadXY(int16_t x, int16_t y);
    int ABVS(int16_t x,int16_t y,int16_t z,int16_t w);
    int AngleXY(int16_t x, int16_t y);
};

