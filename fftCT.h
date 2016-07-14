#ifndef FFTCT_H
#define FFTCT_H

#include <iostream>
#include <cmath>
#include <ctime>

const double PI=3.141592653589793238460;

void fftCT_v2(double* data, unsigned long nz );
void ifftCT_v2(double* data, unsigned long nz );

void fftR_v3(double* data, unsigned long nz );
void ifftR_v3(double* data, unsigned long nz );


void fftCT(double* data, unsigned long nz );
void ifftCT(double* data, unsigned long nz );

void conv(double* x1, double* x2,double* y, unsigned long nz);
void zeroPad(double *data,unsigned long n,unsigned long len);
void cProduct(double* x1, double* x2,double* y, unsigned long nz);
unsigned long ceiling2(unsigned long x);
void printComplexData(double* data, unsigned long nz, char format);

#endif
