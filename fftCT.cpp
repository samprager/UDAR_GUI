//*******Written by Samuel M. Prager*********
// University of Southern California 2015
//
// **************fftCT.cpp**************


#include "fftCT.h"
using namespace std;


// ************** fftCT_c2() **************
// Computes convolution of two complex sequences
// using radix 2 implementations of Cooley-Turkey
// based FFT and iFFT algorithms and reverse binary
// indexing. Twiddle factor, w, is calculated
// using both sin() and cos().
// Accepts length of complex sequence, nn as input
// and generates test data arrays of length 2*nn
// with real parts at even indices and imaginary
// parts at odd indices.Sequences are zero padded
// to twice their length rounded up to the
// nearest power of 2 and their fft, product,
// and ifft are used to perform convolution.

void fftCT_v2(double* data, unsigned long nz )
{
	// Compute FFT radix 2 DIT using divide and conquer approach
	// based on Cooley-Turkey Algorithm and Danielson-Lanczos Lemma
	unsigned long n, mmax, m, j, istep, i;
	double wtemp, wr, wpr, wpi, wi, theta;
	double tempr, tempi;
	// reverse-binary reindexing
	n = nz<<1;
	j = 1;
	for (i=1;i<n;i+=2)
	{
		if (j>i)
		{
			swap(data[j-1],data[i-1]);
			swap(data[j],data[i]);
		}
		m = nz;
		while (m>=2 && j>m)
		{
			j-=m;
			m>>=1;
		}
		j +=m;
	}
	// compute FFT using Danielson-Lanczos Lemma
	// Twiddle Factor expansion using both sin and cos
    mmax=2;
    while (n>mmax) {
        istep = mmax<<1;
        theta = -(2*PI/mmax);
        wpr = cos(theta);
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;
        for (m=1; m < mmax; m += 2) {
            for (i=m; i <= n; i += istep) {
                j=i+mmax;
                tempr = wr*data[j-1] - wi*data[j];
                tempi = wr*data[j] + wi*data[j-1];

                data[j-1] = data[i-1] - tempr;
                data[j] = data[i] - tempi;
                data[i-1] += tempr;
                data[i] += tempi;
            }
            wtemp=wr;
            wr = wr*wpr - wi*wpi;
            wi = wi*wpr + wtemp*wpi;
        }
        mmax=istep;
	}
}

void ifftCT_v2(double* data, unsigned long nz )
{
	// inverse fft using divide and conquer approach
	// based on Cooley-Turkey Algorithm and Danielson-Lanczos Lemma

	unsigned long n, mmax, m, j, istep, i;
	double wtemp, wr, wpr, wpi, wi, theta;
	double tempr, tempi;

	// reverse-binary reindexing
	n = nz<<1;
	j = 1;
	for (i=1;i<n;i+=2)
	{
		if (j>i)
		{
			swap(data[j-1],data[i-1]);
			swap(data[j],data[i]);
		}
		m = nz;
		while (m>=2 && j>m)
		{
			j-=m;
			m>>=1;
		}
		j +=m;
	}
	// compute FFT using Danielson-Lanczos Lemma
	// Twiddle Factor expansion using both sin and cos
    mmax=2;
    while (n>mmax) {
        istep = mmax<<1;
        theta = (2*PI/mmax);
        wpr = cos(theta);
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;
        for (m=1; m < mmax; m += 2) {
            for (i=m; i <= n; i += istep) {
                j=i+mmax;
                tempr = wr*data[j-1] - wi*data[j];
                tempi = wr*data[j] + wi*data[j-1];

                data[j-1] = .5*data[i-1] - .5*tempr;
                data[j] = .5*data[i] - .5*tempi;
                data[i-1] =.5*data[i-1] + .5*tempr;
                data[i] = .5*data[i] + .5*tempi;
            }
            wtemp=wr;
            wr = wr*wpr - wi*wpi;
            wi = wi*wpr + wtemp*wpi;
        }
        mmax=istep;
	}
}

// **************fftR_v3()**************
// Computes convolution of two complex sequences
// using Recursive radix 2 DIT implementations of
// Cooley-Turkey based FFT and iFFT algorithms.
// Twiddle factor, w, is calculated using only sin().
// Accepts length of complex sequence, nn as input
// and generates test data arrays of length 2*nn
// with real parts at even indices and imaginary
// parts at odd indices.Sequences are zero padded
// to twice their length rounded up to the
// nearest power of 2 and their fft, product,
// and ifft are used to perform convolution.

void fftR_v3(double *data, unsigned long nz)
{
    // Recursive Cooley–Tukey DIT FFT
    if (nz<=1) return;

    double wtemp, wr, wpr, wpi, wi, theta;
    double tempr, tempi;
    double even[nz];
    double odd[nz];
    unsigned long n,i;
    n=nz>>1;
    for (i=1;i<nz;i+=2)
    {
        even[i-1]=data[2*i-2];
        even[i] = data[2*i-1];
        odd[i-1] = data[2*i];
        odd[i] = data[2*i+1];
    }
    fftR_v3(even,n);
    fftR_v3(odd,n);

    //Twiddle factor expansion calculated using only sin()
    theta = -(2*PI/nz);
    wtemp = sin(.5*theta);
    wpr = -2.0*wtemp*wtemp;
    wpi = sin(theta);
    wr = 1.0;
    wi = 0.0;
    for (i=1;i<nz;i+=2)
    {
        tempr = wr*odd[i-1]-wi*odd[i];
        tempi = wr*odd[i] + wi*odd[i-1];

        data[i-1] = even[i-1]+tempr;
        data[i] = even[i]+tempi;
        data[i-1+nz] = even[i-1]-tempr;
        data[i+nz] = even[i]-tempi;

        wtemp=wr;
        wr += wr*wpr -wi*wpi;
        wi += wi*wpr + wtemp*wpi;
    }
}

void ifftR_v3(double *data, unsigned long nz)
{
    // Recursive Cooley–Tukey DIT FFT
    if (nz<=1) return;

    double wtemp, wr, wpr, wpi, wi, theta;
    double tempr, tempi;
    double even[nz];
    double odd[nz];
    unsigned long n,i;
    n=nz>>1;
    for (i=1;i<nz;i+=2)
    {
        even[i-1]=data[2*i-2];
        even[i] = data[2*i-1];
        odd[i-1] = data[2*i];
        odd[i] = data[2*i+1];
    }
    ifftR_v3(even,n);
    ifftR_v3(odd,n);

    //Twiddle factor expansion calculated using only sin()
    theta = (2*PI/nz);
    wtemp = sin(.5*theta);
    wpr = -2.0*wtemp*wtemp;
    wpi = sin(theta);
    wr = 1.0;
    wi = 0.0;
    for (i=1;i<nz;i+=2)
    {
        tempr = wr*odd[i-1]-wi*odd[i];
        tempi = wr*odd[i] + wi*odd[i-1];

        data[i-1] = .5*even[i-1] + .5*tempr;
        data[i] = .5*even[i] + .5*tempi;
        data[i-1+nz] = .5*even[i-1] - .5*tempr;
        data[i+nz] = .5*even[i] - .5*tempi;

        wtemp=wr;
        wr += wr*wpr - wi*wpi;
        wi += wi*wpr + wtemp*wpi;
    }
}


// ************** fftCT() **************
// Computes convolution of two complex sequences
// using radix 2 implementations of Cooley-Turkey
// based FFT and iFFT algorithms and reverse binary
// indexing. Twiddle factor, w, is calculated using
// only sin().
// Accepts length of complex sequence, nn as input
// and generates test data arrays of length 2*nn
// with real parts at even indices and imaginary
// parts at odd indices.Sequences are zero padded
// to twice their length rounded up to the
// nearest power of 2 and their fft, product,
// and ifft are used to perform convolution.


void fftCT(double* data, unsigned long nz )
{
	// Compute FFT radix 2 DIT using divide and conquer approach
	// based on Cooley-Turkey Algorithm and Danielson-Lanczos Lemma
	unsigned long n, mmax, m, j, istep, i;
	double wtemp, wr, wpr, wpi, wi, theta;
	double tempr, tempi;

	// reverse-binary reindexing
	n = nz<<1;
	j = 1;
	for (i=1;i<n;i+=2)
	{
		if (j>i)
		{
			swap(data[j-1],data[i-1]);
			swap(data[j],data[i]);
		}
		m = nz;
		while (m>=2 && j>m)
		{
			j-=m;
			m>>=1;
		}
		j +=m;
	}
	// compute FFT using Danielson-Lanczos Lemma
	// Twiddle factor expansion calculated using only sin()
    mmax=2;
    while (n>mmax) {
        istep = mmax<<1;
        theta = -(2*PI/mmax);
        wtemp = sin(0.5*theta);
        wpr = -2.0*wtemp*wtemp;
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;
        for (m=1; m < mmax; m += 2) {
            for (i=m; i <= n; i += istep) {
                j=i+mmax;
                tempr = wr*data[j-1] - wi*data[j];
                tempi = wr*data[j] + wi*data[j-1];

                data[j-1] = data[i-1] - tempr;
                data[j] = data[i] - tempi;
                data[i-1] += tempr;
                data[i] += tempi;
            }
            wtemp=wr;
            wr += wr*wpr - wi*wpi;
            wi += wi*wpr + wtemp*wpi;
        }
        mmax=istep;
	}
}

void ifftCT(double* data, unsigned long nz )
{
	// inverse fft using divide and conquer approach
	// based on Cooley-Turkey Algorithm and Danielson-Lanczos Lemma

	unsigned long n, mmax, m, j, istep, i;
	double wtemp, wr, wpr, wpi, wi, theta;
	double tempr, tempi;

	// reverse-binary reindexing
	n = nz<<1;
	j = 1;
	for (i=1;i<n;i+=2)
	{
		if (j>i)
		{
			swap(data[j-1],data[i-1]);
			swap(data[j],data[i]);
		}
		m = nz;
		while (m>=2 && j>m)
		{
			j-=m;
			m>>=1;
		}
		j +=m;
	}
	// compute FFT using Danielson-Lanczos Lemma
	// Twiddle factor expansion calculated using only sin()
    mmax=2;
    while (n>mmax) {
        istep = mmax<<1;
        theta = (2*PI/mmax);
        wtemp = sin(0.5*theta);
        wpr = -2.0*wtemp*wtemp;
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;
        for (m=1; m < mmax; m += 2) {
            for (i=m; i <= n; i += istep) {
                j=i+mmax;
                tempr = wr*data[j-1] - wi*data[j];
                tempi = wr*data[j] + wi*data[j-1];

                data[j-1] = .5*data[i-1] - .5*tempr;
                data[j] = .5*data[i] - .5*tempi;
                data[i-1] =.5*data[i-1] + .5*tempr;
                data[i] = .5*data[i] + .5*tempi;
            }
            wtemp=wr;
            wr += wr*wpr - wi*wpi;
            wi += wi*wpr + wtemp*wpi;
        }
        mmax=istep;
	}
}

unsigned long ceiling2(unsigned long x)
{
	// rounds up to nearest power of two for input up to 64 bits in length
	unsigned long y = x;
 	y--;
	y|=y>>1;
	y|=y>>2;
	y|=y>>4;
	y|=y>>8;
	y|=y>>16;
	y|=y>>32;
	y++;
	return y;
}

void zeroPad(double *data,unsigned long n,unsigned long len)
{
	// zero pads sequence of length n to length len
	unsigned long i;
	for (i=n;i<len;i+=2)
	{
		data[i] = 0;
		data[i+1] = 0;
	}
}

void cProduct(double* x1, double* x2,double* y, unsigned long nz)
{
	// computes product of two complex arrays
	// assumes even indices are real and odd indices are imaginary
	unsigned long i,n;
	n=nz<<1;
	for(i=1;i<n;i+=2)
	{
		y[i-1] = x1[i-1]*x2[i-1]-x1[i]*x2[i];
		y[i] = x1[i]*x2[i-1] + x1[i-1]*x2[i];
	}
}

void conv(double* x1, double* x2,double* y, unsigned long nz)
{
	// convolution using two nested for loops
	unsigned long n,i,j;
	n=nz<<1;
	for (i=1;i<n;i+=2)
	{
		y[i-1]=0;
		y[i]=0;
		for (j=1;j<i;j+=2)
		{
			y[i-1]+=(x1[j-1])*(x2[i-j])-(x1[j])*(x2[i-j+1]);
			y[i]+=(x1[j-1])*(x2[i-j+1])-(x1[j])*(x2[i-j]);
		}
	}
}

void printComplexData(double* data, unsigned long nz, char format)
{
	// prints complex data
	// formats: r: row, c: column, s: separated
	// assumes even indices are real and odd indices are complex
	unsigned long i,n;
	n=nz<<1;
	if (format == 'c')
	{
		cout<<endl;
		for (i=1;i<n;i+=2){
			cout<<data[i-1];
			if (data[i]>=0) cout<<"+";
			cout<<data[i]<<"i"<<endl;
		}
	}
	else if (format == 'r')
	{
		cout<<endl;
		for (i=1;i<n;i+=2){
			cout<<data[i-1];
			if (data[i]>=0) cout<<"+";
			cout<<data[i]<<"i ";
		}
		cout<<endl;
	}
	else if (format == 's')
	{
		cout<<endl;
		cout<<"real: ";
		for (i=1;i<n;i+=2)
			cout<<data[i-1]<<" ";
		cout<<endl;
		cout<<"imag: ";
		for (i=1;i<n;i+=2)
			cout<<data[i]<<" ";
		cout<<endl;
	}
	else
	{
		cout<<endl;
		for (i=1;i<n;i+=2)
			cout<<data[i-1]<<" "<<data[i]<<" ";
		cout<<endl;
	}
}
