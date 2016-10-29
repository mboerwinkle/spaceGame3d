#ifndef QUATOPS_H
#define QUATOPS_H
typedef double quat[4];//w,x,y,z
extern void rotAppend(double* targ, double* append, double* save);
extern void rotVector(double* uVec, quat rot);
extern void rotPoint(int64_t* loc, quat rot);
extern void generateRotationMatrix(quat rot, double *M);
extern double quatLen(quat r);
extern void quatNormalize(quat r);
#endif
