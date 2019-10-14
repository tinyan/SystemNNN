//
//
//

#include <windows.h>
#include <locale.h>
#include <INITGUID.H>


#include "..\nyanLib\include\\commonMacro.h"

#include "nameList.h"
#include "myTextStore.h"
#include "myIme.h"

#define numberof(A) (sizeof(A)/sizeof(*(A)))

CMyIME* CMyIME::m_this = NULL;

char m_test[][64]=
{
	"���P",
	"���Q",	
	"���R",
};


CMyIME::CMyIME()
{

	m_opened = FALSE;

	m_bufferMax = 128;
	m_bufferLength = 64;
	m_buffer = new char[m_bufferMax*m_bufferLength];

	m_thread_mgr_cp = NULL;
	m_document_mgr_cp = NULL;
	m_context_cp = NULL;
	m_function_provider_cp = NULL;
	m_reconversion_cp = NULL;
	m_text_store_cp = NULL;
	m_edit_cookie = 0;

	m_this = this;

	HRESULT   hr = E_FAIL;

	do
	{
	  // �X���b�h�}�l�[�W���[�̐���
	  hr = CoCreateInstance(
			 CLSID_TF_ThreadMgr,
			 NULL,
			 CLSCTX_INPROC_SERVER,
			 IID_ITfThreadMgr,
			 (void**)&m_thread_mgr_cp
		   );
	  if( FAILED(hr) )
	  {
//		_RPTF1(_CRT_WARN, "�X���b�h�}�l�[�W���[�̐����Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n", hr );
		OutputDebugString("_CRT_WARN, �X���b�h�}�l�[�W���[�̐����Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n, hr ");
		break;
	  }
  
	  // �h�L�������g�}�l�[�W���[�̐���
	  hr = m_thread_mgr_cp->CreateDocumentMgr(&m_document_mgr_cp);
	  if( FAILED(hr) || m_document_mgr_cp == NULL )
	  {
//		_RPTF1(_CRT_WARN,   "�h�L�������g�}�l�[�W���[�̐����Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n", hr  );
		OutputDebugString("_CRT_WARN,   �h�L�������g�}�l�[�W���[�̐����Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n, hr  ");
		break;
	  }
  
	  // �X���b�h�}�l�[�W���[�̃A�N�e�B�u��
	  TfClientId  client_id = 0;
	  hr = m_thread_mgr_cp->Activate(&client_id);
	  if( FAILED(hr) )
	  {
//		_RPTF1(_CRT_WARN,  "�X���b�h�}�l�[�W���[�̃A�N�e�B�u���Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n", hr		  );
		OutputDebugString("_CRT_WARN,  �X���b�h�}�l�[�W���[�̃A�N�e�B�u���Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n, hr		  ");
		break;
	  }
  
	  // �e�L�X�g�X�g�A�̐���
	  CMyTextStore::CreateInstance(m_text_store_cp);
  
	  // �R���e�L�X�g�̐���
	  hr = m_document_mgr_cp->CreateContext(
			 client_id,
			 0,     // reserved
			 (ITextStoreACP*)m_text_store_cp,
			 &m_context_cp,
			 &m_edit_cookie
		   );
	  if( FAILED(hr) )
	  {
//		_RPTF1(_CRT_WARN,  "�R���e�L�X�g�̐����Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n", hr  );
		OutputDebugString("_CRT_WARN,  �R���e�L�X�g�̐����Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n, hr  ");
		break;
	  }
//hr = E_FAIL;  
//break;

	  // �R���e�L�X�g�� push
	  hr = m_document_mgr_cp->Push(m_context_cp);
	  if( FAILED(hr) )
	  {
//		_RPTF1(_CRT_WARN,   "�R���e�L�X�g�� push �Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n", hr  );
		OutputDebugString("_CRT_WARN,   �R���e�L�X�g�� push �Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n, hr  ");
		break;
	  }
  
	  // �t�@���N�V�����v���o�C�_�[���擾����B
	  hr = m_thread_mgr_cp->GetFunctionProvider(
			 GUID_SYSTEM_FUNCTIONPROVIDER,
			 &m_function_provider_cp
		   );
	  if( FAILED(hr) )
	  {
//		_RPTF1(_CRT_WARN,   "�t�@���N�V�����v���o�C�_�[�̎擾�Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n", hr	  );
		OutputDebugString("_CRT_WARN,   �t�@���N�V�����v���o�C�_�[�̎擾�Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n, hr	  ");
		break;
	  }

	  // ITfFnReconversion �̎擾
	  hr = m_function_provider_cp->GetFunction(
			 GUID_NULL,
			 IID_ITfFnReconversion,
			 (IUnknown**)&m_reconversion_cp
		   );
	  if( FAILED(hr) )
	  {
//		_RPTF1(_CRT_WARN, "ITfFnReconversion �̎擾�Ɏ��s���܂����B�G���[�R�[�h : 0x%08X.\n", hr);
		OutputDebugString("_CRT_WARN ITfFnReconversion �̎擾�Ɏ��s���܂����B�G���[�R�[�h : 0x%08X.\n hr");
		break;
	  }
  
	  // �t�H�[�J�X�擾
	  hr = m_thread_mgr_cp->SetFocus(m_document_mgr_cp);
	  if( FAILED(hr) )
	  {
//		_RPTF1(_CRT_WARN,  "�X���b�h�}�l�[�W���[�� SetFocus() �Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n", hr  );
		OutputDebugString("_CRT_WARN,  �X���b�h�}�l�[�W���[�� SetFocus() �Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n hr  ");
		break;
	  }

	  hr = S_OK;
	}
	while( 0 );

	m_opened = TRUE;

	if( FAILED(hr) )
	  Cleanup();
	SetLastError(hr);

}

CMyIME::~CMyIME()
{
	End();
}

void CMyIME::End(void)
{
	Cleanup();
}

static WCHAR wText[4096];

LPSTR CMyIME::Start(LPSTR text)
{
//	WCHAR wText[4096];

	setlocale( LC_ALL, "jpn" );  
	int retValue = 0;
	mbstowcs_s( (size_t*)&retValue,wText, sizeof( wText ),text,sizeof(wText)/4 );

	m_number = 0;
	m_max = 0;


	if (m_opened)
	{
		EnumCandidates(wText,EnumCandidatesCallback,NULL);
	}
	else
	{
		m_max = 1;
		memcpy(m_buffer,text,strlen(text)+1);

	}

	return m_buffer + m_number * m_bufferLength;
//	return m_test[m_number];
}

LPSTR CMyIME::GetNext(void)
{
	if (m_max > 0)
	{
		m_number++;
		m_number %= m_max;
	}
	return m_buffer + m_number * m_bufferLength;
//	return m_test[m_number];
}


bool CMyIME::EnumCandidatesCallback(
	  int             i_index,
	  int             i_number_of_candidates,
	  const wchar_t*  i_candidate,
	  void*           io_param
	)
{
	return m_this->MyCallback(i_index,i_number_of_candidates,i_candidate,io_param);
}

bool CMyIME::MyCallback(
	  int             i_index,
	  int             i_number_of_candidates,
	  const wchar_t*  i_candidate,
	  void*           io_param
	)
{
	setlocale( LC_ALL, "jpn" );

	int mx = m_this->m_bufferLength;
	int n = m_this->m_max;
	if (n>=m_this->m_bufferMax) return false;

	char* buf = m_buffer + m_bufferLength * m_max;
	*buf=0;
	if (wcstombs_s( NULL,buf, m_bufferLength,i_candidate, m_bufferLength) != 0)
	{
		return true;
	}

	if (CheckKanjiOnly(buf) == FALSE)
	{
		return true;
	}

	m_max++;
#if defined _DEBUG
	OutputDebugString("\x00d\x00alist:");
	OutputDebugStringW(i_candidate);
	OutputDebugString(":");
	OutputDebugString(buf);
#endif

	return true;
}


BOOL CMyIME::CheckKanjiOnly(LPSTR mes)
{
	if (mes == NULL) return FALSE;
	int ln = (int)strlen(mes);
	int n = 0;
	
	while (n<ln)
	{
		int c = ((int)*(mes+n)) & 0xff;
		if (c<0x81) return FALSE;
		if ((c>=0xa0) && (c<0xe0)) return FALSE;
		if (c>=0xf0) return FALSE;	
		if ((ln-n) < 2) return FALSE;

		n+=2;
	}

	return TRUE;
}


#define _UNICODE


bool CMyIME::IsOpened(void)
{
	if (m_opened) return true;
	return false;
}

//�@�I�u�W�F�N�g�̔j�����s���܂��BITfDocumentMgr::Pop() �� ITfThreadMgr::Deactivate() ���Ăяo���Ȃ��� �@�Q�ƃJ�E���g�� 0 �ɂȂ炸�ACOM �I�u�W�F�N�g���������Ȃ����Ƃ�����悤�ł��B 
//! �N���[���A�b�v
bool CMyIME::Cleanup()
{
  // �e�L�X�g�X�g�A�̉��
  ENDRELEASE(m_text_store_cp);
  // ���R���o�[�W�����t�@���N�V�����̉��
  ENDRELEASE(m_reconversion_cp);
  // �t�@���N�V�����v���o�C�_�[�̉��
  ENDRELEASE(m_function_provider_cp);
  // �R���e�L�X�g�̉��
  ENDRELEASE(m_context_cp);
  // �h�L�������g�}�l�[�W���[�̉��
  if( m_document_mgr_cp )
  {
    // �S�ẴR���e�L�X�g���������B
//@@    m_document_mgr_cp->Pop(TF_POPF_ALL);
    m_document_mgr_cp->Pop(0);
    ENDRELEASE(m_document_mgr_cp);
  }
  // �X���b�h�}�l�[�W���[�̉��
  if( m_thread_mgr_cp )
  {
    // �f�A�N�e�B�u�ɂ��Ă���������B
    m_thread_mgr_cp->Deactivate();
    ENDRELEASE(m_thread_mgr_cp);
  }
  
  m_opened = FALSE;

  return true;
}




//�@�X���b�h�}�l�[�W���[�ɓ��̓t�H�[�J�X�����悤�ɗv�����܂��B�v����Ƀe�L�X�g�T�[�r�X������͂��~�����Ƃ������Ƃ� TSF �}�l�[�W���[�ɓ`������̂��Ǝv���܂��BOS �� TIP �ɂ���Ă̓t�H�[�J�X�������Ă����ԂłȂ��� ITfFnReconversion::GetReconversion() �����삵�Ȃ��悤�Ȃ̂ŁA�E�B���h�E���t�H�[�J�X�����������ɃX���b�h�}�l�[�W���[�ɂ��t�H�[�J�X���������Ă��܂��B 
//! �t�H�[�J�X�̎擾
bool CMyIME::SetFocus()
{
  bool    retval = false;
  
  if( IsOpened() )
  {
    // �t�H�[�J�X
    HRESULT hr = m_thread_mgr_cp->SetFocus(m_document_mgr_cp);
    if( FAILED(hr) )
    {
//      _RPTF1(_CRT_WARN,         "�X���b�h�}�l�[�W���[�� SetFocus() �Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n", hr           );
      OutputDebugString("_CRT_WARN,         �X���b�h�}�l�[�W���[�� SetFocus() �Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n, hr           ");
    }
    else
    {
      retval = true;
    }
  }
  
  return retval;
}

//�@�ϊ���⃊�X�g���擾���郁�\�b�h�ł��B�܂��A�擾�Ƃ������񋓂Ƃ������Bi_yomi �̕ϊ����� 3 �Ԗڂɓn���ꂽ�p�����[�^�� 2 �Ԗڂ̃p�����[�^�ɓn���ꂽ�R�[���o�b�N�֐��ɓn���܂��B
//�ĕϊ��ɂ� ITfFnReconversion �����u�h�L�������g�̂��͈̔͂��ĕϊ�����Ƃ�����ǂ͈̔͂��ĕϊ����邩�H�v�Ɩ₢���킹�� QueryRange() ���\�b�h�ƁA���ۂɕϊ���⃊�X�g���擾���� GetReconversion() ���\�b�h���g���܂��B
// �@�������A����� 2 �̃��\�b�h�ɓn���h�L�������g�͈̔͂Ƃ����̂͐��l�^�ł͂���܂���BITfRange �ւ̃|�C���^��n���Ă��Ȃ���΂����Ȃ��̂ł��B���̃|�C���^���擾����̂� ITfContext::GetSelection() ���\�b�h�ɂȂ�܂��BITfContext::GetSelection() ���\�b�h�̓e�L�X�g�X�g�A�� GetSelection() ���\�b�h���Ăяo���A���l�^�ŕԂ��ꂽ�͈͂� ITfRange �I�u�W�F�N�g�ɕϊ����Ă��̃C���^�[�t�F�C�X�ւ̃|�C���^��Ԃ��Ă���܂��B
// �@�����Œ��ӂ��Ȃ���΂����Ȃ��̂� ITfFnReconversion::QueryRange() �� ITfFnReconversion::GetReconversion() �̓e�L�X�g�X�g�A�� RequestLock() ���R�[�����ăh�L�������g�ɃA�N�Z�X���Ă��܂����AITfContext::GetSelection() �� RequestLock() ���Ă΂��ɂ��̂܂� ITextStoreACP::GetSelection() ���\�b�h���Ă�ł��܂��B�ł��̂ŁAGetSelection() ����Ƃ��͎����Ń��b�N�������Ă����Ȃ��Ƃ����܂��񂵁AITfFnReconversion �̃��\�b�h���Ăяo���Ƃ��͋t�Ƀ��b�N���������Ă����Ȃ��Ƃ����܂���B 

//! �ϊ���⃊�X�g��񋓂���B
bool CMyIME::EnumCandidates(
  const wchar_t*            i_yomi,
  EnumCandidatesCallbackP   i_callback,
  void*                     io_param
)
{
  bool                retval          = false;
  HRESULT             hr              = E_FAIL;
  TF_SELECTION        selections[10]  = { 0 };
  ULONG               fetched_count   = 0;
  ITfRange*           range_cp        = NULL;
  BOOL                is_converted    = FALSE;
  ITfCandidateList*   cand_list_cp    = NULL;
  ULONG               cand_length     = 0;
  
  do
  {
    if( IsOpened() == false )
    {
//      _RPTF0(_CRT_WARN, "�������Ɏ��s�����̂� EnumCandidates() ���Ă΂�܂����B\n");
      OutputDebugString("_CRT_WARN, �������Ɏ��s�����̂� EnumCandidates() ���Ă΂�܂����B\n");
      break;
    }
  
    // ��������Z�b�g
    m_text_store_cp->SetString(i_yomi);
    
    // �h�L�������g�̃��b�N���s���B
    if( m_text_store_cp->LockDocument(TS_LF_READ) )
    {
      // �I��͈͂̎擾
      hr = m_context_cp->GetSelection(
             m_edit_cookie,
             TF_DEFAULT_SELECTION,
             numberof(selections),
             selections,
             &fetched_count
           );
      
      // �h�L�������g�̃A�����b�N
      m_text_store_cp->UnlockDocument();
      
      if( FAILED(hr) )
      {
//        _RPTF1(_CRT_WARN, "�I��͈͂̎擾�Ɏ��s���܂����B�G���[�R�[�h : 0x%08X.\n", hr);
        OutputDebugString("_CRT_WARN, �I��͈͂̎擾�Ɏ��s���܂����B�G���[�R�[�h : 0x%08X.\n, hr");
        break;
      }
    }
    

    // �ϊ��͈͂��擾����B
    hr = m_reconversion_cp->QueryRange(selections[0].range, &range_cp, &is_converted);
    if( FAILED(hr) || range_cp == NULL )
    {
//      _RPTF1(_CRT_WARN, "�ϊ��͈͂̎擾�Ɏ��s���܂����B�G���[�R�[�h : 0x%08X.\n", hr);
      OutputDebugString("_CRT_WARN, �ϊ��͈͂̎擾�Ɏ��s���܂����B�G���[�R�[�h : 0x%08X.\n, hr");
      break;
    }

    // �ĕϊ����s��
    hr = m_reconversion_cp->GetReconversion(selections[0].range, &cand_list_cp);
    if( FAILED(hr) || cand_list_cp == NULL )
    {
//      _RPTF1(_CRT_WARN, "�ĕϊ��Ɏ��s���܂����B�G���[�R�[�h : 0x%08X.\n", hr);
      OutputDebugString("_CRT_WARN, �ĕϊ��Ɏ��s���܂����B�G���[�R�[�h : 0x%08X.\n, hr");
      break;
    }
    
    // ��␔���擾����B
    hr = cand_list_cp->GetCandidateNum(&cand_length);
    if( FAILED(hr) )
    {
//      _RPTF1(_CRT_WARN, "��␔�̎擾�Ɏ��s���܂����B�G���[�R�[�h : 0x%08X.\n", hr);
      OutputDebugString("_CRT_WARN, ��␔�̎擾�Ɏ��s���܂����B�G���[�R�[�h : 0x%08X.\n, hr");
      break;
    }
    
    // ����߂�l�ɃZ�b�g����B
    for(ULONG i = 0; i < cand_length; i++)
    {
      ITfCandidateString*   string_cp = NULL;
      BSTR                  bstr      = NULL;

      if( SUCCEEDED(cand_list_cp->GetCandidate(i, &string_cp))
      &&  SUCCEEDED(string_cp->GetString(&bstr)) )
      {
			if( i_callback(i, cand_length, bstr, io_param) == false )
          i = cand_length;

        SysFreeString(bstr);
      }
      
      ENDRELEASE(string_cp);
    }
    
    retval = true;
  }
  while( 0 );
  
  // �N���[���A�b�v
  ENDRELEASE(cand_list_cp);
  ENDRELEASE(range_cp);
  for(int i = 0; i < numberof(selections); i++)
  {
    ENDRELEASE(selections[i].range);
  }
  
  return retval;
}

#undef _UNICODE

/*


// mbstowcs�֐��Ń��C�h������֕ϊ�
char    strm[]  = "Test�X�g�����O";
wchar_t strwfm[32];
setlocale( LC_ALL, "Japanese" );  
mbstowcs( strwfm, strm, strlen( strm )+1 );
wprintf( L"%s(������=%d)\n", strwfm, wcslen( strwfm ) );



wcstombs�֐� - ���C�h�����񁨃}���`�o�C�g������



// wcstombs�֐��Ń}���`�o�C�g������֕ϊ�
wchar_t strw[]  = L"Test���Ƃ��";
char    strmfw[32];
setlocale( LC_ALL, "Japanese" );  
wcstombs( strmfw, strw, sizeof( strmfw ) );
printf( "%s(������=%d)\n", strmfw, strlen( strmfw ) );



*/


/*

 TsfReconverter �̎���

�@TSF �֘A�̃I�u�W�F�N�g�̐����A�擾�A���������s���A�ϊ�����񋓂��郁�\�b�h�����N���X�ł��B�I�u�W�F�N�g�̐����A�擾�A�����͑S�ăR���X�g���N�^�ōs���Ă��܂��B���s���Ă���O�͓����Ȃ��̂ŁA�����������ǂ����� IsOpened() ���\�b�h�Ŋm�F���܂��B
 �@�������ɐ��������� EnumCandidates() �ŕϊ���╶������擾���܂��B2 �Ԗڂ̈����Ŏw�肵���R�[���o�b�N�֐��ɗ񋓂��������񂪓n����܂��B
 �@SetFocus() �̓E�B���h�E���t�H�[�J�X���擾�����Ƃ�(WM_SETFOCUS ���b�Z�[�W�������Ƃ�)�ɌĂяo���܂��B 
TsfReconverter.h
   1 : #ifndef __TSF_RECONVERTER_H_INCLUDED__
   2 : #define __TSF_RECONVERTER_H_INCLUDED__
   3 : #include <msctf.h>
   4 : #include <msaatext.h>
   5 : #include <ctffunc.h>
   6 : #include "ReconvTextStore.h"
   7 : 
   8 : 
   9 : //! TsfReconverter::EnumCandidates() �ɓn���R�[���o�b�N�֐�
//  10 : !
//  11 :  *  @param[in]      i_index
//  12 :  *    ���Ԗڂ̌�₩�B
//  13 :  *  @param[in]      i_number_of_candidates
//  14 :  *    ���̃g�[�^����
//  15 :  *  @param[in]      i_candidate
//  16 :  *    ��╶����B�R�[���o�b�N���甲�����當����͉�������B
//  17 :  *  @param[in,out]  io_param
//  18 :  *    EnumCandidates() �ɓn�����p�����[�^�[�B
//  19 :  *
//  20 :  *  @return �񋓂𑱂���ꍇ�� true, ���~����ꍇ�� false ��Ԃ��B
//  21 :  
  22 : typedef bool (*EnumCandidatesCallbackP)(int             i_index,
  23 :                                         int             i_number_of_candidates,
  24 :                                         const wchar_t*  i_candidate,
  25 :                                         void*           io_param
  26 :                                        );
  27 : 
  28 : 
  29 : //! TSF(Text Service Framework) �𗘗p���ĕϊ���⃊�X�g���擾����N���X�B
  30 : class TsfReconverter
  31 : {
  32 :   //===========================================================================
  33 :   // ���J���\�b�h
  34 :   //===========================================================================
  35 : public:
  36 :   //! �R���X�g���N�^
  37 :   TsfReconverter();
  38 :   //! �f�X�g���N�^
  39 :   virtual ~TsfReconverter();
  40 :   
  41 :   //! �N���[���A�b�v
  42 :   bool Cleanup();
  43 :   
  44 :   //! �������ɐ����������ǂ������ׂ�B
  45 :   bool IsOpened();
  46 :   
  47 :   //! �t�H�[�J�X�̎擾�B
  48 :   bool SetFocus();
  49 : 
  50 :   //! �ϊ���⃊�X�g��񋓂���B
  51 :   bool EnumCandidates(
  52 :     const wchar_t*            i_yomi,
  53 :     EnumCandidatesCallbackP   i_callback,
  54 :     void*                     io_param
  55 :   );
  56 :   
  57 :   //===========================================================================
  58 :   // ����J���\�b�h
  59 :   //===========================================================================
  60 : private:
  61 : 
  62 :   //! �R�s�[�R���X�g���N�^�͎g�p�֎~
  63 :   TsfReconverter(const TsfReconverter&);
  64 :   //! ������Z�q�͎g�p�֎~
  65 :   const TsfReconverter& operator=(const TsfReconverter&);
  66 : 
  67 :   //===========================================================================
  68 :   // �����o
  69 :   //===========================================================================
  70 : public:
  71 :   ITfThreadMgr*         m_thread_mgr_cp;
  72 :   ITfDocumentMgr*       m_document_mgr_cp;
  73 :   ITfContext*           m_context_cp;
  74 :   ITfFunctionProvider*  m_function_provider_cp;
  75 :   ReconvTextStore*      m_text_store_cp;
  76 :   ITfFnReconversion*    m_reconversion_cp;
  77 :   TfEditCookie          m_edit_cookie;
  78 : };
  79 : 
  80 : 
  81 : #endif


�R���X�g���N�^
*/

/*


�@�X���b�h�}�l�[�W���[�A�h�L�������g�}�l�[�W���[�A�R���e�L�X�g�A�t�@���N�V�����v���o�C�_�[�A���R���o�[�W�����t�@���N�V�����̐����܂��͎擾�A���������s���Ă��܂��B�e�L�X�g�X�g�A�̓R���e�L�X�g�������Ɏw�肵�Ă��܂�(61�s�ڂŐ����A67�s�ڂŎw��)�B 
TsfReconverter.cpp
   9 : //! �R���X�g���N�^
  10 : TsfReconverter::TsfReconverter()
  11 : : m_thread_mgr_cp(NULL),
  12 :   m_document_mgr_cp(NULL),
  13 :   m_context_cp(NULL),
  14 :   m_function_provider_cp(NULL),
  15 :   m_reconversion_cp(NULL),
  16 :   m_text_store_cp(NULL),
  17 :   m_edit_cookie(0)
  18 : {
  19 :   HRESULT   hr = E_FAIL;
  20 :   
  21 :   do
  22 :   {
  23 :     // �X���b�h�}�l�[�W���[�̐���
  24 :     hr = CoCreateInstance(
  25 :            CLSID_TF_ThreadMgr,
  26 :            NULL,
  27 :            CLSCTX_INPROC_SERVER,
  28 :            IID_ITfThreadMgr,
  29 :            (void**)&m_thread_mgr_cp
  30 :          );
  31 :     if( FAILED(hr) )
  32 :     {
  33 :       _RPTF1(_CRT_WARN,
  34 :              "�X���b�h�}�l�[�W���[�̐����Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n", hr
  35 :             );
  36 :       break;
  37 :     }
  38 :     
  39 :     // �h�L�������g�}�l�[�W���[�̐���
  40 :     hr = m_thread_mgr_cp->CreateDocumentMgr(&m_document_mgr_cp);
  41 :     if( FAILED(hr) || m_document_mgr_cp == NULL )
  42 :     {
  43 :       _RPTF1(_CRT_WARN,
  44 :              "�h�L�������g�}�l�[�W���[�̐����Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n", hr
  45 :             );
  46 :       break;
  47 :     }
  48 :     
  49 :     // �X���b�h�}�l�[�W���[�̃A�N�e�B�u��
  50 :     TfClientId  client_id = 0;
  51 :     hr = m_thread_mgr_cp->Activate(&client_id);
  52 :     if( FAILED(hr) )
  53 :     {
  54 :       _RPTF1(_CRT_WARN,
  55 :              "�X���b�h�}�l�[�W���[�̃A�N�e�B�u���Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n", hr
  56 :             );
  57 :       break;
  58 :     }
  59 :     
  60 :     // �e�L�X�g�X�g�A�̐���
  61 :     ReconvTextStore::CreateInstance(m_text_store_cp);
  62 :     
  63 :     // �R���e�L�X�g�̐���
  64 :     hr = m_document_mgr_cp->CreateContext(
  65 :            client_id,
  66 :            0,     // reserved
  67 :            (ITextStoreACP*)m_text_store_cp,
  68 :            &m_context_cp,
  69 :            &m_edit_cookie
  70 :          );
  71 :     if( FAILED(hr) )
  72 :     {
  73 :       _RPTF1(_CRT_WARN,
  74 :              "�R���e�L�X�g�̐����Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n", hr
  75 :             );
  76 :       break;
  77 :     }
  78 :     
  79 :     // �R���e�L�X�g�� push
  80 :     hr = m_document_mgr_cp->Push(m_context_cp);
  81 :     if( FAILED(hr) )
  82 :     {
  83 :       _RPTF1(_CRT_WARN,
  84 :              "�R���e�L�X�g�� push �Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n", hr
  85 :             );
  86 :       break;
  87 :     }
  88 :     
  89 :     // �t�@���N�V�����v���o�C�_�[���擾����B
  90 :     hr = m_thread_mgr_cp->GetFunctionProvider(
  91 :            GUID_SYSTEM_FUNCTIONPROVIDER,
  92 :            &m_function_provider_cp
  93 :          );
  94 :     if( FAILED(hr) )
  95 :     {
  96 :       _RPTF1(_CRT_WARN,
  97 :              "�t�@���N�V�����v���o�C�_�[�̎擾�Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n", hr
  98 :             );
  99 :       break;
 100 :     }
 101 : 
 102 :     // ITfFnReconversion �̎擾
 103 :     hr = m_function_provider_cp->GetFunction(
 104 :            GUID_NULL,
 105 :            IID_ITfFnReconversion,
 106 :            (IUnknown**)&m_reconversion_cp
 107 :          );
 108 :     if( FAILED(hr) )
 109 :     {
 110 :       _RPTF1(_CRT_WARN, "ITfFnReconversion �̎擾�Ɏ��s���܂����B�G���[�R�[�h : 0x%08X.\n", hr);
 111 :       break;
 112 :     }
 113 :     
 114 :     // �t�H�[�J�X�擾
 115 :     hr = m_thread_mgr_cp->SetFocus(m_document_mgr_cp);
 116 :     if( FAILED(hr) )
 117 :     {
 118 :       _RPTF1(_CRT_WARN,
 119 :              "�X���b�h�}�l�[�W���[�� SetFocus() �Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n", hr
 120 :             );
 121 :       break;
 122 :     }
 123 : 
 124 :     hr = S_OK;
 125 :   }
 126 :   while( 0 );
 127 :   
 128 :   if( FAILED(hr) )
 129 :     Cleanup();
 130 :   SetLastError(hr);
 131 : }

 Cleanup()

�@�I�u�W�F�N�g�̔j�����s���܂��BITfDocumentMgr::Pop() �� ITfThreadMgr::Deactivate() ���Ăяo���Ȃ��� �@�Q�ƃJ�E���g�� 0 �ɂȂ炸�ACOM �I�u�W�F�N�g���������Ȃ����Ƃ�����悤�ł��B 
TsfReconverter.cpp
 147 : //! �N���[���A�b�v
 148 : bool TsfReconverter::Cleanup()
 149 : {
 150 :   // �e�L�X�g�X�g�A�̉��
 151 :   RELEASE(m_text_store_cp);
 152 :   // ���R���o�[�W�����t�@���N�V�����̉��
 153 :   RELEASE(m_reconversion_cp);
 154 :   // �t�@���N�V�����v���o�C�_�[�̉��
 155 :   RELEASE(m_function_provider_cp);
 156 :   // �R���e�L�X�g�̉��
 157 :   RELEASE(m_context_cp);
 158 :   // �h�L�������g�}�l�[�W���[�̉��
 159 :   if( m_document_mgr_cp )
 160 :   {
 161 :     // �S�ẴR���e�L�X�g���������B
 162 :     m_document_mgr_cp->Pop(TF_POPF_ALL);
 163 :     RELEASE(m_document_mgr_cp);
 164 :   }
 165 :   // �X���b�h�}�l�[�W���[�̉��
 166 :   if( m_thread_mgr_cp )
 167 :   {
 168 :     // �f�A�N�e�B�u�ɂ��Ă���������B
 169 :     m_thread_mgr_cp->Deactivate();
 170 :     RELEASE(m_thread_mgr_cp);
 171 :   }
 172 :   
 173 :   return true;
 174 : }



 SetFocus()

�@�X���b�h�}�l�[�W���[�ɓ��̓t�H�[�J�X�����悤�ɗv�����܂��B�v����Ƀe�L�X�g�T�[�r�X������͂��~�����Ƃ������Ƃ� TSF �}�l�[�W���[�ɓ`������̂��Ǝv���܂��BOS �� TIP �ɂ���Ă̓t�H�[�J�X�������Ă����ԂłȂ��� ITfFnReconversion::GetReconversion() �����삵�Ȃ��悤�Ȃ̂ŁA�E�B���h�E���t�H�[�J�X�����������ɃX���b�h�}�l�[�W���[�ɂ��t�H�[�J�X���������Ă��܂��B 
TsfReconverter.cpp
 190 : //! �t�H�[�J�X�̎擾
 191 : bool TsfReconverter::SetFocus()
 192 : {
 193 :   bool    retval = false;
 194 :   
 195 :   if( IsOpened() )
 196 :   {
 197 :     // �t�H�[�J�X
 198 :     HRESULT hr = m_thread_mgr_cp->SetFocus(m_document_mgr_cp);
 199 :     if( FAILED(hr) )
 200 :     {
 201 :       _RPTF1(_CRT_WARN,
 202 :              "�X���b�h�}�l�[�W���[�� SetFocus() �Ɏ��s���܂����B�G���[�R�[�h:0x%08X\n", hr
 203 :             );
 204 :     }
 205 :     else
 206 :     {
 207 :       retval = true;
 208 :     }
 209 :   }
 210 :   
 211 :   return retval;
 212 : }


 EnumCandidates()

�@�ϊ���⃊�X�g���擾���郁�\�b�h�ł��B�܂��A�擾�Ƃ������񋓂Ƃ������Bi_yomi �̕ϊ����� 3 �Ԗڂɓn���ꂽ�p�����[�^�� 2 �Ԗڂ̃p�����[�^�ɓn���ꂽ�R�[���o�b�N�֐��ɓn���܂��B
 �@�ĕϊ��ɂ� ITfFnReconversion �����u�h�L�������g�̂��͈̔͂��ĕϊ�����Ƃ�����ǂ͈̔͂��ĕϊ����邩�H�v�Ɩ₢���킹�� QueryRange() ���\�b�h�ƁA���ۂɕϊ���⃊�X�g���擾���� GetReconversion() ���\�b�h���g���܂��B
 �@�������A����� 2 �̃��\�b�h�ɓn���h�L�������g�͈̔͂Ƃ����̂͐��l�^�ł͂���܂���BITfRange �ւ̃|�C���^��n���Ă��Ȃ���΂����Ȃ��̂ł��B���̃|�C���^���擾����̂� ITfContext::GetSelection() ���\�b�h�ɂȂ�܂��BITfContext::GetSelection() ���\�b�h�̓e�L�X�g�X�g�A�� GetSelection() ���\�b�h���Ăяo���A���l�^�ŕԂ��ꂽ�͈͂� ITfRange �I�u�W�F�N�g�ɕϊ����Ă��̃C���^�[�t�F�C�X�ւ̃|�C���^��Ԃ��Ă���܂��B
 �@�����Œ��ӂ��Ȃ���΂����Ȃ��̂� ITfFnReconversion::QueryRange() �� ITfFnReconversion::GetReconversion() �̓e�L�X�g�X�g�A�� RequestLock() ���R�[�����ăh�L�������g�ɃA�N�Z�X���Ă��܂����AITfContext::GetSelection() �� RequestLock() ���Ă΂��ɂ��̂܂� ITextStoreACP::GetSelection() ���\�b�h���Ă�ł��܂��B�ł��̂ŁAGetSelection() ����Ƃ��͎����Ń��b�N�������Ă����Ȃ��Ƃ����܂��񂵁AITfFnReconversion �̃��\�b�h���Ăяo���Ƃ��͋t�Ƀ��b�N���������Ă����Ȃ��Ƃ����܂���B 
TsfReconverter.cpp
 218 : //! �ϊ���⃊�X�g��񋓂���B
 219 : bool TsfReconverter::EnumCandidates(
 220 :   const wchar_t*            i_yomi,
 221 :   EnumCandidatesCallbackP   i_callback,
 222 :   void*                     io_param
 223 : )
 224 : {
 225 :   bool                retval          = false;
 226 :   HRESULT             hr              = E_FAIL;
 227 :   TF_SELECTION        selections[10]  = { 0 };
 228 :   ULONG               fetched_count   = 0;
 229 :   ITfRange*           range_cp        = NULL;
 230 :   BOOL                is_converted    = FALSE;
 231 :   ITfCandidateList*   cand_list_cp    = NULL;
 232 :   ULONG               cand_length     = 0;
 233 :   
 234 :   do
 235 :   {
 236 :     if( IsOpened() == false )
 237 :     {
 238 :       _RPTF0(_CRT_WARN, "�������Ɏ��s�����̂� EnumCandidates() ���Ă΂�܂����B\n");
 239 :       break;
 240 :     }
 241 :   
 242 :     // ��������Z�b�g
 243 :     m_text_store_cp->SetString(i_yomi);
 244 :     
 245 :     // �h�L�������g�̃��b�N���s���B
 246 :     if( m_text_store_cp->LockDocument(TS_LF_READ) )
 247 :     {
 248 :       // �I��͈͂̎擾
 249 :       hr = m_context_cp->GetSelection(
 250 :              m_edit_cookie,
 251 :              TF_DEFAULT_SELECTION,
 252 :              numberof(selections),
 253 :              selections,
 254 :              &fetched_count
 255 :            );
 256 :       
 257 :       // �h�L�������g�̃A�����b�N
 258 :       m_text_store_cp->UnlockDocument();
 259 :       
 260 :       if( FAILED(hr) )
 261 :       {
 262 :         _RPTF1(_CRT_WARN, "�I��͈͂̎擾�Ɏ��s���܂����B�G���[�R�[�h : 0x%08X.\n", hr);
 263 :         break;
 264 :       }
 265 :     }
 266 :     
 267 :     // �ϊ��͈͂��擾����B
 268 :     hr = m_reconversion_cp->QueryRange(selections[0].range, &range_cp, &is_converted);
 269 :     if( FAILED(hr) || range_cp == NULL )
 270 :     {
 271 :       _RPTF1(_CRT_WARN, "�ϊ��͈͂̎擾�Ɏ��s���܂����B�G���[�R�[�h : 0x%08X.\n", hr);
 272 :       break;
 273 :     }
 274 : 
 275 :     // �ĕϊ����s��
 276 :     hr = m_reconversion_cp->GetReconversion(selections[0].range, &cand_list_cp);
 277 :     if( FAILED(hr) || cand_list_cp == NULL )
 278 :     {
 279 :       _RPTF1(_CRT_WARN, "�ĕϊ��Ɏ��s���܂����B�G���[�R�[�h : 0x%08X.\n", hr);
 280 :       break;
 281 :     }
 282 :     
 283 :     // ��␔���擾����B
 284 :     hr = cand_list_cp->GetCandidateNum(&cand_length);
 285 :     if( FAILED(hr) )
 286 :     {
 287 :       _RPTF1(_CRT_WARN, "��␔�̎擾�Ɏ��s���܂����B�G���[�R�[�h : 0x%08X.\n", hr);
 288 :       break;
 289 :     }
 290 :     
 291 :     // ����߂�l�ɃZ�b�g����B
 292 :     for(ULONG i = 0; i < cand_length; i++)
 293 :     {
 294 :       ITfCandidateString*   string_cp = NULL;
 295 :       BSTR                  bstr      = NULL;
 296 : 
 297 :       if( SUCCEEDED(cand_list_cp->GetCandidate(i, &string_cp))
 298 :       &&  SUCCEEDED(string_cp->GetString(&bstr)) )
 299 :       {
 300 :         if( i_callback(i, cand_length, bstr, io_param) == false )
 301 :           i = cand_length;
 302 : 
 303 :         SysFreeString(bstr);
 304 :       }
 305 :       
 306 :       RELEASE(string_cp);
 307 :     }
 308 :     
 309 :     retval = true;
 310 :   }
 311 :   while( 0 );
 312 :   
 313 :   // �N���[���A�b�v
 314 :   RELEASE(cand_list_cp);
 315 :   RELEASE(range_cp);
 316 :   for(int i = 0; i < numberof(selections); i++)
 317 :   {
 318 :     RELEASE(selections[i].range);
 319 :   }
 320 :   
 321 :   return retval;
 322 : }

 �e�X�g�v���O����

�@UI �̏������������Ⴒ����Ə����Ă��܂��Əœ_���ڂ₯�Ă��܂��̂ŁA�R�}���h���C���Ŏ󂯎���������ɑ΂��� �ϊ����X�g��\������v���O�����ɂ��Ă݂܂����B 
main.cpp
   1 : #include "stdafx.h"
   2 : #include <INITGUID.H>
   3 : #include <msctf.h>
   4 : #include <msaatext.h>
   5 : #include <ctffunc.h>
   6 : #include <stdio.h>
   7 : #include "TsfReconverter.h"
   8 : 
   9 : 
  10 : //=============================================================================
  11 : 
  12 : 
  13 : //! TsfReconverter::EnumCandidates() �ɓn���R�[���o�b�N
  14 : static bool EnumCandidatesCallback(
  15 :   int             i_index,
  16 :   int             i_number_of_candidates,
  17 :   const wchar_t*  i_candidate,
  18 :   void*           io_param
  19 : )
  20 : {
  21 :   wprintf(L"%2d/%2d : %s\n", i_index + 1, i_number_of_candidates, i_candidate);
  22 :   return true;
  23 : }
  24 : 
  25 : 
  26 : //=============================================================================
  27 : 
  28 : 
  29 : //! ���C�����[�`���B
  30 : int wmain(int argc, wchar_t** argv)
  31 : {
  32 :   setlocale(LC_ALL, "Japanese");
  33 :   CoInitialize(NULL);
  34 : 
  35 :   TsfReconverter  reconverter;
  36 :   
  37 :   if( reconverter.IsOpened() )
  38 :   {
  39 :     for(int i = 1; i < argc; i++)
  40 :     {
  41 :       reconverter.EnumCandidates(argv[i], &EnumCandidatesCallback, NULL);
  42 :     }
  43 :   }
  44 : 
  45 :   return 0;
  46 : }


  ���s����
C:\TsfReconverter>tsftest.exe �ւ񂩂�
 1/ 4 : �ϊ�
 2/ 4 : �Ԋ�
 3/ 4 : �ւ񂩂�
 4/ 4 : �w���J��





*/
