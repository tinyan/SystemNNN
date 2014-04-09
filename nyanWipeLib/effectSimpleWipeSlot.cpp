//
// effectsimplewipeMove.cpp					///移動タイプの共通クラスひながた。現時点ではshapeのコピーにすぎない
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeSlot.h"

#include "allSimpleWipe.h"


int CEffectSimpleWipeSlot::m_slotKaiten[]=
{
	2,3,5,4,1
};

CEffectSimpleWipeSlot::CEffectSimpleWipeSlot(CAllSimpleWipe* allWipe,int slot,int tateyoko) : CEffectSimpleWipeCommon(allWipe)
{
	m_256OkFlag = TRUE;
	m_slot = slot;
	m_tateyoko = tateyoko;
}


CEffectSimpleWipeSlot::~CEffectSimpleWipeSlot()
{
	End();
}

void CEffectSimpleWipeSlot::End(void)
{
}




void CEffectSimpleWipeSlot::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax, POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	if (m_count >= m_countMax-1)
	{
		int srcX = m_endPoint.x;
		int srcY = m_endPoint.y;
		m_endPic->Blt(0,0,srcX,srcY,screenSizeX,screenSizeY,FALSE);
		return;
	}


	if (m_tateyoko == 0)
	{
		for (int i=0;i<m_slot;i++)
		{
			int sizeX = screenSizeX / m_slot;
			int putX = i * sizeX;

			if (i == m_slot-1)
			{
				sizeX = screenSizeX - sizeX*(m_slot-1);
			}

			int kaiten = m_slotKaiten[i];
			kaiten *= 2;
			kaiten++;

			int dv = m_countMax-1;
			dv -= m_slot;
			dv += i;
			if (dv<1) dv = 1;

			int c = dv - m_count;
			if (c>dv) c = dv;
			if (c<0) c = 0;


			LONGLONG kk = c*c;
			kk *= kaiten;
			kk *= screenSizeY;
			kk /= (dv*dv);
			int k = (int)kk;
			k %= (screenSizeY*2);



			if (i & 1)
			{
				k *= -1;
				k += screenSizeY*2;
				k %= (screenSizeY*2);
			}

			k += screenSizeY;
			k %= (screenSizeY*2);


			int srcX1 = putX + m_startPoint.x;
			int srcY1 = m_startPoint.y;

			int srcX2 = putX + m_endPoint.x;
			int srcY2= m_endPoint.y;


			int putY1 = k - screenSizeY*2;
			int putY2 = k - screenSizeY*2 + screenSizeY;

			int putY3 = putY1 + screenSizeY*2;
			int putY4 = putY2 + screenSizeY*2;

			m_startPic->Blt(putX,putY1,srcX1,srcY1,sizeX,screenSizeY,FALSE);
			m_endPic->Blt(putX,putY2,srcX2,srcY2,sizeX,screenSizeY,FALSE);

			m_startPic->Blt(putX,putY3,srcX1,srcY1,sizeX,screenSizeY,FALSE);
			m_endPic->Blt(putX,putY4,srcX2,srcY2,sizeX,screenSizeY,FALSE);
		}
	}
	else
	{
		for (int j=0;j<m_slot;j++)
		{
			int sizeY = screenSizeY / m_slot;
			int putY = j * sizeY;

			if (j == m_slot-1)
			{
				sizeY = screenSizeY - sizeY*(m_slot-1);
			}

			int kaiten = m_slotKaiten[j];
			kaiten *= 2;
			kaiten++;

			int dv = m_countMax-1;
			dv -= m_slot;
			dv += j;
			if (dv<1) dv = 1;


			int c = dv - m_count;
			if (c>dv) c = dv;
			if (c<0) c = 0;


//			int k1 = (c*c)/dv;

			LONGLONG kk = c*c;
			kk *= kaiten;
			kk *= screenSizeX;
			kk /= (dv*dv);
			int k = (int)kk;
			k %= (screenSizeX*2);


			if (j & 1)
			{
				k *= -1;
				k += screenSizeX*2;
				k %= (screenSizeX*2);
			}

			k += screenSizeX;
			k %= (screenSizeX*2);


			int srcX1 = m_startPoint.x;
			int srcY1 = putY + m_startPoint.y;

			int srcX2 = m_endPoint.x;
			int srcY2 = putY + m_endPoint.y;


			int putX1 = k - screenSizeX*2;
			int putX2 = k - screenSizeX*2 + screenSizeX;

			int putX3 = putX1 + screenSizeX*2;
			int putX4 = putX2 + screenSizeX*2;

			m_startPic->Blt(putX1,putY,srcX1,srcY1,screenSizeX,sizeY,FALSE);
			m_endPic->Blt(putX2,putY,srcX2,srcY2,screenSizeX,sizeY,FALSE);

			m_startPic->Blt(putX3,putY,srcX1,srcY1,screenSizeX,sizeY,FALSE);
			m_endPic->Blt(putX4,putY,srcX2,srcY2,screenSizeX,sizeY,FALSE);
		}
	}



}



/*_*/

