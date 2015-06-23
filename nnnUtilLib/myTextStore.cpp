//
//
//

#include <windows.h>
#include "..\nyanLib\include\\commonMacro.h"

#include "myTextStore.h"


#define _UNICODE


#define numberof(A) (sizeof(A)/sizeof(*(A)))

CMyTextStore::CMyTextStore()
{
	m_lock_count = 0;
	m_lock_flags = false;
	m_ref_count = 0;
}

CMyTextStore::~CMyTextStore()
{
}

//#include <atlcomcli.h>
//#include <atlbase.h>
//#include <atlcom.h>
//#include <STComPtr.h>

//typedef STComPtr <ISTEventSubInfo> ISTEventSubInfoPtr;

// Compare two objects for equivalence
HRESULT CMyTextStore::CreateInstance(CMyTextStore*& o_text_store_cp)
{
	o_text_store_cp = new CMyTextStore();
	return S_OK;
}


 bool IsEqualObject(IUnknown* pFirst,IUnknown* pOther)
 {
 if (pFirst == NULL && pOther == NULL)
 return true; // They are both NULL objects

 if (pFirst == NULL || pOther == NULL)
 return false; // One is NULL the other is not

// STComPtr<IUnknown> punk1;
 //STComPtr<IUnknown> punk2;
 IUnknown* punk1;
 IUnknown* punk2;

 pFirst->QueryInterface(IID_IUnknown, (void**)&punk1);
 pOther->QueryInterface(IID_IUnknown, (void**)&punk2);
 return punk1 == punk2;
 }



STDMETHODIMP_(DWORD) CMyTextStore::AddRef()
{
	m_ref_count++;
	return m_ref_count;
}


//! �Q�ƃJ�E���g�̃f�N�������g����щ��
STDMETHODIMP_(DWORD) CMyTextStore::Release()
{
	m_ref_count--;
	DWORD retval = m_ref_count;
  
	if( retval == 0 )
	{
		delete this;
	}

	return retval;
}


//�v������C���^�[�t�F�C�X��ID���n�����̂ł���ɉ����� 2 �Ԗڂ̈�����ʂ��ĕԂ��Ă��܂��B ������قƂ�ǂ��񑩂̏����ł��B 
//! �C���^�[�t�F�C�X�̖₢���킹
STDMETHODIMP CMyTextStore::QueryInterface(
  REFIID    i_riid,
  LPVOID*   o_interface_cp_p
)
{
	HRESULT   retval = E_FAIL;

    if( IsBadWritePtr(o_interface_cp_p, sizeof(LPVOID)) )
    {
		retval = E_INVALIDARG;
    }
	else
	{
		if( IsEqualIID(i_riid, IID_IUnknown) || IsEqualIID(i_riid, IID_ITextStoreACP) )
		{
			retval = S_OK;
			*o_interface_cp_p = (ITextStoreACP*)this;
			// ���������ꍇ�͎Q�ƃJ�E���g�𑝂₷
			AddRef();
		}
		else
		{
			*o_interface_cp_p = NULL;
			retval = E_NOINTERFACE;
		}
	}
  
	return retval;
}








 
//���O����͉���������̂Ȃ̂�������ɂ����̂ł����A�[�I�Ɍ����΃R�[���o�b�N�̓o�^�ł��B�e�L�X�g�X�g�A�́A�h�L�������g�̕ύX�ȂǃC�x���g�������������ɁA�o�^����Ă���V���N�̑Ή����郁�\�b�h���Ăяo���Ă��Ȃ���΂����܂���BTSF �}�l�[�W���[�Ƀe�L�X�g�X�g�A��o�^����ƁATSF �}�l�[�W���[����Ăяo����܂��B
//1�Ԗڂ̈����͓o�^�������V���N�̃C���^�[�t�F�C�XID�A2�Ԗڂ̈����͓o�^����V���N�ւ̃|�C���^�A3�Ԗڂ̈����̓R�[���o�b�N���ė~�����C�x���g�̎�ނ��w�肷��t���O�ł��B
//�T���v���� tsfapp ���l�A1�̃V���N���������o�^�ł��Ȃ��悤�ɂ��܂��B�o�^�v���̂������V���N�������o�ϐ��� m_sink_cp �ɁA�}�X�N�� m_sink_mask �ɕۑ����Ă����܂��B 
//ReconvTextStore.cpp
//! �V���N�̓o�^���s���B

STDMETHODIMP CMyTextStore::AdviseSink(
  REFIID      i_riid,
  IUnknown*   io_unknown_cp,
  DWORD       i_mask
)
{
  HRESULT   retval    = E_FAIL;
  
  do
  {
    // io_unknown_cp �ɐ������|�C���^���n���ꂽ���`�F�b�N����B
    // �܂��A�o�^�ł���V���N�� ITextStoreACPSink �����B
    if( IsBadReadPtr(io_unknown_cp, sizeof(IUnknown*))
    ||  IsEqualIID(i_riid, IID_ITextStoreACPSink) == false )
    {
//      _RPTF0(_CRT_WARN, "*** Error *** bad ptr or object.\n");
      OutputDebugString("_CRT_WARN, *** Error *** bad ptr or object.\n");
      retval = E_INVALIDARG;
      break;
    }
    
    // ���ɓo�^����Ă���V���N�Ɠ����ꍇ�̓}�X�N�̍X�V���s���B
    if( IsEqualObject(m_sink_cp, io_unknown_cp) )
    {
      m_sink_mask = i_mask;
      retval = S_OK;
    }
    // ���ɃV���N���o�^����Ă���ꍇ�͎��s�B
    else if( m_sink_cp )
    {
//      _RPTF0(_CRT_WARN, "*** Error *** sink already exists.\n");
      OutputDebugString("_RPTF0(_CRT_WARN, *** Error *** sink already exists.\n");
      retval = CONNECT_E_ADVISELIMIT;
    }
    // �V�����o�^
    else
    {
      // ITextStoreACPSink �C���^�[�t�F�C�X���擾����B
      retval = io_unknown_cp->QueryInterface(
                 IID_ITextStoreACPSink,
                 (void**)&m_sink_cp
               );
      // ���������ꍇ�̓}�X�N��ۑ�����B
      if( SUCCEEDED(retval) )
        m_sink_mask = i_mask;
    }
  }
  while( 0 );
  
  return retval;
}



//�V���N�̓o�^���������܂��B1�Ԗڂ̈����͉����������V���N�ւ̃|�C���^�ł��B 
//ReconvTextStore.cpp
//! �V���N�̓o�^����������B
STDMETHODIMP CMyTextStore::UnadviseSink(
  IUnknown*   io_unknown_cp
)
{
  HRESULT     retval      = E_FAIL;
  IUnknown*   unk_id_cp   = NULL;
  
  do
  {
    // �L���ȃ|�C���^���n���ꂽ�����ׂ�B
    if( IsBadReadPtr(io_unknown_cp, sizeof(void*)) )
    {
//      _RPTF0(_CRT_WARN, "*** Error *** io_unknown_cp is bad ptr.\n");
      OutputDebugString("_RPTF0(_CRT_WARN, *** Error *** io_unknown_cp is bad ptr.\n");
      retval = E_INVALIDARG;
      break;
    }
  
    // �o�^����Ă��Ȃ��V���N�̏ꍇ�̓G���[�B
    if( IsEqualObject(io_unknown_cp, m_sink_cp) == false )
    {
//      _RPTF0(_CRT_WARN, "*** Error *** no connection.\n");
      OutputDebugString("_RPTF0(_CRT_WARN, *** Error *** no connection.\n");
      retval = CONNECT_E_NOCONNECTION;
      break;
    }

    // ���
    ENDRELEASE(m_sink_cp);
    m_sink_mask = 0;
    retval = S_OK;
  }
  while( 0 );
  
  return retval;
}




//�h�L�������g�ɑ΂��ă��b�N��v�����A���b�N�����������ꍇ�ɓo�^���Ă���V���N�� OnLockGranted() ���\�b�h�� �Ăԃ��\�b�h�ł��B
//TSF �ł͕����̃e�L�X�g�T�[�r�X���瓯���ɓ��͂�����\��������܂��B�Ⴆ�΃L�[�{�[�h�������Ȃ��特�����͂� �s�����ꍇ�Ȃǂł��B���ɂ��A�A�v���P�[�V�������Ńh�L�������g��ǂݍ��񂾂�ύX�������ꍇ�����Ă���܂��B ���̂悤�ȏꍇ�Ɉ�̃h�L�������g�ɑ΂��Ċe�X���D������ɃA�N�Z�X�ł��Ă��܂��Ă͍���܂��B
//TSF �̍�@�ł͎��g���Ǘ����Ă��Ȃ��h�L�������g�փA�N�Z�X����ɂ͕K�� RequestLock() �Ń��b�N�v�����o���āA �Ăяo���ꂽ OnLockGranted() ���\�b�h�̒��ōs���܂��BOnLockGranted() �𒼖󂷂�Ɓu���b�N���F�߂�ꂽ���v �Ȃ̂ł��̂܂܂ł��ˁB
//���b�N����Ă��Ȃ��󋵂Ńh�L�������g�ɃA�N�Z�X���郁�\�b�h���Ă΂ꂽ�ꍇ�A�e�L�X�g�X�g�A�� TS_E_NOLOCK �G���[��Ԃ��K�v������܂��B
//�Ȃ��ARequestLock() �ɑΉ�����A�����b�N�̗v���Ƃ����̂͂���܂���B�e�L�X�g�X�g�A�� OnLockGranted() ���� ���䂪�Ԃ��ꂽ��h�L�������g�ւ̃A�N�Z�X���I�������Ƃ������ƂŃ��b�N���������܂��B
//���g�̊Ǘ����Ă���h�L�������g�փA�N�Z�X����ꍇ�ɂ͏�L�̍�@�ɏ]�� (OnLockGranted() ���ł̂݃h�L�������g�փA�N�Z�X����)�K�v�͂Ȃ��悤�ł��B

//1�Ԗڂ̈����͓ǎ��p��ǂݏ����̗������s���Ƃ��������b�N�̃^�C�v��\���t���O�ł��B
//2�Ԗڂ̈����̓V���N�� OnLockGranted() ���\�b�h�̖߂�l�̊i�[��ł��B

STDMETHODIMP CMyTextStore::RequestLock(
  DWORD       i_lock_flags,
  HRESULT*    o_session_result_p
)
{
  HRESULT   retval      = E_FAIL;
  LONG      lock_count  = InterlockedIncrement(&m_lock_count);
  
  do
  {
    // �V���N���o�^����Ă��Ȃ��ꍇ�̓G���[
    if( m_sink_cp == NULL )
    {
//      _RPTF0(_CRT_WARN, "*** Error *** m_sink_cp is NULL.\n");
      OutputDebugString("_CRT_WARN, *** Error *** m_sink_cp is NULL.\n");
      retval = E_UNEXPECTED;
      break;
    }
    
    // �L���Ȉ������H
    if( IsBadWritePtr(o_session_result_p, sizeof(HRESULT)) )
    {
//      _RPTF0(_CRT_WARN, "*** Error *** o_session_result_p is bad ptr.\n");
      OutputDebugString("_CRT_WARN, *** Error *** o_session_result_p is bad ptr.\n");
      retval = E_INVALIDARG;
      break;
    }
    
    *o_session_result_p = E_FAIL;

    // ���b�N�Ɏ��s�����ꍇ�B
    if( lock_count != 1 )
    {
//      _RPTF1(_CRT_WARN, "*** Error *** unable to lock. count : %d.\n", lock_count);
      OutputDebugString("_CRT_WARN, *** Error *** unable to lock. count : %d.\n, lock_count");

      // �������b�N��v���B
      if( (i_lock_flags & TS_LF_SYNC) == TS_LF_SYNC )
        *o_session_result_p = TS_E_SYNCHRONOUS;
      else  // �񓯊��v��
        *o_session_result_p = E_NOTIMPL;

      retval = S_OK;  // �߂�l�� S_OK
      break;
    }
    
    // OnLockGranted() ���R�[������B
    m_lock_flags = i_lock_flags;
    try
    {
      *o_session_result_p = m_sink_cp->OnLockGranted(i_lock_flags);
    }
    catch(...)
    {
//      _RPTF0(_CRT_WARN, "*** ERROR *** exception occured.\n");
      OutputDebugString("_CRT_WARN, *** ERROR *** exception occured.\n");
      *o_session_result_p = E_FAIL;
    }
    m_lock_flags = 0;

    retval = S_OK;
  }
  while( 0 );
  
  InterlockedDecrement(&m_lock_count);
  
  return retval;
}






//! �h�L�������g�̃��b�N���s���B���������ꍇ true, ���s�����ꍇ false ��Ԃ��B
bool CMyTextStore::LockDocument(DWORD i_lock_flags)
{
  bool    retval      = false;
  LONG    lock_count  = InterlockedIncrement(&m_lock_count);
  
  if( lock_count == 1 )
  {
    m_lock_flags  = i_lock_flags;
    retval        = true;
  }
  else
  {
    InterlockedDecrement(&m_lock_count);
  }
  
  return retval;
}


//! �h�L�������g�̃��b�N����������B���b�N���ĂȂ��󋵂ŌĂ΂Ȃ����ƁB
bool CMyTextStore::UnlockDocument()
{
  bool    retval      = false;
  
  if( m_lock_flags )
  {
    m_lock_flags = 0;
    retval = true;
    InterlockedDecrement(&m_lock_count);
  }
  
  return retval;
}


//! �h�L�������g�����b�N�����H
bool CMyTextStore::IsLocked(DWORD i_lock_flags)
{
  return (m_lock_flags & i_lock_flags) == i_lock_flags;
}





//! �ϊ���⃊�X�g���擾��������������Z�b�g����B
bool CMyTextStore::SetString(const wchar_t* i_string)
{
  bool    retval      = false;
  
  do
  {
    if( IsBadReadPtr(i_string, sizeof(wchar_t)) )
    {
      //_RPTF0(_CRT_WARN, "*** ERROR *** i_string is bad ptr.\n");
      OutputDebugString("_CRT_WARN, *** ERROR *** i_string is bad ptr.\n");
      break;
    }

    if( LockDocument(TS_LF_READWRITE) == false )
    {
//      _RPTF0(_CRT_WARN, "*** Error *** unable to lock.\n");
      OutputDebugString("_CRT_WARN, *** Error *** unable to lock.\n");
      break;
    }

    TS_TEXTCHANGE text_change = { 0 };
    text_change.acpStart  = 0;
    text_change.acpOldEnd = lstrlen((LPCSTR)m_text);
    text_change.acpNewEnd = lstrlen((LPCSTR)i_string);
    
    lstrcpyn((LPSTR)m_text, (LPCSTR)i_string, numberof(m_text) - 1);
    UnlockDocument();
      
    if( m_sink_cp && (m_sink_mask & TS_AS_TEXT_CHANGE) )
      m_sink_cp->OnTextChange(0, &text_change);

    retval = true;
  }
  while( 0 );
  
  return retval;
}


 
//�h�L�������g�̃X�e�[�^�X��Ԃ����\�b�h�ł��B�X�e�[�^�X�Ƃ͓ǎ��p�⏈�����Ȃǂ̏�Ԃ̂��Ƃł��B ���ɂ������̑I���������邩�ǂ�����Ԃ��Ȃ���΂����܂���B����A�e�L�X�g�T�[�r�X������͂��󂯕t���� �K�v�͂���܂���̂ŁA�ǎ��p�A��̑I�����������Ȃ��A�ƕԂ��܂��B 
//! �h�L�������g�̃X�e�[�^�X���擾����B
STDMETHODIMP CMyTextStore::GetStatus(
  TS_STATUS*  o_document_status_p
)
{
  HRESULT   retval = E_INVALIDARG;
  
  do
  {
    if( IsBadWritePtr(o_document_status_p, sizeof TS_STATUS) )
    {
//      _RPTF0(_CRT_WARN, "*** ERROR *** o_document_status_p is bad ptr.\n");
      OutputDebugString("_CRT_WARN, *** ERROR *** o_document_status_p is bad ptr.\n");
      retval = E_INVALIDARG;
      break;
    }
    
    o_document_status_p->dwDynamicFlags = TS_SD_READONLY;
    // ��̑I�����������Ȃ�
    o_document_status_p->dwStaticFlags = TS_SS_REGIONS;
    
    retval = S_OK;
  }
  while( 0 );

  return retval;
}



//�@�h�L�������g�̑I��͈͂�Ԃ����\�b�h�ł��B �I���ʒu�̕����͊܂݂܂���B�u�����������v�Łu�����v��I������ ����ꍇ�͊J�n�ʒu�� 2 �A�I���ʒu�� 4 �ƂȂ�܂��B
// �@�h�L�������g�ɃA�N�Z�X���郁�\�b�h�Ȃ̂Ń��b�N��ԂłȂ��ꍇ�� TS_E_NOLOCK ��Ԃ��܂��B 
//! �h�L�������g�̑I��͈͂��擾����B
STDMETHODIMP CMyTextStore::GetSelection(
  ULONG               i_index,
  ULONG               i_selection_buffer_length,
  TS_SELECTION_ACP*   o_selections,
  ULONG*              o_fetched_length_p
)
{
  HRESULT   retval = E_INVALIDARG;
  
  do
  {
    if( IsBadWritePtr(o_selections, sizeof TS_SELECTION_ACP)
    ||  IsBadWritePtr(o_fetched_length_p, sizeof(ULONG)) )
    {
//      _RPTF0(_CRT_WARN, "*** ERROR *** invalid parameter.\n");
      OutputDebugString("_CRT_WARN, *** ERROR *** invalid parameter.\n");
      retval = E_INVALIDARG;
      break;
    }
    
    *o_fetched_length_p = 0;
    
    if( IsLocked(TS_LF_READ) == false )
    {
      //_RPTF0(_CRT_WARN, "*** ERROR *** no lock.\n");
      OutputDebugString("_CRT_WARN, *** ERROR *** no lock.\n");
      retval = TS_E_NOLOCK;
      break;
    }
    
    if( i_index != TF_DEFAULT_SELECTION && i_index > 0 )
    {
      //_RPTF0(_CRT_WARN, "*** ERROR *** i_index is not valid.\n");
      OutputDebugString("_CRT_WARN, *** ERROR *** i_index is not valid.\n");
      retval = E_INVALIDARG;
      break;
    }
    
    memset(o_selections, 0, sizeof(o_selections[0]));
    o_selections[0].acpStart = 0;
    if( m_text[0] )
      o_selections[0].acpEnd = lstrlen((LPCSTR)m_text);
    else
      o_selections[0].acpEnd = 0;
    o_selections[0].style.fInterimChar  = FALSE;
    o_selections[0].style.ase           = TS_AE_START;

    *o_fetched_length_p = 1;
    retval = S_OK;
  }
  while( 0 );
  
  return retval;
}

 
//�@�h�L�������g�̎w�肵���͈͂̕������Ԃ����\�b�h�ł��BGetSelection() �Ɠ��l�ɏI���ʒu�̕����͊܂݂܂���B�I���ʒu�� -1 �̏ꍇ�͏I���܂ŁA�Ƃ����Ӗ��ɂȂ�܂��B
//�h�L�������g�ɃA�N�Z�X���郁�\�b�h�Ȃ̂Ń��b�N��ԂłȂ��ꍇ�� TS_E_NOLOCK ��Ԃ��܂��B 
//! �e�L�X�g���擾����B
STDMETHODIMP CMyTextStore::GetText(
  LONG          i_start_index,
  LONG          i_end_index,
  WCHAR*        o_plain_text,
  ULONG         i_plain_text_length,
  ULONG*        o_plain_text_length_p,
  TS_RUNINFO*   o_run_info_p,
  ULONG         i_run_info_length,
  ULONG*        o_run_info_length_p,
  LONG*         o_next_unread_char_pos_p
)
{
  HRESULT   retval = E_INVALIDARG;
  
  do
  {
    if( IsLocked(TS_LF_READ) == false )
    {
      retval = TS_E_NOLOCK;
      break;
    }
    
    ULONG   text_length = lstrlen((LPCSTR)m_text);
    ULONG   copy_length = min(text_length, i_plain_text_length);
    
    // ��������i�[�B�R�s�[��� L'\0' �ŏI����Ă���K�v�͖����B
    if( IsBadWritePtr(o_plain_text, i_plain_text_length * sizeof(wchar_t)) == FALSE )
    {
      memset(o_plain_text, 0, i_plain_text_length * sizeof(wchar_t));
      memcpy(o_plain_text, m_text, copy_length * sizeof(wchar_t));
    }
    
    // �i�[����������̕��������i�[�B
    if( IsBadWritePtr(o_plain_text_length_p, sizeof ULONG) == FALSE )
    {
      *o_plain_text_length_p = copy_length;
    }
    
    // RUNINFO ���i�[�B
    if( IsBadWritePtr(o_run_info_p, sizeof TS_RUNINFO) == FALSE )
    {
      o_run_info_p[0].type   = TS_RT_PLAIN;
      o_run_info_p[0].uCount = text_length;
    }
    
    // RUNINFO ���i�[���������i�[�B
    if( IsBadWritePtr(o_run_info_length_p, sizeof ULONG) == FALSE )
      *o_run_info_length_p = 1;
    
    // ���̕����̈ʒu���i�[�B
    if( IsBadWritePtr(o_next_unread_char_pos_p, sizeof LONG) == FALSE )
      *o_next_unread_char_pos_p = i_start_index + text_length;
    
    retval = S_OK;
  }
  while( 0 );
  
  return retval;
}

 
//�@�h�L�������g�ɑ΂��ăC���T�[�g�܂��͑I��͈͂̕ύX���\���₢���킹�郁�\�b�h�ł��B������������Ă��Ȃ��� ITfFnReconversion �̈ꕔ�̃��\�b�h�����s���Ă��܂��܂��B�h�L�������g�̃X�e�[�^�X�ɂ�炸�A���삪�L�����ǂ�����₢���킹�郁�\�b�h�݂����ł��ˁB 
//! �e�L�X�g�̃C���T�[�g�܂��͑I��͈͂̕ύX���\���₢���킹��B
STDMETHODIMP CMyTextStore::QueryInsert(
  LONG    i_start_index,
  LONG    i_end_index,
  ULONG   i_length,
  LONG*   o_start_index_p,
  LONG*   o_end_index_p
)
{
  HRESULT retval = E_FAIL;

  if( i_start_index < 0
  ||  i_start_index > i_end_index
  ||  i_end_index   > lstrlen((LPCSTR)m_text) )
  {
    retval = E_INVALIDARG;
  }
  else
  {
    if( o_start_index_p )
      *o_start_index_p = i_start_index;
    
    if( o_end_index_p )
      *o_end_index_p   = i_end_index;

    retval = S_OK;
  }
  
  return retval;
}




  STDMETHODIMP CMyTextStore::GetActiveView(
    TsViewCookie*
  )
  {
	  return E_NOTIMPL;
  }

  STDMETHODIMP CMyTextStore::SetSelection(
    ULONG, const TS_SELECTION_ACP*
  )
    {
	  return E_NOTIMPL;
  }

  STDMETHODIMP CMyTextStore::SetText(
    DWORD, LONG, LONG, const WCHAR*, ULONG, TS_TEXTCHANGE*
  )
  {
	  return E_NOTIMPL;
  }

  STDMETHODIMP CMyTextStore::GetFormattedText(
    LONG, LONG, IDataObject**
  )
  {
	  return E_NOTIMPL;
  }

  STDMETHODIMP CMyTextStore::RequestSupportedAttrs(
    DWORD, ULONG, const TS_ATTRID*
  )
  {
	  return E_NOTIMPL;
  }

  STDMETHODIMP CMyTextStore::RequestAttrsAtPosition(
    LONG, ULONG, const TS_ATTRID*, DWORD
  )
  {
	  return E_NOTIMPL;
  }

  STDMETHODIMP CMyTextStore::RetrieveRequestedAttrs(
    ULONG, TS_ATTRVAL*, ULONG*
  )
  {
	  return E_NOTIMPL;
  }

  STDMETHODIMP CMyTextStore::GetEndACP(
    LONG*
  )
  {
	  return E_NOTIMPL;
  }
  STDMETHODIMP CMyTextStore::GetTextExt(
    TsViewCookie, LONG, LONG, RECT*, BOOL*
  )
  {
	  return E_NOTIMPL;
  }

  STDMETHODIMP CMyTextStore::GetScreenExt(
    TsViewCookie, RECT*
  )
  {
	  return E_NOTIMPL;
  }

  STDMETHODIMP CMyTextStore::GetWnd(
    TsViewCookie, HWND*
  )
  {
	  return E_NOTIMPL;
  }

  STDMETHODIMP CMyTextStore::InsertTextAtSelection(
    DWORD, const WCHAR*, ULONG, LONG*, LONG*, TS_TEXTCHANGE*
  )
  {
	  return E_NOTIMPL;
  }

  STDMETHODIMP CMyTextStore::RequestAttrsTransitioningAtPosition(
    LONG, ULONG, const TS_ATTRID*, DWORD
  )
  {
	  return E_NOTIMPL;
  }

  STDMETHODIMP CMyTextStore::FindNextAttrTransition(
    LONG, LONG, ULONG, const TS_ATTRID*, DWORD, LONG*, BOOL*, LONG*
  )
  {
	  return E_NOTIMPL;
  }

  STDMETHODIMP CMyTextStore::GetEmbedded(
    LONG, REFGUID, REFIID, IUnknown**
  )
  {
	  return E_NOTIMPL;
  }

  STDMETHODIMP CMyTextStore::QueryInsertEmbedded(
    const GUID*, const FORMATETC*, BOOL*
  )
  {
	  return E_NOTIMPL;
  }

  STDMETHODIMP CMyTextStore::InsertEmbedded(
    DWORD, LONG, LONG, IDataObject*, TS_TEXTCHANGE*
  )
  {
	  return E_NOTIMPL;
  }

  STDMETHODIMP CMyTextStore::GetACPFromPoint(
    TsViewCookie, const POINT*, DWORD, LONG*
  )
  {
	  return E_NOTIMPL;
  }

  STDMETHODIMP CMyTextStore::InsertEmbeddedAtSelection(
    DWORD, IDataObject*, LONG*, LONG*, TS_TEXTCHANGE*
  )
  {
	  return E_NOTIMPL;
  }





#undef _UNICODE


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
