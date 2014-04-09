//
// calcuSpeed.cpp
//

#include <windows.h>
//#include <stdio.h>

#include <Math.h>
#include "calcuSpeed.h"



CCalcuSpeed::CCalcuSpeed()
{
}

CCalcuSpeed::~CCalcuSpeed()
{
	End();
}

void CCalcuSpeed::End()
{
}


//
// 0:^
// 1:Q^
// 2:^P
// 3:^_
// 4:^P_


// 5:^_^_^_
// 6:_^_^_^
// 7:^b^b^b
// 8:_b_b_b

//9:^_^_^_3‰ñ
//10:^b^b^b3‰ñ


//’Ç‰Á—\’è
//

//100- ”½“]
//200-random

//
//+30‚Å‰Á‘¬A+60‚ÅŒ¸‘¬ƒ^ƒCƒv‚É‚·‚é‚Ì‚Í‚¢‚¢‚©‚à
//+75‚Å(1-cos)/2
//

//99(mod100) random

//
// static 
//
int CCalcuSpeed::calcu(int count, int countMax, int startData, int endData, int delayCount, int speedType, int kasokuType)
{
	if ((speedType /100) % 2)
	{
		int tmp = endData;
		endData = startData;
		startData = tmp;
	}

	int randomFlag = speedType / 200;

	speedType %= 100;

	kasokuType = speedType / 15;
	speedType %= 15;

	/*
	if (speedType >= 60)
	{
		speedType -= 60;
		kasokuType = 2;
	}

	if (speedType >= 30)
	{
		speedType -= 30;
		kasokuType = 1;
	}
*/


	if (countMax<1) countMax = 1;
	if (count<0) count = 0;
	if (count>countMax) count = countMax;
	if (delayCount<0) delayCount = 0;

	int waveDiv = delayCount;
	if (waveDiv <= 0) waveDiv = 1;
	int waveDiv2 = waveDiv*2;

	int waveCount = count % waveDiv;
	int waveCount2 = count % waveDiv2;


	double c = (double)count;
	double dv = (double)countMax;
	double d = c / dv;

	switch (speedType)
	{
	case 1:
		if (count<delayCount)
		{
			d = 0.0;
		}
		else
		{
			double dv2 = (double)(dv - delayCount);
			if (dv2<1.0) dv2 = 1.0;
			double c2 = (double)(count - delayCount);
			if (c2<0.0) c2 = 0.0;

			d = c2 / dv2;
		}
		break;
	case 2:
		if (count<delayCount)
		{
			double dv2 = (double)delayCount;
			if (dv2<1.0) dv2 = 1.0;
			
			d = (c / dv2);
		}
		else
		{
			d = 1.0;
		}
		break;
	case 3:
		if (count<delayCount)
		{
			double dv2 = (double)delayCount;
			if (dv2<1.0) dv2 = 1.0;
			d = c / dv2;
		}
		else
		{
			double dv2 = (double)(dv - delayCount);
			if (dv2<1.0) dv2 = 1.0;

			double c2 = (double)(dv  - count);
			if (c2<0.0) c2 = 0.0;

			d = c2 / dv2;
		}
		break;
	case 4:
		if (count<delayCount)
		{
			double dv2 = (double)delayCount;
			if (dv2 < 1.0) dv2 = 1.0;

			d = c / dv2;
		}
		else if (count >= (countMax - delayCount))
		{
			double dv2 = (double)delayCount;
			if (dv2 < 1.0) dv2 = 1.0;

			double c2 = (double)(dv  - count);
			if (c2<0.0) c2 = 0.0;

			d = c2 / dv2;
		}
		else
		{
			d = 1.0;
		}
		break;
	case 5:
		dv = (double)waveDiv;

		if (waveCount2 < waveDiv)
		{
			d = (double)waveCount2;
		}
		else
		{
			d = (double)(waveDiv2-waveCount2);
		}
		d /= dv;
		break;
	case 6:
		dv = (double)waveDiv;

		if (waveCount2 < waveDiv)
		{
			d = (double)(waveDiv-waveCount2);
		}
		else
		{
			d = (double)(waveCount2-waveDiv);
		}
		d /= dv;

		break;
	case 7:
		dv = (double)waveDiv;
		d = (double)waveCount;
		d /= dv;
		break;
	case 8:
		dv = (double)(waveDiv);
		d = (double)(waveDiv-waveCount);
		d /= dv;
		break;
	case 9:
		if (count <= waveDiv2 * 2)
		{
			//1 2

			dv = (double)waveDiv;

			if (waveCount2 < waveDiv)
			{
				d = (double)waveCount2;
			}
			else
			{
				d = (double)(waveDiv2-waveCount2);
			}
			d /= dv;

		}
		else
		{
			//last
			int lastWave = countMax - waveDiv2*2;

			int lastDiv = lastWave / 2;
			if (lastDiv <= 0) lastDiv = 1;


			int lastAmari = count - waveDiv2*2; 
			if (lastAmari  <= lastDiv)
			{
				d = (double)lastAmari;
			}
			else
			{
				d = (double)(lastWave-lastAmari);
			}

			dv = (double)(lastWave/2);
			if (dv <= 0.0) dv = 1.0;

			d /= dv;
		}
		break;
	case 10:
		if (count <= waveDiv*2)
		{
			dv = (double)waveDiv;
			d = (double)waveCount;
			d /= dv;
		}
		else
		{
			//last
			int lastWave = countMax - waveDiv*2;
			int lastDiv = lastWave;
			if (lastDiv <= 0) lastDiv = 1;
			int lastAmari = count - waveDiv*2;
			d = (double)lastAmari;
			dv = (double)lastDiv;
			if (dv <= 0.0) dv = 1.0;
			d /= dv;
		}
		break;
	case 11:
	case 12:
	case 0:
	default:
		break;
	}

	if (d<0.0) d = 0.0;
	if (d>1.0) d = 1.0;

	if (kasokuType == 2)
	{
		// ^2

		d = (d*d);
	}
	else if (kasokuType == 4)
	{
		//sqr
		d = sqrt(d);
	}
	else if (kasokuType == 5)
	{
		//(1-cos(th))/2
		d = (1.0-cos(d*3.14159)) * 0.5;
	}

	if (randomFlag)
	{
		double dRnd = (double)(rand() % 10000);
		dRnd *= 0.0001;
		d *= dRnd;
	}

	double dt = (double)(endData - startData);
	dt *= d;
	dt += (double)startData;
	int ans = (int)(dt + 0.5);

//char mes[256];
//sprintf(mes,"%d",ans);
//OutputDebugString(mes);


	return ans;
}




/*_*/

