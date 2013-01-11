//
// effect.cpp
//


#include <windows.h>

#include "..\nyanlib\include\commonmacro.h"
#include "..\nyanlib\include\myGraphics.h"

#include "allEffect.h"

#include "..\nyanlib\include\effect.h"
#include "..\nyanlib\include\picture.h"


char CEffect::m_staticFileNameBuffer[PICTURE_KOSUU_MAX][256];
EFFECT CEffect::m_staticEffect[LAYER_KOSUU_MAX];
char CEffect::m_staticTaihiFileNameBuffer[PICTURE_KOSUU_MAX][256];
EFFECT CEffect::m_staticTaihiEffect[LAYER_KOSUU_MAX];


int CEffect::m_layerKosuuMaxSetup = LAYER_KOSUU_MAX;
int CEffect::m_pictureKosuuMaxSetup = PICTURE_KOSUU_MAX;

CEffect::CEffect()
{
	m_layerKosuuMax =  m_layerKosuuMaxSetup;
	m_pictureKosuuMax =  m_pictureKosuuMaxSetup;

	m_allEffect = new CAllEffect();
}


CEffect::~CEffect()
{
	End();
}


void CEffect::End(void)
{
	ENDDELETECLASS(m_allEffect);
}



void CEffect::SetEye(int n, BOOL md)
{
	m_allEffect->SetEye(n,md);
}


void CEffect::ClearAllEffect(BOOL b)
{
	m_allEffect->ClearAllEffect(b);
}


CPicture* CEffect::GetPicture(int n)
{
	return m_allEffect->GetPicture(n);
}


void CEffect::ClearEffect(int n)
{
	m_allEffect->ClearEffect(n);
}


void CEffect::ClearMakeCGEffect(int n)
{
	m_allEffect->ClearMakeCGEffect(n);
}

void CEffect::SetLayerScript(int n,int d)
{
	m_allEffect->SetLayerScript(n,d);
}


//for buffer->use
BOOL CEffect::ChangeEffectCommandOnly(int num, int effect)
{
	return m_allEffect->ChangeEffectCommandOnly(num,effect);
}




BOOL CEffect::SetEffectScript(int num,int effect,int paraKosuu,int* paraPtr)
{
	return m_allEffect->SetEffectScript(num,effect,paraKosuu,paraPtr);
}


void CEffect::SkipPrint(void)
{
	m_allEffect->SkipPrint();
}


void CEffect::SetNowNoClearFlag(BOOL b)
{
	m_allEffect->SetNowNoClearFlag(b);
}


void CEffect::Print(BOOL bScreenFlag,BOOL bEyeCheckFlag)
{
	m_allEffect->Print(bScreenFlag,bEyeCheckFlag);
}

void CEffect::PrintLayers(int startLayer,int endLayer,BOOL bScreenFlag,BOOL bEyeCheckFlag)
{
	m_allEffect->PrintLayers(startLayer,endLayer,bScreenFlag,bEyeCheckFlag);
}


void CEffect::BeginEffect(void)
{
	m_allEffect->BeginEffect();
}


void CEffect::CountUp(int delta)
{
	m_allEffect->CountUp(delta);
}


void CEffect::Calcu(int cnt)
{
	m_allEffect->Calcu(cnt);
}


void CEffect::CalcuOnly(void)
{
	m_allEffect->CalcuOnly();
}


void CEffect::EndEffect(void)
{
	m_allEffect->EndEffect();
}


void CEffect::SkipAllEffectCount(void)
{
	m_allEffect->SkipAllEffectCount();
}

void CEffect::CalcuZahyo(void)
{
	m_allEffect->CalcuZahyo();
}




void CEffect::CheckNeedAllPrint(void)
{
	m_allEffect->CheckNeedAllPrint();
}

int CEffect::GetParaSize(void)
{
	return m_allEffect->GetParaSize();
}


void* CEffect::GetEffectDataPointer(int n)
{
	return m_allEffect->GetEffectDataPointer(n);
}


void CEffect::SetEffectFileName(int n, LPSTR filename)
{
	m_allEffect->SetEffectFileName(n,filename);
}


void CEffect::SetMakeFileName(int n,LPSTR filename)
{
	m_allEffect->SetMakeFileName(n,filename);
}


LPSTR CEffect::GetEffectFileName(int n)
{
	return m_allEffect->GetEffectFileName(n);
}


LPSTR CEffect::GetMakeFileName(int n)
{
	return m_allEffect->GetMakeFileName(n);
}


void CEffect::PreMakeCG(int n)
{
	m_allEffect->PreMakeCG(n);
}

void CEffect::PostMakeCG(int n)
{
	m_allEffect->PostMakeCG(n);
}

void CEffect::GetMyRect(int layer, int n, RECT* lpRect)
{
	m_allEffect->GetMyRect(layer,n,lpRect);
}


void CEffect::SetMyRect(int layer, int n, RECT* lpRect)
{
	m_allEffect->SetMyRect(layer,n,lpRect);
}


void CEffect::ResetCount(int n)
{
	m_allEffect->ResetCount(n);
}


void CEffect::SetCountToLast(void)
{
	m_allEffect->SetCountToLast();
}

int CEffect::GetEffectEndIsChangeLayer(int effect)
{
	return m_allEffect->GetEffectEndIsChangeLayer(effect);
}


//ŠO•”ŒÄ‚Ño‚µ—p
void CEffect::PrintSimpleWipe(int n, CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax)
{
	m_allEffect->PrintSimpleWipe(n,lpPicStart,lpPicEnd,count,countMax);
}

void CEffect::ExchangeEffectPic(int layer1, int layer2)
{
	m_allEffect->ExchangeEffectPic(layer1,layer2);
}


BOOL CEffect::ResizePicture(int n, int sizeX, int sizeY)
{
	return m_allEffect->ResizePicture(n,sizeX,sizeY);
}



BOOL CEffect::CheckBGLayer(int layer)
{
	return m_allEffect->CheckBGLayer(layer);
}

void CEffect::InitAllParameter(void)
{
	m_allEffect->InitAllParameter();
}

void CEffect::InitParameter(int layer)
{
	m_allEffect->InitParameter(layer);
}

CPicture* CEffect::GetOverrapPic(int n)
{
	return m_allEffect->GetOverrapPic(n);
}


int* CEffect::GetGetBuffer(void)
{
	return m_allEffect->GetGetBuffer();
}


void CEffect::SetOverrapPic(int n, CPicture* lpPic)
{
	m_allEffect->SetOverrapPic(n,lpPic);
}


void CEffect::GetGetScreen(void)
{
	m_allEffect->GetGetScreen();
}

void CEffect::PutGetScreen(void)
{
	m_allEffect->PutGetScreen();
}

void CEffect::SetMouseZahyo(POINT pt)
{
	m_allEffect->SetMouseZahyo(pt);
}

POINT CEffect::GetMouseZahyo(void)
{
	return m_allEffect->GetMouseZahyo();
}

BOOL CEffect::CheckSpeaking(void)
{
	return m_allEffect->CheckSpeaking();
}

void CEffect::SetSpeakingFlag(BOOL flg)
{
	m_allEffect->SetSpeakingFlag(flg);
}


void CEffect::SetEffect(int layer,EFFECT* lpEffect)
{
	m_allEffect->m_effect[layer] = *lpEffect;
}

int CEffect::GetPictureNumber(int layer)
{
	return m_allEffect->m_effect[layer].pic;
}

void CEffect::SetLayerPic(int layer,int pic)
{
	m_allEffect->m_effect[layer].pic = pic;
}


void CEffect::TaihiAllEffect(void)
{
	m_allEffect->TaihiAllEffect();
}

void CEffect::FuqueAllEffect(void)
{
	m_allEffect->FuqueAllEffect();
}

LPSTR CEffect::GetTaihiEffectFileName(int n)
{
	return m_allEffect->GetTaihiEffectFileName(n);
}

void* CEffect::GetTaihiEffectDataPointer(int n)
{
	return m_allEffect->GetTaihiEffectDataPointer(n);
}

void CEffect::TaihiAllEffectToStaticBuffer(void)
{
//OutputDebugString("\nvoid CEffect::TaihiAllEffectToStaticBuffer(void)");

	for (int i=0;i<m_layerKosuuMax;i++)
	{
		EFFECT* lpEffect = (EFFECT*)(m_allEffect->GetEffectDataPointer(i));
		m_staticEffect[i] = *lpEffect;

		CPicture* lpPic = GetPicture(i);
		LPSTR filename = lpPic->GetFileName();
		int ln = strlen(filename);
		if (ln>254) ln = 254;
		memcpy(m_staticFileNameBuffer[i],filename,ln);
		m_staticFileNameBuffer[i][ln] = 0;
		m_staticFileNameBuffer[i][ln+1] = 0;

//OutputDebugString("\nfile=");
//OutputDebugString(filename);

		lpEffect = (EFFECT*)(m_allEffect->GetTaihiEffectDataPointer(i));
		m_staticTaihiEffect[i] = *lpEffect;

		filename = m_allEffect->GetTaihiEffectFileName(i);
		memcpy(m_staticTaihiFileNameBuffer[i],filename,256);

	}
}

void CEffect::FuqueAllEffectByStaticBuffer(void)
{
//OutputDebugString("\nvoid CEffect::FuqueAllEffectByStaticBuffer(void)");
	for (int i=0;i<m_layerKosuuMax;i++)
	{
		EFFECT* lpEffect = (EFFECT*)(m_allEffect->GetEffectDataPointer(i));
		*lpEffect = m_staticEffect[i];

		LPSTR filename = m_allEffect->GetEffectFileName(i);
		memcpy(filename,m_staticFileNameBuffer[i],256);
//OutputDebugString("\nfile=");
//OutputDebugString(filename);

		if ((*filename) != 0) 
		{
			CPicture* pic = GetPicture(i);
//			pic->Flush();
			pic->LoadDWQ(filename);
		}

		lpEffect = (EFFECT*)(m_allEffect->GetTaihiEffectDataPointer(i));
		*lpEffect = m_staticTaihiEffect[i];

		filename = m_allEffect->GetTaihiEffectFileName(i);
		memcpy(filename,m_staticTaihiFileNameBuffer[i],256);
//OutputDebugString("\ntaihifile=");
//OutputDebugString(filename);

	}

	m_allEffect->InitAllParameter();

//	m_allEffect->FuqueAllEffect();
}


void CEffect::ReCreateAllShader(void)
{
	m_allEffect->ReCreateAllShader();
}


/*_*/

