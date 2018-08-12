#include <windows.h>
#include <math.h>

#include "..\nyanlib\include\commonMacro.h"

#include "fft.h"

CFFT::CFFT()
{
	for (int i=0;i<32;i++)
	{
		m_tableFlag[i] = FALSE;
		m_cossinTable[i] = NULL;
	}
}

CFFT::~CFFT()
{
	End();
}

void CFFT::End(void)
{
	for (int i=0;i<32;i++)
	{
		DELETEARRAY(m_cossinTable[i]);
	}
}

void CFFT::Calcu(int n,float* ar,float* ai)
{
	int r = n2r(n);
	if (m_tableFlag[r] == FALSE)
	{
		MakeTable(n);
	}


    int m, mh, i, j, k, irev;
	float wr,wi,xr,xi;

    i = 0;
    for (j = 1; j < n - 1; j++)
	{
        for (k = n >> 1; k > (i ^= k); k >>= 1);

        if (j < i)
		{
            xr = ar[j];
            xi = ai[j];
            ar[j] = ar[i];
            ai[j] = ai[i];
            ar[i] = xr;
            ai[i] = xi;
        }
    }


    for (mh = 1; (m = mh << 1) <= n; mh = m)
	{
        irev = 0;
        for (i = 0; i < n; i += m)
		{
//            wr = cos(theta * irev);
  //          wi = sin(theta * irev);
			wr = m_cossinTable[r][irev*2];
			wi = m_cossinTable[r][irev*2+1];

            for (k = n >> 2; k > (irev ^= k); k >>= 1);

            for (j = i; j < mh + i; j++)
			{
                k = j + mh;
                xr = ar[j] - ar[k];
                xi = ai[j] - ai[k];
                ar[j] += ar[k];
                ai[j] += ai[k];
                ar[k] = wr * xr - wi * xi;
                ai[k] = wr * xi + wi * xr;
            }
        }
    }

	//
	float dv = 1.0f / ((float)n);
	for (i=0;i<n;i++)
	{
		ar[i] *= dv;
		ai[i] *= dv;
	}

}

int CFFT::n2r(int n)
{
	if (n == 256) return 8;
	if (n == 512) return 9;
	if (n == 1024) return 10;

	return 8;
}

void CFFT::MakeTable(int n)
{
	int r = n2r(n);
	if ((r<0) || (r>=32)) return;//error!

	if (m_tableFlag[r]) return;

	m_tableFlag[r] = TRUE;

	m_cossinTable[r] = new float[n*2];
	for (int i=0;i<n;i++)
	{
	//	int k = i % r;
	//	float th = (float)k;
	//	th *= 3.14159f * 2.0f / ((float)r);

	//	int k = i % r;
		float th = (float)i;
		th *= 3.14159f * 2.0f / ((float)n);

		m_cossinTable[r][i*2] = (float)cos(th);
		m_cossinTable[r][i*2+1] = (float)sin(th);
	}
}


/*
ƒŠƒXƒg1.2.1-3. Šî” 2 ‚ÌŽü”g”ŠÔˆø‚« FFT (C³”Å) 
#include <math.h>

void fft(int n, double theta, double ar[], double ai[])
{
    int m, mh, i, j, k, irev;
    double wr, wi, xr, xi;

  //   ---- scrambler ---- 
    i = 0;
    for (j = 1; j < n - 1; j++) {
        for (k = n >> 1; k > (i ^= k); k >>= 1);
        if (j < i) {
            xr = ar[j];
            xi = ai[j];
            ar[j] = ar[i];
            ai[j] = ai[i];
            ar[i] = xr;
            ai[i] = xi;
        }
    }
    for (mh = 1; (m = mh << 1) <= n; mh = m) {
        irev = 0;
        for (i = 0; i < n; i += m) {
            wr = cos(theta * irev);
            wi = sin(theta * irev);
            for (k = n >> 2; k > (irev ^= k); k >>= 1);
            for (j = i; j < mh + i; j++) {
                k = j + mh;
                xr = ar[j] - ar[k];
                xi = ai[j] - ai[k];
                ar[j] += ar[k];
                ai[j] += ai[k];
                ar[k] = wr * xr - wi * xi;
                ai[k] = wr * xi + wi * xr;
            }
        }
    }
}
*/


