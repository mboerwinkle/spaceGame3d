extern void rotAppend(double* targ, double* append, double* save);
extern void rotVector(double* uVec, quat rot);
extern void generateRotationMatrix(quat rot, double *M);
extern double quatLen(quat r);
extern void quatNormalize(quat r);
