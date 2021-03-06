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


//! 参照カウントのデクリメントおよび解放
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


//要求するインターフェイスのIDが渡されるのでそれに応じて 2 番目の引数を通じて返してやります。 これもほとんどお約束の処理です。 
//! インターフェイスの問い合わせ
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
			// 成功した場合は参照カウントを増やす
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








 
//名前からは何をするものなのか分かりにくいのですが、端的に言えばコールバックの登録です。テキストストアは、ドキュメントの変更などイベントが発生した時に、登録されているシンクの対応するメソッドを呼び出してやらなければいけません。TSF マネージャーにテキストストアを登録すると、TSF マネージャーから呼び出されます。
//1番目の引数は登録したいシンクのインターフェイスID、2番目の引数は登録するシンクへのポインタ、3番目の引数はコールバックして欲しいイベントの種類を指定するフラグです。
//サンプルの tsfapp 同様、1つのシンクだけしか登録できないようにします。登録要求のあったシンクをメンバ変数の m_sink_cp に、マスクを m_sink_mask に保存しておきます。 
//ReconvTextStore.cpp
//! シンクの登録を行う。

STDMETHODIMP CMyTextStore::AdviseSink(
  REFIID      i_riid,
  IUnknown*   io_unknown_cp,
  DWORD       i_mask
)
{
  HRESULT   retval    = E_FAIL;
  
  do
  {
    // io_unknown_cp に正しいポインタが渡されたかチェックする。
    // また、登録できるシンクは ITextStoreACPSink だけ。
    if( IsBadReadPtr(io_unknown_cp, sizeof(IUnknown*))
    ||  IsEqualIID(i_riid, IID_ITextStoreACPSink) == false )
    {
//      _RPTF0(_CRT_WARN, "*** Error *** bad ptr or object.\n");
      OutputDebugString("_CRT_WARN, *** Error *** bad ptr or object.\n");
      retval = E_INVALIDARG;
      break;
    }
    
    // 既に登録されているシンクと同じ場合はマスクの更新を行う。
    if( IsEqualObject(m_sink_cp, io_unknown_cp) )
    {
      m_sink_mask = i_mask;
      retval = S_OK;
    }
    // 既にシンクが登録されている場合は失敗。
    else if( m_sink_cp )
    {
//      _RPTF0(_CRT_WARN, "*** Error *** sink already exists.\n");
      OutputDebugString("_RPTF0(_CRT_WARN, *** Error *** sink already exists.\n");
      retval = CONNECT_E_ADVISELIMIT;
    }
    // 新しく登録
    else
    {
      // ITextStoreACPSink インターフェイスを取得する。
      retval = io_unknown_cp->QueryInterface(
                 IID_ITextStoreACPSink,
                 (void**)&m_sink_cp
               );
      // 成功した場合はマスクを保存する。
      if( SUCCEEDED(retval) )
        m_sink_mask = i_mask;
    }
  }
  while( 0 );
  
  return retval;
}



//シンクの登録を解除します。1番目の引数は解除したいシンクへのポインタです。 
//ReconvTextStore.cpp
//! シンクの登録を解除する。
STDMETHODIMP CMyTextStore::UnadviseSink(
  IUnknown*   io_unknown_cp
)
{
  HRESULT     retval      = E_FAIL;
  IUnknown*   unk_id_cp   = NULL;
  
  do
  {
    // 有効なポインタが渡されたか調べる。
    if( IsBadReadPtr(io_unknown_cp, sizeof(void*)) )
    {
//      _RPTF0(_CRT_WARN, "*** Error *** io_unknown_cp is bad ptr.\n");
      OutputDebugString("_RPTF0(_CRT_WARN, *** Error *** io_unknown_cp is bad ptr.\n");
      retval = E_INVALIDARG;
      break;
    }
  
    // 登録されていないシンクの場合はエラー。
    if( IsEqualObject(io_unknown_cp, m_sink_cp) == false )
    {
//      _RPTF0(_CRT_WARN, "*** Error *** no connection.\n");
      OutputDebugString("_RPTF0(_CRT_WARN, *** Error *** no connection.\n");
      retval = CONNECT_E_NOCONNECTION;
      break;
    }

    // 解放
    ENDRELEASE(m_sink_cp);
    m_sink_mask = 0;
    retval = S_OK;
  }
  while( 0 );
  
  return retval;
}




//ドキュメントに対してロックを要求し、ロックが成功した場合に登録してあるシンクの OnLockGranted() メソッドを 呼ぶメソッドです。
//TSF では複数のテキストサービスから同時に入力がくる可能性があります。例えばキーボードを押しながら音声入力を 行った場合などです。他にも、アプリケーション側でドキュメントを読み込んだり変更したい場合だってあります。 そのような場合に一つのドキュメントに対して各々が好き勝手にアクセスできてしまっては困ります。
//TSF の作法では自身が管理していないドキュメントへアクセスするには必ず RequestLock() でロック要求を出して、 呼び出された OnLockGranted() メソッドの中で行います。OnLockGranted() を直訳すると「ロックが認められた時」 なのでそのままですね。
//ロックされていない状況でドキュメントにアクセスするメソッドが呼ばれた場合、テキストストアは TS_E_NOLOCK エラーを返す必要があります。
//なお、RequestLock() に対応するアンロックの要求というのはありません。テキストストアは OnLockGranted() から 制御が返されたらドキュメントへのアクセスが終了したということでロックを解除します。
//自身の管理しているドキュメントへアクセスする場合には上記の作法に従う (OnLockGranted() 内でのみドキュメントへアクセスする)必要はないようです。

//1番目の引数は読取専用や読み書きの両方を行うといったロックのタイプを表すフラグです。
//2番目の引数はシンクの OnLockGranted() メソッドの戻り値の格納先です。

STDMETHODIMP CMyTextStore::RequestLock(
  DWORD       i_lock_flags,
  HRESULT*    o_session_result_p
)
{
  HRESULT   retval      = E_FAIL;
  LONG      lock_count  = InterlockedIncrement(&m_lock_count);
  
  do
  {
    // シンクが登録されていない場合はエラー
    if( m_sink_cp == NULL )
    {
//      _RPTF0(_CRT_WARN, "*** Error *** m_sink_cp is NULL.\n");
      OutputDebugString("_CRT_WARN, *** Error *** m_sink_cp is NULL.\n");
      retval = E_UNEXPECTED;
      break;
    }
    
    // 有効な引数か？
    if( IsBadWritePtr(o_session_result_p, sizeof(HRESULT)) )
    {
//      _RPTF0(_CRT_WARN, "*** Error *** o_session_result_p is bad ptr.\n");
      OutputDebugString("_CRT_WARN, *** Error *** o_session_result_p is bad ptr.\n");
      retval = E_INVALIDARG;
      break;
    }
    
    *o_session_result_p = E_FAIL;

    // ロックに失敗した場合。
    if( lock_count != 1 )
    {
//      _RPTF1(_CRT_WARN, "*** Error *** unable to lock. count : %d.\n", lock_count);
      OutputDebugString("_CRT_WARN, *** Error *** unable to lock. count : %d.\n, lock_count");

      // 同期ロックを要求。
      if( (i_lock_flags & TS_LF_SYNC) == TS_LF_SYNC )
        *o_session_result_p = TS_E_SYNCHRONOUS;
      else  // 非同期要求
        *o_session_result_p = E_NOTIMPL;

      retval = S_OK;  // 戻り値は S_OK
      break;
    }
    
    // OnLockGranted() をコールする。
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






//! ドキュメントのロックを行う。成功した場合 true, 失敗した場合 false を返す。
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


//! ドキュメントのロックを解除する。ロックしてない状況で呼ばないこと。
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


//! ドキュメントをロック中か？
bool CMyTextStore::IsLocked(DWORD i_lock_flags)
{
  return (m_lock_flags & i_lock_flags) == i_lock_flags;
}





//! 変換候補リストを取得したい文字列をセットする。
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


 
//ドキュメントのステータスを返すメソッドです。ステータスとは読取専用や処理中などの状態のことです。 他にも複数の選択を許可するかどうかを返さなければいけません。今回、テキストサービスから入力を受け付ける 必要はありませんので、読取専用、一つの選択しか許可しない、と返します。 
//! ドキュメントのステータスを取得する。
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
    // 一つの選択しか許可しない
    o_document_status_p->dwStaticFlags = TS_SS_REGIONS;
    
    retval = S_OK;
  }
  while( 0 );

  return retval;
}



//　ドキュメントの選択範囲を返すメソッドです。 終了位置の文字は含みません。「あいうえお」で「うえ」を選択して いる場合は開始位置が 2 、終了位置が 4 となります。
// 　ドキュメントにアクセスするメソッドなのでロック状態でない場合は TS_E_NOLOCK を返します。 
//! ドキュメントの選択範囲を取得する。
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

 
//　ドキュメントの指定した範囲の文字列を返すメソッドです。GetSelection() と同様に終了位置の文字は含みません。終了位置が -1 の場合は終わりまで、という意味になります。
//ドキュメントにアクセスするメソッドなのでロック状態でない場合は TS_E_NOLOCK を返します。 
//! テキストを取得する。
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
    
    // 文字列を格納。コピー先は L'\0' で終わっている必要は無い。
    if( IsBadWritePtr(o_plain_text, i_plain_text_length * sizeof(wchar_t)) == FALSE )
    {
      memset(o_plain_text, 0, i_plain_text_length * sizeof(wchar_t));
      memcpy(o_plain_text, m_text, copy_length * sizeof(wchar_t));
    }
    
    // 格納した文字列の文字数を格納。
    if( IsBadWritePtr(o_plain_text_length_p, sizeof ULONG) == FALSE )
    {
      *o_plain_text_length_p = copy_length;
    }
    
    // RUNINFO を格納。
    if( IsBadWritePtr(o_run_info_p, sizeof TS_RUNINFO) == FALSE )
    {
      o_run_info_p[0].type   = TS_RT_PLAIN;
      o_run_info_p[0].uCount = text_length;
    }
    
    // RUNINFO を格納した数を格納。
    if( IsBadWritePtr(o_run_info_length_p, sizeof ULONG) == FALSE )
      *o_run_info_length_p = 1;
    
    // 次の文字の位置を格納。
    if( IsBadWritePtr(o_next_unread_char_pos_p, sizeof LONG) == FALSE )
      *o_next_unread_char_pos_p = i_start_index + text_length;
    
    retval = S_OK;
  }
  while( 0 );
  
  return retval;
}

 
//　ドキュメントに対してインサートまたは選択範囲の変更が可能か問い合わせるメソッドです。これを実装してやらないと ITfFnReconversion の一部のメソッドが失敗してしまいます。ドキュメントのステータスによらず、操作が有効かどうかを問い合わせるメソッドみたいですね。 
//! テキストのインサートまたは選択範囲の変更が可能か問い合わせる。
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

 TsfReconverter の実装

　TSF 関連のオブジェクトの生成、取得、初期化を行い、変換候補を列挙するメソッドをもつクラスです。オブジェクトの生成、取得、初期は全てコンストラクタで行っています。失敗しても例外は投げないので、成功したかどうかは IsOpened() メソッドで確認します。
 　初期化に成功したら EnumCandidates() で変換候補文字列を取得します。2 番目の引数で指定したコールバック関数に列挙した文字列が渡されます。
 　SetFocus() はウィンドウがフォーカスを取得したとき(WM_SETFOCUS メッセージがきたとき)に呼び出します。 
TsfReconverter.h
   1 : #ifndef __TSF_RECONVERTER_H_INCLUDED__
   2 : #define __TSF_RECONVERTER_H_INCLUDED__
   3 : #include <msctf.h>
   4 : #include <msaatext.h>
   5 : #include <ctffunc.h>
   6 : #include "ReconvTextStore.h"
   7 : 
   8 : 
   9 : //! TsfReconverter::EnumCandidates() に渡すコールバック関数
//  10 : !
//  11 :  *  @param[in]      i_index
//  12 :  *    何番目の候補か。
//  13 :  *  @param[in]      i_number_of_candidates
//  14 :  *    候補のトータル数
//  15 :  *  @param[in]      i_candidate
//  16 :  *    候補文字列。コールバックから抜けたら文字列は解放される。
//  17 :  *  @param[in,out]  io_param
//  18 :  *    EnumCandidates() に渡したパラメーター。
//  19 :  *
//  20 :  *  @return 列挙を続ける場合は true, 中止する場合は false を返す。
//  21 :  
  22 : typedef bool (*EnumCandidatesCallbackP)(int             i_index,
  23 :                                         int             i_number_of_candidates,
  24 :                                         const wchar_t*  i_candidate,
  25 :                                         void*           io_param
  26 :                                        );
  27 : 
  28 : 
  29 : //! TSF(Text Service Framework) を利用して変換候補リストを取得するクラス。
  30 : class TsfReconverter
  31 : {
  32 :   //===========================================================================
  33 :   // 公開メソッド
  34 :   //===========================================================================
  35 : public:
  36 :   //! コンストラクタ
  37 :   TsfReconverter();
  38 :   //! デストラクタ
  39 :   virtual ~TsfReconverter();
  40 :   
  41 :   //! クリーンアップ
  42 :   bool Cleanup();
  43 :   
  44 :   //! 初期化に成功したかどうか調べる。
  45 :   bool IsOpened();
  46 :   
  47 :   //! フォーカスの取得。
  48 :   bool SetFocus();
  49 : 
  50 :   //! 変換候補リストを列挙する。
  51 :   bool EnumCandidates(
  52 :     const wchar_t*            i_yomi,
  53 :     EnumCandidatesCallbackP   i_callback,
  54 :     void*                     io_param
  55 :   );
  56 :   
  57 :   //===========================================================================
  58 :   // 非公開メソッド
  59 :   //===========================================================================
  60 : private:
  61 : 
  62 :   //! コピーコンストラクタは使用禁止
  63 :   TsfReconverter(const TsfReconverter&);
  64 :   //! 代入演算子は使用禁止
  65 :   const TsfReconverter& operator=(const TsfReconverter&);
  66 : 
  67 :   //===========================================================================
  68 :   // メンバ
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


コンストラクタ

　スレッドマネージャー、ドキュメントマネージャー、コンテキスト、ファンクションプロバイダー、リコンバージョンファンクションの生成または取得、初期化を行っています。テキストストアはコンテキスト生成時に指定しています(61行目で生成、67行目で指定)。 
TsfReconverter.cpp
   9 : //! コンストラクタ
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
  23 :     // スレッドマネージャーの生成
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
  34 :              "スレッドマネージャーの生成に失敗しました。エラーコード:0x%08X\n", hr
  35 :             );
  36 :       break;
  37 :     }
  38 :     
  39 :     // ドキュメントマネージャーの生成
  40 :     hr = m_thread_mgr_cp->CreateDocumentMgr(&m_document_mgr_cp);
  41 :     if( FAILED(hr) || m_document_mgr_cp == NULL )
  42 :     {
  43 :       _RPTF1(_CRT_WARN,
  44 :              "ドキュメントマネージャーの生成に失敗しました。エラーコード:0x%08X\n", hr
  45 :             );
  46 :       break;
  47 :     }
  48 :     
  49 :     // スレッドマネージャーのアクティブ化
  50 :     TfClientId  client_id = 0;
  51 :     hr = m_thread_mgr_cp->Activate(&client_id);
  52 :     if( FAILED(hr) )
  53 :     {
  54 :       _RPTF1(_CRT_WARN,
  55 :              "スレッドマネージャーのアクティブ化に失敗しました。エラーコード:0x%08X\n", hr
  56 :             );
  57 :       break;
  58 :     }
  59 :     
  60 :     // テキストストアの生成
  61 :     ReconvTextStore::CreateInstance(m_text_store_cp);
  62 :     
  63 :     // コンテキストの生成
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
  74 :              "コンテキストの生成に失敗しました。エラーコード:0x%08X\n", hr
  75 :             );
  76 :       break;
  77 :     }
  78 :     
  79 :     // コンテキストの push
  80 :     hr = m_document_mgr_cp->Push(m_context_cp);
  81 :     if( FAILED(hr) )
  82 :     {
  83 :       _RPTF1(_CRT_WARN,
  84 :              "コンテキストの push に失敗しました。エラーコード:0x%08X\n", hr
  85 :             );
  86 :       break;
  87 :     }
  88 :     
  89 :     // ファンクションプロバイダーを取得する。
  90 :     hr = m_thread_mgr_cp->GetFunctionProvider(
  91 :            GUID_SYSTEM_FUNCTIONPROVIDER,
  92 :            &m_function_provider_cp
  93 :          );
  94 :     if( FAILED(hr) )
  95 :     {
  96 :       _RPTF1(_CRT_WARN,
  97 :              "ファンクションプロバイダーの取得に失敗しました。エラーコード:0x%08X\n", hr
  98 :             );
  99 :       break;
 100 :     }
 101 : 
 102 :     // ITfFnReconversion の取得
 103 :     hr = m_function_provider_cp->GetFunction(
 104 :            GUID_NULL,
 105 :            IID_ITfFnReconversion,
 106 :            (IUnknown**)&m_reconversion_cp
 107 :          );
 108 :     if( FAILED(hr) )
 109 :     {
 110 :       _RPTF1(_CRT_WARN, "ITfFnReconversion の取得に失敗しました。エラーコード : 0x%08X.\n", hr);
 111 :       break;
 112 :     }
 113 :     
 114 :     // フォーカス取得
 115 :     hr = m_thread_mgr_cp->SetFocus(m_document_mgr_cp);
 116 :     if( FAILED(hr) )
 117 :     {
 118 :       _RPTF1(_CRT_WARN,
 119 :              "スレッドマネージャーの SetFocus() に失敗しました。エラーコード:0x%08X\n", hr
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

　オブジェクトの破棄を行います。ITfDocumentMgr::Pop() や ITfThreadMgr::Deactivate() を呼び出さないと 　参照カウントが 0 にならず、COM オブジェクトが解放されないことがあるようです。 
TsfReconverter.cpp
 147 : //! クリーンアップ
 148 : bool TsfReconverter::Cleanup()
 149 : {
 150 :   // テキストストアの解放
 151 :   RELEASE(m_text_store_cp);
 152 :   // リコンバージョンファンクションの解放
 153 :   RELEASE(m_reconversion_cp);
 154 :   // ファンクションプロバイダーの解放
 155 :   RELEASE(m_function_provider_cp);
 156 :   // コンテキストの解放
 157 :   RELEASE(m_context_cp);
 158 :   // ドキュメントマネージャーの解放
 159 :   if( m_document_mgr_cp )
 160 :   {
 161 :     // 全てのコンテキストを解放する。
 162 :     m_document_mgr_cp->Pop(TF_POPF_ALL);
 163 :     RELEASE(m_document_mgr_cp);
 164 :   }
 165 :   // スレッドマネージャーの解放
 166 :   if( m_thread_mgr_cp )
 167 :   {
 168 :     // デアクティブにしてから解放する。
 169 :     m_thread_mgr_cp->Deactivate();
 170 :     RELEASE(m_thread_mgr_cp);
 171 :   }
 172 :   
 173 :   return true;
 174 : }



 SetFocus()

　スレッドマネージャーに入力フォーカスを持つように要求します。要するにテキストサービスから入力が欲しいということを TSF マネージャーに伝えるものだと思います。OS や TIP によってはフォーカスを持っている状態でないと ITfFnReconversion::GetReconversion() が動作しないようなので、ウィンドウがフォーカスを持った時にスレッドマネージャーにもフォーカスを持たせてやります。 
TsfReconverter.cpp
 190 : //! フォーカスの取得
 191 : bool TsfReconverter::SetFocus()
 192 : {
 193 :   bool    retval = false;
 194 :   
 195 :   if( IsOpened() )
 196 :   {
 197 :     // フォーカス
 198 :     HRESULT hr = m_thread_mgr_cp->SetFocus(m_document_mgr_cp);
 199 :     if( FAILED(hr) )
 200 :     {
 201 :       _RPTF1(_CRT_WARN,
 202 :              "スレッドマネージャーの SetFocus() に失敗しました。エラーコード:0x%08X\n", hr
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

　変換候補リストを取得するメソッドです。まぁ、取得というか列挙というか。i_yomi の変換候補と 3 番目に渡されたパラメータを 2 番目のパラメータに渡されたコールバック関数に渡します。
 　再変換には ITfFnReconversion がもつ「ドキュメントのこの範囲を再変換するとしたらどの範囲を再変換するか？」と問い合わせる QueryRange() メソッドと、実際に変換候補リストを取得する GetReconversion() メソッドを使います。
 　ただし、それら 2 つのメソッドに渡すドキュメントの範囲というのは数値型ではありません。ITfRange へのポインタを渡してやらなければいけないのです。そのポインタを取得するのが ITfContext::GetSelection() メソッドになります。ITfContext::GetSelection() メソッドはテキストストアの GetSelection() メソッドを呼び出し、数値型で返された範囲を ITfRange オブジェクトに変換してそのインターフェイスへのポインタを返してくれます。
 　ここで注意しなければいけないのは ITfFnReconversion::QueryRange() と ITfFnReconversion::GetReconversion() はテキストストアの RequestLock() をコールしてドキュメントにアクセスしてきますが、ITfContext::GetSelection() は RequestLock() を呼ばずにそのまま ITextStoreACP::GetSelection() メソッドを呼んできます。ですので、GetSelection() するときは自分でロックをかけておかないといけませんし、ITfFnReconversion のメソッドを呼び出すときは逆にロックを解除しておかないといけません。 
TsfReconverter.cpp
 218 : //! 変換候補リストを列挙する。
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
 238 :       _RPTF0(_CRT_WARN, "初期化に失敗したのに EnumCandidates() が呼ばれました。\n");
 239 :       break;
 240 :     }
 241 :   
 242 :     // 文字列をセット
 243 :     m_text_store_cp->SetString(i_yomi);
 244 :     
 245 :     // ドキュメントのロックを行う。
 246 :     if( m_text_store_cp->LockDocument(TS_LF_READ) )
 247 :     {
 248 :       // 選択範囲の取得
 249 :       hr = m_context_cp->GetSelection(
 250 :              m_edit_cookie,
 251 :              TF_DEFAULT_SELECTION,
 252 :              numberof(selections),
 253 :              selections,
 254 :              &fetched_count
 255 :            );
 256 :       
 257 :       // ドキュメントのアンロック
 258 :       m_text_store_cp->UnlockDocument();
 259 :       
 260 :       if( FAILED(hr) )
 261 :       {
 262 :         _RPTF1(_CRT_WARN, "選択範囲の取得に失敗しました。エラーコード : 0x%08X.\n", hr);
 263 :         break;
 264 :       }
 265 :     }
 266 :     
 267 :     // 変換範囲を取得する。
 268 :     hr = m_reconversion_cp->QueryRange(selections[0].range, &range_cp, &is_converted);
 269 :     if( FAILED(hr) || range_cp == NULL )
 270 :     {
 271 :       _RPTF1(_CRT_WARN, "変換範囲の取得に失敗しました。エラーコード : 0x%08X.\n", hr);
 272 :       break;
 273 :     }
 274 : 
 275 :     // 再変換を行う
 276 :     hr = m_reconversion_cp->GetReconversion(selections[0].range, &cand_list_cp);
 277 :     if( FAILED(hr) || cand_list_cp == NULL )
 278 :     {
 279 :       _RPTF1(_CRT_WARN, "再変換に失敗しました。エラーコード : 0x%08X.\n", hr);
 280 :       break;
 281 :     }
 282 :     
 283 :     // 候補数を取得する。
 284 :     hr = cand_list_cp->GetCandidateNum(&cand_length);
 285 :     if( FAILED(hr) )
 286 :     {
 287 :       _RPTF1(_CRT_WARN, "候補数の取得に失敗しました。エラーコード : 0x%08X.\n", hr);
 288 :       break;
 289 :     }
 290 :     
 291 :     // 候補を戻り値にセットする。
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
 313 :   // クリーンアップ
 314 :   RELEASE(cand_list_cp);
 315 :   RELEASE(range_cp);
 316 :   for(int i = 0; i < numberof(selections); i++)
 317 :   {
 318 :     RELEASE(selections[i].range);
 319 :   }
 320 :   
 321 :   return retval;
 322 : }

 テストプログラム

　UI の初期化をごちゃごちゃと書いてしまうと焦点がぼやけてしまうので、コマンドラインで受け取った引数に対する 変換リストを表示するプログラムにしてみました。 
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
  13 : //! TsfReconverter::EnumCandidates() に渡すコールバック
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
  29 : //! メインルーチン。
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


  実行結果
C:\TsfReconverter>tsftest.exe へんかん
 1/ 4 : 変換
 2/ 4 : 返還
 3/ 4 : へんかん
 4/ 4 : ヘンカン





*/


/*


// mbstowcs関数でワイド文字列へ変換
char    strm[]  = "Testストリング";
wchar_t strwfm[32];
setlocale( LC_ALL, "Japanese" );  
mbstowcs( strwfm, strm, strlen( strm )+1 );
wprintf( L"%s(文字数=%d)\n", strwfm, wcslen( strwfm ) );



wcstombs関数 - ワイド文字列→マルチバイト文字列



// wcstombs関数でマルチバイト文字列へ変換
wchar_t strw[]  = L"Testすとりんぐ";
char    strmfw[32];
setlocale( LC_ALL, "Japanese" );  
wcstombs( strmfw, strw, sizeof( strmfw ) );
printf( "%s(文字数=%d)\n", strmfw, strlen( strmfw ) );



*/
