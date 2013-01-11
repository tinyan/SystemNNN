//
//
//


#include <windows.h>
#include <stdio.h>

#include <dshow.h>
#include <D3d9.h>
#include <Vmr9.h>

#include "..\nyanLib\include\commonmacro.h"
#include "mydirectShow.h"


CMyDirectShow::CMyDirectShow(HWND hwnd,int message,int useVMR9Flag)
{
	//Co-Init‚Í‚¨‚±‚È‚í‚ê‚Ä‚¢‚é‘O’ñ‚Å

	m_parentHWnd = hwnd;
	m_graphNotify = message;
	m_useVMR9Flag = useVMR9Flag;

	m_volume = 90;
	m_playFlag = FALSE;
	m_completeFlag = FALSE;

	m_mediaSeek = NULL;
	m_basicAudio = NULL;
	m_mediaEventEx = NULL;
	m_mediaControl = NULL;
	m_graphBuilder = NULL;

	m_vmr9 = NULL;
	m_vmrWindowLessControl9 = NULL;
	m_vmrFilterConfig9 = NULL;

	m_videoWindow = NULL;


//	HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,IID_IGraphBuilder, (void **)&m_graphBuilder);
  //  if (FAILED(hr))
    //{
//MessageBox(NULL,"2","error",MB_OK);
        //printf("ERROR - Could not create the Filter Graph Manager.");
        //return;
    //}


/*
	HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,IID_IGraphBuilder, (void **)&m_graphBuilder);
    if (FAILED(hr))
    {
//MessageBox(NULL,"2","error",MB_OK);
        //printf("ERROR - Could not create the Filter Graph Manager.");
        //return;
    }

	CreateVMR9();

*/




	/*
	hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER,IID_IBaseFilter, (void **)&m_pbaseFilter);
    if (FAILED(hr))
    {
        printf("ERROR - Could not create the Grabber.");
        return;
    }

	hr = CoCreateInstance(CLSID_NullRenderer, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&m_pNullFilter);
	sprintf(mes,"[coCreateNullFilter:%x]",hr);
	OutputDebugString(mes);


//	hr = m_pGrabber->QueryInterface(IID_IBaseFilter,(void**)&m_pbaseFilter);
//	sprintf(mes,"[basefilter:%x]",hr);
//	OutputDebugString(mes);
	hr = m_pbaseFilter->QueryInterface(IID_ISampleGrabber,(void**)&m_pGrabber);
	sprintf(mes,"[q:grab:%x]",hr);
	OutputDebugString(mes);


	AM_MEDIA_TYPE mt;
	ZeroMemory(&mt,sizeof(mt));
	mt.majortype = MEDIATYPE_Video;
	mt.subtype = MEDIASUBTYPE_RGB32;
	mt.formattype = FORMAT_VideoInfo;
	hr = m_pGrabber->SetMediaType(&mt);

	sprintf(mes,"[setmediatype:%x]",hr);
	OutputDebugString(mes);



	hr = m_pGraph->AddFilter(m_pbaseFilter,L"Grabber");
	sprintf(mes,"[addbasefilter:%x]",hr);
	OutputDebugString(mes);

	hr = m_pGraph->AddFilter(m_pNullFilter,L"NullRenderer");

	sprintf(mes,"[addnullfilter:%x]",hr);
	OutputDebugString(mes);


	IEnumPins* pEnum = NULL;

	pEnum = NULL;
	m_pbaseFilter->EnumPins(&pEnum);
	pEnum->Reset();
	pEnum->Skip(1);
	IPin* pGrabberOutput;
	hr = pEnum->Next(1, &pGrabberOutput, NULL); 



	pEnum = NULL;
	m_pNullFilter->EnumPins(&pEnum);
	pEnum->Reset();
	IPin* pNullInputPin;
	hr = pEnum->Next(1, &pNullInputPin, NULL);

	hr = m_pGraph->Connect(pGrabberOutput, pNullInputPin);
*/
}

CMyDirectShow::~CMyDirectShow()
{
	End();
}

void CMyDirectShow::End(void)
{
	StopMovie();

	RemoveAllFilter(m_graphBuilder);

	ReleaseRoutine();
//	ReleaseBuilders();
//	ReleaseVMR9();
}



BOOL CMyDirectShow::PlayMovie(LPSTR filename,LONGLONG seekTime)
{
	int ln = strlen(filename);
	memcpy(m_lastFileName,filename,ln+1);

	//‚¿‚á‚ñ‚Æ‚Æ‚Ü‚Á‚Ä‚¢‚é‚©H
	StopMovie();

	RemoveAllFilter(m_graphBuilder);
	ReleaseRoutine();

//////////	ReleaseVMR9();

	HRESULT hr;

	if (m_graphBuilder == NULL)
	{
		hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,IID_IGraphBuilder, (void **)&m_graphBuilder);
		if (FAILED(hr))
		{
//MessageBox(NULL,"PlayMovie-1","error",MB_OK);
			//printf("ERROR - Could not create the Filter Graph Manager.");
			//return;
		}
	}

	if (m_useVMR9Flag)
	{
		CreateVMR9();
		if (m_vmr9 == NULL)
		{
	//MessageBox(NULL,"PlayMovie-2","error",MB_OK);
			return FALSE;
		}
	}
	else
	{
		hr = ((IGraphBuilder*)m_graphBuilder)->QueryInterface(IID_IVideoWindow,(void**)&m_videoWindow);
		if (FAILED(hr))
		{
//MessageBox(NULL,"PlayMovie-2-2","error",MB_OK);

//MessageBox(NULL,"3","error",MB_OK);
		}
	}


    hr = ((IGraphBuilder*)m_graphBuilder)->QueryInterface(IID_IMediaControl, (void **)&m_mediaControl);
	if (FAILED(hr))
	{
//MessageBox(NULL,"PlayMovie-3","error",MB_OK);

//MessageBox(NULL,"3","error",MB_OK);
	}

	hr = ((IGraphBuilder*)m_graphBuilder)->QueryInterface(IID_IMediaEventEx,(void**)&m_mediaEventEx);
	if (FAILED(hr))
	{
//MessageBox(NULL,"PlayMovie-4","error",MB_OK);

//MessageBox(NULL,"5","error",MB_OK);
	}

	hr = ((IGraphBuilder*)m_graphBuilder)->QueryInterface(IID_IBasicAudio, (void **)&m_basicAudio);
	if (FAILED(hr))
	{
//MessageBox(NULL,"PlayMovie-5","error",MB_OK);

//MessageBox(NULL,"6","error",MB_OK);
	}

	hr = ((IGraphBuilder*)m_graphBuilder)->QueryInterface(IID_IBasicAudio, (void **)&m_basicAudio);
	if (FAILED(hr))
	{
//MessageBox(NULL,"PlayMovie-6","error",MB_OK);

//MessageBox(NULL,"7","error",MB_OK);
	}

	hr = ((IGraphBuilder*)m_graphBuilder)->QueryInterface(IID_IMediaSeeking, (void **)&m_mediaSeek);
	if (FAILED(hr))
	{
//MessageBox(NULL,"PlayMovie-7","error",MB_OK);

//MessageBox(NULL,"8","error",MB_OK);
	}

	IBasicAudio* basicAudio = (IBasicAudio*)m_basicAudio;


//	char fname[128] = "ˆÅ‚ÌºˆÙ•·˜^_0614 OP ‚‰æŽ¿”Å.mpg";
	
	unsigned short fname2[256];
	
	MultiByteToWideChar(CP_ACP,0,filename,-1,fname2,256);
	
	hr = ((IGraphBuilder*)m_graphBuilder)->RenderFile(fname2, NULL);
	if (FAILED(hr))
	{
//MessageBox(NULL,"PlayMovie-8","error",MB_OK);

//MessageBox(NULL,"9","error",MB_OK);
	}
	
	if (m_useVMR9Flag)
	{
		RECT srcRect;

		long width;
		long height;
		long aWidth;
		long aHeight;

		hr = ((IVMRWindowlessControl9*)m_vmrWindowLessControl9)->GetNativeVideoSize(&width,&height,&aWidth,&aHeight);
		if (FAILED(hr))
		{
//MessageBox(NULL,"PlayMovie-9","error",MB_OK);

	//MessageBox(NULL,"10","error",MB_OK);
		}

		SetRect(&srcRect,0,0,width,height);

		RECT dstRect;
		SetRect(&dstRect,0,0,800,600);

		hr = ((IVMRWindowlessControl9*)m_vmrWindowLessControl9)->SetVideoPosition(&srcRect,&dstRect);
		if (FAILED(hr))
		{
//MessageBox(NULL,"PlayMovie-10","error",MB_OK);

	//MessageBox(NULL,"11","error",MB_OK);
		}
	}
	else
	{
		((IVideoWindow*)m_videoWindow)->put_Owner((OAHWND)m_parentHWnd);
		((IVideoWindow*)m_videoWindow)->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);

		RECT rc;
		long destWidth;
		long destHeight;

		GetClientRect(m_parentHWnd,&rc);
		destWidth = rc.right;
		destHeight = rc.bottom;
		((IVideoWindow*)m_videoWindow)->SetWindowPosition(0,0,destWidth,destHeight);
		((IVideoWindow*)m_videoWindow)->put_MessageDrain((OAHWND)m_parentHWnd);
	}



	hr = ((IMediaEventEx*)m_mediaEventEx)->SetNotifyWindow((OAHWND)m_parentHWnd,m_graphNotify,0);
	if (FAILED(hr))
	{
//MessageBox(NULL,"PlayMovie-11","error",MB_OK);

//MessageBox(NULL,"12","error",MB_OK);
	}

	basicAudio->put_Volume(m_volume*100-10000);
	m_completeFlag = FALSE;


	if (seekTime > 0)
	{
		hr = ((IMediaSeeking*)m_mediaSeek)->SetPositions(&seekTime,AM_SEEKING_AbsolutePositioning,NULL,AM_SEEKING_NoPositioning);
		if (FAILED(hr))
		{
//MessageBox(NULL,"PlayMovie-12","error",MB_OK);

//MessageBox(NULL,"13","error",MB_OK);
		}
	}
	else
	{
	
	}

	hr = ((IMediaControl*)m_mediaControl)->Run();
	if (FAILED(hr))
	{
//MessageBox(NULL,"PlayMovie-13","error",MB_OK);

//MessageBox(NULL,"14","error",MB_OK);
	}


	//if (hr != S_OK)
	if (0)
	{
		OAFilterState fs;

		int n = 0;
		while (TRUE)
		{
			hr = ((IMediaControl*)m_mediaControl)->GetState(10,&fs);
			if (hr == S_OK) break;
			n++;
			if (n>=10) break;
		}
	}

	m_playFlag = TRUE;

	return TRUE;
}


BOOL CMyDirectShow::StopMovie(void)
{
	if (m_playFlag == FALSE) return FALSE;

	if (m_mediaControl != NULL)
	{
		HRESULT hr = ((IMediaControl*)m_mediaControl)->Stop();	//wait?
		if (hr != S_OK)
		{
			OAFilterState fs;

			int n = 0;
			while (1)
			{
#if defined _DEBUG
				OutputDebugString("*");
#endif
				hr = ((IMediaControl*)m_mediaControl)->GetState(50,&fs);
				if (hr == S_OK) break;
				n++;
				if (n>=10) break;
			}
		}
	}


	RemoveAllFilter(m_graphBuilder);

	ReleaseRoutine();
//	ReleaseBuilders();

	m_playFlag = FALSE;
	return TRUE;
}

void CMyDirectShow::ReleaseBuilders(void)
{
	IVideoWindow* videoWindow = (IVideoWindow*)m_videoWindow;
	IMediaSeeking* mediaSeek = (IMediaSeeking*)m_mediaSeek;
	IBasicAudio* basicAudio = (IBasicAudio*)m_basicAudio;
	IMediaEventEx* mediaEventEx = (IMediaEventEx*)m_mediaEventEx;
	IMediaControl* mediaControl = (IMediaControl*)m_mediaControl;
	IGraphBuilder* graphBuilder = (IGraphBuilder*)m_graphBuilder;

	ENDRELEASE(videoWindow);
	ENDRELEASE(mediaSeek);
	ENDRELEASE(basicAudio);
	ENDRELEASE(mediaEventEx);
	ENDRELEASE(mediaControl);
	ENDRELEASE(graphBuilder);

	m_videoWindow = NULL;
	m_basicAudio = NULL;
	m_mediaEventEx = NULL;
	m_mediaControl = NULL;
	m_graphBuilder = NULL;
	m_mediaSeek = NULL;
}


void CMyDirectShow::ChangeVolume(int vol)
{
	m_volume = vol;



	//if ‚³‚¢‚¹‚¿‚ã‚¤
}



BOOL CMyDirectShow::OnNotify(void)
{
	long evCode;
	long param1;
	long param2;

	BOOL flg = FALSE;
#if defined _DEBUG
OutputDebugString("[OnNotify]");
#endif
	if (m_mediaEventEx == NULL) return TRUE;
	BOOL flg2 = FALSE;

	while(SUCCEEDED(((IMediaEventEx*)m_mediaEventEx)->GetEvent(&evCode,&param1,&param2,0)))
	{
#if defined _DEBUG
OutputDebugString("@");
#endif
		switch (evCode)
		{
		case EC_COMPLETE:
			((IMediaControl*)m_mediaControl)->Stop();
//OutputDebugString("[EC_COMPLETE]");
//			StopMovie();
			m_completeFlag = TRUE;
			flg2 = TRUE;
			break;
		}

		((IMediaEventEx*)m_mediaEventEx)->FreeEventParams(evCode,param1,param2);
	}

	if (flg2)
	{
		RemoveAllFilter(m_graphBuilder);
		ReleaseRoutine();
//		ReleaseBuilders();
	}


	return flg;
}


BOOL CMyDirectShow::OnPaint(HWND hwnd,HDC hdc)
{
	if (m_useVMR9Flag)
	{
		if (m_vmrWindowLessControl9 != NULL)
		{
			((IVMRWindowlessControl9*)m_vmrWindowLessControl9)->RepaintVideo(hwnd,hdc);
		}
	}

	return TRUE;
}

BOOL CMyDirectShow::OnDisplayChanged(void)
{
	if (m_useVMR9Flag)
	{
		if (m_vmrWindowLessControl9 != NULL)
		{
			((IVMRWindowlessControl9*)m_vmrWindowLessControl9)->DisplayModeChanged();
		}
	}

	return TRUE;
}

BOOL CMyDirectShow::OnSize(void)
{
	return TRUE;
}


int CMyDirectShow::CheckCodec(LPSTR filename)
{
	unsigned short fname2[256];

	if (m_useVMR9Flag)
	{
		CreateVMR9();
		if (m_vmr9 == NULL)
		{
	//MessageBox(NULL,"000000!!!!","error",MB_OK);

			ReleaseVMR9();
			return 0;
		}
	}


	MultiByteToWideChar(CP_ACP,0,filename,-1,fname2,256);

	//hr = m_graphBuilder->RenderFile(fname2, NULL);

	IGraphBuilder*	graphBuilder;

	HRESULT hr0 = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,IID_IGraphBuilder, (void **)&graphBuilder);
    if (FAILED(hr0))
    {
		if (m_useVMR9Flag)
		{
			ReleaseVMR9();
		}
//        printf("ERROR - Could not create the Filter Graph Manager.");
        return 0;
    }

	HRESULT hr = graphBuilder->RenderFile(fname2, NULL);


/*

	IMediaControl*	 mediaControl;
	IFilterGraph* filterGraph;

    HRESULT hr2 = graphBuilder->QueryInterface(IID_IMediaControl, (void **)&mediaControl);
    HRESULT hr3 = graphBuilder->QueryInterface(IID_IFilterGraph, (void **)&filterGraph);
//	sprintf(mes,"[control:%x]",hr);
//	OutputDebugString(mes);

	if (mediaControl != NULL)
	{
		mediaControl->Stop();
//		mediaControl->Release();
	}


	IEnumFilters* pEnum = NULL;
	filterGraph->EnumFilters(&pEnum);

	pEnum->Reset();

	int k = 0;
	BOOL flg = TRUE;
	while (flg)
	{
		IBaseFilter* pFilter;
		ULONG kosuu;

		HRESULT hr99 = pEnum->Next(1,&pFilter,&kosuu);
		if (hr99 == VFW_E_ENUM_OUT_OF_SYNC)
		{
			OutputDebugString("[E_OUT]");
			pEnum->Reset();
		}
		else if ((hr99 != S_OK) && (hr99 != S_FALSE))
		{
			if (hr99 == E_INVALIDARG) OutputDebugString("[INVARG]");
			if (hr99 == E_POINTER) OutputDebugString("[E_POINTER]");
//char mes99[256];
//sprintf(mes99,"[enum error %X]",hr99);
//OutputDebugString(mes99);
			break;
		}
		else
		{
			if (hr99 == S_OK)
			{
				OutputDebugString("[S_OK]");
		//		flg = TRUE;
				filterGraph->RemoveFilter(pFilter);
				pFilter->Release();
			}
			if (hr99 == S_FALSE)
			{
				OutputDebugString("[S_FALSE]");
				flg = FALSE;
			}
OutputDebugString("[found]");
		}
		k++;
		if (k>256) break;
	}


	pEnum->Release();

//	IEnumPins* pEnum = NULL;

//	pEnum = NULL;
//	m_pbaseFilter->EnumPins(&pEnum);
//	pEnum->Reset();
//	pEnum->Skip(1);
//	IPin* pGrabberOutput;
//	hr = pEnum->Next(1, &pGrabberOutput, NULL); 


	if (filterGraph != NULL)
	{
		filterGraph->Release();
	}

	if (mediaControl != NULL)
	{
//		mediaControl->Stop();
		mediaControl->Release();
	}


*/


	RemoveAllFilter(graphBuilder);

	if (m_useVMR9Flag)
	{
		ReleaseVMR9();
	}

	if (graphBuilder != NULL)
	{
		graphBuilder->Release();
	}


	if (hr == S_OK) return 3;
	if (hr == VFW_S_AUDIO_NOT_RENDERED) return 2;
	if (hr == VFW_S_VIDEO_NOT_RENDERED) return 1;
	if (hr == VFW_S_PARTIAL_RENDER) return 1;

	if (FAILED(hr)) return 0;

	return 3;
}


/*
void CMyDirectShow::ChangeToFullScreen(HWND hwnd)
{
	m_fullScreenFlag = TRUE;

	if (m_playFlag)
	{
		if (m_videoWindow != NULL)
		{
			HRESULT hr = m_videoWindow->put_Owner((OAHWND)m_parentHWnd);

			hr = m_videoWindow->put_MessageDrain((OAHWND)m_parentHWnd);

			hr = m_videoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
//			sprintf(mes,"[Style:%x]",hr);
//			OutputDebugString(mes);

			hr = m_videoWindow->SetWindowPosition(0,0,800,600);
//			sprintf(mes,"[Pos:%x]",hr);
//			OutputDebugString(mes);

			m_videoWindow->put_FullScreenMode(OAFALSE);
		}
	}
}

void CMyDirectShow::ChangeToWindowScreen(HWND hwnd)
{
	m_fullScreenFlag = FALSE;

	if (m_playFlag)
	{
		if (m_videoWindow != NULL)
		{
			HRESULT hr = m_videoWindow->put_Owner((OAHWND)m_parentHWnd);

			hr = m_videoWindow->put_MessageDrain((OAHWND)m_parentHWnd);

			hr = m_videoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
//			sprintf(mes,"[Style:%x]",hr);
//			OutputDebugString(mes);

			hr = m_videoWindow->SetWindowPosition(0,0,800,600);
//			sprintf(mes,"[Pos:%x]",hr);
//			OutputDebugString(mes);

			m_videoWindow->put_FullScreenMode(OATRUE);
		}
	}
}
*/

//void CMyDirectShow::RemoveAllFilter(IGraphBuilder* graphBuilder)
void CMyDirectShow::RemoveAllFilter(LPVOID graphBuilder0)
{
	if (graphBuilder0 == NULL) return;

	IGraphBuilder* graphBuilder = (IGraphBuilder*)graphBuilder0;

	IMediaControl*	 mediaControl;
	IFilterGraph* filterGraph;

    HRESULT hr2 = graphBuilder->QueryInterface(IID_IMediaControl, (void **)&mediaControl);
    HRESULT hr3 = graphBuilder->QueryInterface(IID_IFilterGraph, (void **)&filterGraph);

	if (mediaControl != NULL)
	{
		mediaControl->Stop();
	}

	IEnumFilters* pEnum = NULL;
	filterGraph->EnumFilters(&pEnum);

	pEnum->Reset();

	int k = 0;
	BOOL flg = TRUE;
	while (flg)
	{
		IBaseFilter* pFilter;
		ULONG kosuu;

		HRESULT hr99 = pEnum->Next(1,&pFilter,&kosuu);
		if (hr99 == VFW_E_ENUM_OUT_OF_SYNC)
		{
//			OutputDebugString("[E_OUT]");
			pEnum->Reset();
		}
		else if ((hr99 != S_OK) && (hr99 != S_FALSE))
		{
#if defined _DEBUG
			if (hr99 == E_INVALIDARG) OutputDebugString("[INVARG]");
			if (hr99 == E_POINTER) OutputDebugString("[E_POINTER]");
#endif
//char mes99[256];
//sprintf(mes99,"[enum error %X]",hr99);
//OutputDebugString(mes99);
			break;
		}
		else
		{
			if (hr99 == S_OK)
			{
//				OutputDebugString("[S_OK]");
		//		flg = TRUE;
				filterGraph->RemoveFilter(pFilter);
				pFilter->Release();
			}
			if (hr99 == S_FALSE)
			{
//				OutputDebugString("[S_FALSE]");
				flg = FALSE;
			}
//OutputDebugString("[found]");
		}
		k++;
		if (k>256) break;
	}


	pEnum->Release();


	if (filterGraph != NULL)
	{
		filterGraph->Release();
	}

	if (mediaControl != NULL)
	{
		mediaControl->Release();
	}
}

BOOL CMyDirectShow::Pause(void)
{
	HRESULT hr0 = ((IMediaSeeking*)m_mediaSeek)->GetCurrentPosition(&m_pauseTime);
	if (FAILED(hr0))
	{
		m_pauseTime = -1;
	}

	StopMovie();
	ReleaseVMR9();

	return TRUE;


//OutputDebugString("[DirectShow::Pause]");
	HRESULT hr = ((IMediaControl*)m_mediaControl)->Pause();
	if (hr != S_OK)
	{
		OAFilterState fs;

		int n = 0;
		while (1)
		{
//			OutputDebugString("+");
			hr = ((IMediaControl*)m_mediaControl)->GetState(50,&fs);
			if (hr == S_OK) break;
			n++;
			if (n>=10) break;
		}
	}

//OutputDebugString("[DirectShow::Stop]");
	hr = ((IMediaControl*)m_mediaControl)->Stop();
	if (hr != S_OK)
	{
		OAFilterState fs;

		int n = 0;
		while (1)
		{
//			OutputDebugString("*");
			hr = ((IMediaControl*)m_mediaControl)->GetState(50,&fs);
			if (hr == S_OK) break;
			n++;
			if (n>=10) break;
		}
	}

	return TRUE;
}

BOOL CMyDirectShow::Resume(void)
{
	//CreateVMR9();
	PlayMovie(m_lastFileName,m_pauseTime);
	return TRUE;

	HRESULT hr = ((IMediaControl*)m_mediaControl)->Run();
	if (hr == S_FALSE)
	{
		OAFilterState fs;

		int n = 0;
		while (1)
		{
//			OutputDebugString("-");
			hr = ((IMediaControl*)m_mediaControl)->GetState(50,&fs);
			if (hr == S_OK) break;
			n++;
			if (n>=10) break;
		}

	}
	return TRUE;
}


void CMyDirectShow::ReleaseVMR9(void)
{
	if (m_vmrWindowLessControl9 != NULL)
	{
		((IVMRWindowlessControl9*)m_vmrWindowLessControl9)->Release();
		m_vmrWindowLessControl9 = NULL;
	}

	if (m_vmr9 != NULL)
	{
		((IBaseFilter*)m_vmr9)->Release();
		m_vmr9 = NULL;
	}
}


void CMyDirectShow::CreateVMR9(void)
{
	HRESULT hr;

	if (m_vmr9 != NULL) return;

	if (m_vmr9 == NULL)
	{
		hr = CoCreateInstance(CLSID_VideoMixingRenderer9, NULL, CLSCTX_INPROC, IID_IBaseFilter, (void**)&m_vmr9);
		if (FAILED(hr))
		{
//MessageBox(NULL,"CreateVMR9-0","error",MB_OK);
			return;
		}
	}

	if (m_graphBuilder != NULL)
	{
		hr = ((IGraphBuilder*)m_graphBuilder)->AddFilter((IBaseFilter*)m_vmr9,L"Video Mixing Renderer 9");
		if (FAILED(hr))
		{
//MessageBox(NULL,"CreateVMR9-1","error",MB_OK);
		}
	}






	if (m_vmrFilterConfig9 == NULL)
	{
		hr = ((IBaseFilter*)m_vmr9)->QueryInterface(IID_IVMRFilterConfig9, (void**)&m_vmrFilterConfig9);
		if (FAILED(hr))
		{
//MessageBox(NULL,"CreateVMR9-3","error",MB_OK);
			return;
		}
	}


	if (m_vmrFilterConfig9 != NULL)
	{
		hr = ((IVMRFilterConfig9*)m_vmrFilterConfig9)->SetRenderingMode(VMRMode_Windowless);
	}

	if (SUCCEEDED(hr))
	{
		((IVMRFilterConfig9*)m_vmrFilterConfig9)->Release();
		m_vmrFilterConfig9 = NULL;

		if (m_vmrWindowLessControl9 == NULL)
		{
			hr = ((IBaseFilter*)m_vmr9)->QueryInterface(IID_IVMRWindowlessControl9, (void**)&m_vmrWindowLessControl9);
		}

		if (SUCCEEDED(hr)) 
		{
			((IVMRWindowlessControl9*)m_vmrWindowLessControl9)->SetVideoClippingWindow(m_parentHWnd);
		}
		else
		{
//MessageBox(NULL,"CreateVMR9-4","error",MB_OK);

		}
	}
	else
	{
//MessageBox(NULL,"CreateVMR9-5","error",MB_OK);

	//	MessageBox(NULL,"error3","3",MB_OK);
	}
}


void CMyDirectShow::ReleaseRoutine(void)
{
	ReleaseBuilders();
	ReleaseVMR9();
}



/*_*/

