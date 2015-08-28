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
	"候補１",
	"候補２",	
	"候補３",
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
	  // スレッドマネージャーの生成
	  hr = CoCreateInstance(
			 CLSID_TF_ThreadMgr,
			 NULL,
			 CLSCTX_INPROC_SERVER,
			 IID_ITfThreadMgr,
			 (void**)&m_thread_mgr_cp
		   );
	  if( FAILED(hr) )
	  {
//		_RPTF1(_CRT_WARN, "スレッドマネージャーの生成に失敗しました。エラーコード:0x%08X\n", hr );
		OutputDebugString("_CRT_WARN, スレッドマネージャーの生成に失敗しました。エラーコード:0x%08X\n, hr ");
		break;
	  }
  
	  // ドキュメントマネージャーの生成
	  hr = m_thread_mgr_cp->CreateDocumentMgr(&m_document_mgr_cp);
	  if( FAILED(hr) || m_document_mgr_cp == NULL )
	  {
//		_RPTF1(_CRT_WARN,   "ドキュメントマネージャーの生成に失敗しました。エラーコード:0x%08X\n", hr  );
		OutputDebugString("_CRT_WARN,   ドキュメントマネージャーの生成に失敗しました。エラーコード:0x%08X\n, hr  ");
		break;
	  }
  
	  // スレッドマネージャーのアクティブ化
	  TfClientId  client_id = 0;
	  hr = m_thread_mgr_cp->Activate(&client_id);
	  if( FAILED(hr) )
	  {
//		_RPTF1(_CRT_WARN,  "スレッドマネージャーのアクティブ化に失敗しました。エラーコード:0x%08X\n", hr		  );
		OutputDebugString("_CRT_WARN,  スレッドマネージャーのアクティブ化に失敗しました。エラーコード:0x%08X\n, hr		  ");
		break;
	  }
  
	  // テキストストアの生成
	  CMyTextStore::CreateInstance(m_text_store_cp);
  
	  // コンテキストの生成
	  hr = m_document_mgr_cp->CreateContext(
			 client_id,
			 0,     // reserved
			 (ITextStoreACP*)m_text_store_cp,
			 &m_context_cp,
			 &m_edit_cookie
		   );
	  if( FAILED(hr) )
	  {
//		_RPTF1(_CRT_WARN,  "コンテキストの生成に失敗しました。エラーコード:0x%08X\n", hr  );
		OutputDebugString("_CRT_WARN,  コンテキストの生成に失敗しました。エラーコード:0x%08X\n, hr  ");
		break;
	  }
//hr = E_FAIL;  
//break;

	  // コンテキストの push
	  hr = m_document_mgr_cp->Push(m_context_cp);
	  if( FAILED(hr) )
	  {
//		_RPTF1(_CRT_WARN,   "コンテキストの push に失敗しました。エラーコード:0x%08X\n", hr  );
		OutputDebugString("_CRT_WARN,   コンテキストの push に失敗しました。エラーコード:0x%08X\n, hr  ");
		break;
	  }
  
	  // ファンクションプロバイダーを取得する。
	  hr = m_thread_mgr_cp->GetFunctionProvider(
			 GUID_SYSTEM_FUNCTIONPROVIDER,
			 &m_function_provider_cp
		   );
	  if( FAILED(hr) )
	  {
//		_RPTF1(_CRT_WARN,   "ファンクションプロバイダーの取得に失敗しました。エラーコード:0x%08X\n", hr	  );
		OutputDebugString("_CRT_WARN,   ファンクションプロバイダーの取得に失敗しました。エラーコード:0x%08X\n, hr	  ");
		break;
	  }

	  // ITfFnReconversion の取得
	  hr = m_function_provider_cp->GetFunction(
			 GUID_NULL,
			 IID_ITfFnReconversion,
			 (IUnknown**)&m_reconversion_cp
		   );
	  if( FAILED(hr) )
	  {
//		_RPTF1(_CRT_WARN, "ITfFnReconversion の取得に失敗しました。エラーコード : 0x%08X.\n", hr);
		OutputDebugString("_CRT_WARN ITfFnReconversion の取得に失敗しました。エラーコード : 0x%08X.\n hr");
		break;
	  }
  
	  // フォーカス取得
	  hr = m_thread_mgr_cp->SetFocus(m_document_mgr_cp);
	  if( FAILED(hr) )
	  {
//		_RPTF1(_CRT_WARN,  "スレッドマネージャーの SetFocus() に失敗しました。エラーコード:0x%08X\n", hr  );
		OutputDebugString("_CRT_WARN,  スレッドマネージャーの SetFocus() に失敗しました。エラーコード:0x%08X\n hr  ");
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


LPSTR CMyIME::Start(LPSTR text)
{
	WCHAR wText[4096];

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
	int ln = strlen(mes);
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

//　オブジェクトの破棄を行います。ITfDocumentMgr::Pop() や ITfThreadMgr::Deactivate() を呼び出さないと 　参照カウントが 0 にならず、COM オブジェクトが解放されないことがあるようです。 
//! クリーンアップ
bool CMyIME::Cleanup()
{
  // テキストストアの解放
  ENDRELEASE(m_text_store_cp);
  // リコンバージョンファンクションの解放
  ENDRELEASE(m_reconversion_cp);
  // ファンクションプロバイダーの解放
  ENDRELEASE(m_function_provider_cp);
  // コンテキストの解放
  ENDRELEASE(m_context_cp);
  // ドキュメントマネージャーの解放
  if( m_document_mgr_cp )
  {
    // 全てのコンテキストを解放する。
//@@    m_document_mgr_cp->Pop(TF_POPF_ALL);
    m_document_mgr_cp->Pop(0);
    ENDRELEASE(m_document_mgr_cp);
  }
  // スレッドマネージャーの解放
  if( m_thread_mgr_cp )
  {
    // デアクティブにしてから解放する。
    m_thread_mgr_cp->Deactivate();
    ENDRELEASE(m_thread_mgr_cp);
  }
  
  m_opened = FALSE;

  return true;
}




//　スレッドマネージャーに入力フォーカスを持つように要求します。要するにテキストサービスから入力が欲しいということを TSF マネージャーに伝えるものだと思います。OS や TIP によってはフォーカスを持っている状態でないと ITfFnReconversion::GetReconversion() が動作しないようなので、ウィンドウがフォーカスを持った時にスレッドマネージャーにもフォーカスを持たせてやります。 
//! フォーカスの取得
bool CMyIME::SetFocus()
{
  bool    retval = false;
  
  if( IsOpened() )
  {
    // フォーカス
    HRESULT hr = m_thread_mgr_cp->SetFocus(m_document_mgr_cp);
    if( FAILED(hr) )
    {
//      _RPTF1(_CRT_WARN,         "スレッドマネージャーの SetFocus() に失敗しました。エラーコード:0x%08X\n", hr           );
      OutputDebugString("_CRT_WARN,         スレッドマネージャーの SetFocus() に失敗しました。エラーコード:0x%08X\n, hr           ");
    }
    else
    {
      retval = true;
    }
  }
  
  return retval;
}

//　変換候補リストを取得するメソッドです。まぁ、取得というか列挙というか。i_yomi の変換候補と 3 番目に渡されたパラメータを 2 番目のパラメータに渡されたコールバック関数に渡します。
//再変換には ITfFnReconversion がもつ「ドキュメントのこの範囲を再変換するとしたらどの範囲を再変換するか？」と問い合わせる QueryRange() メソッドと、実際に変換候補リストを取得する GetReconversion() メソッドを使います。
// 　ただし、それら 2 つのメソッドに渡すドキュメントの範囲というのは数値型ではありません。ITfRange へのポインタを渡してやらなければいけないのです。そのポインタを取得するのが ITfContext::GetSelection() メソッドになります。ITfContext::GetSelection() メソッドはテキストストアの GetSelection() メソッドを呼び出し、数値型で返された範囲を ITfRange オブジェクトに変換してそのインターフェイスへのポインタを返してくれます。
// 　ここで注意しなければいけないのは ITfFnReconversion::QueryRange() と ITfFnReconversion::GetReconversion() はテキストストアの RequestLock() をコールしてドキュメントにアクセスしてきますが、ITfContext::GetSelection() は RequestLock() を呼ばずにそのまま ITextStoreACP::GetSelection() メソッドを呼んできます。ですので、GetSelection() するときは自分でロックをかけておかないといけませんし、ITfFnReconversion のメソッドを呼び出すときは逆にロックを解除しておかないといけません。 

//! 変換候補リストを列挙する。
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
//      _RPTF0(_CRT_WARN, "初期化に失敗したのに EnumCandidates() が呼ばれました。\n");
      OutputDebugString("_CRT_WARN, 初期化に失敗したのに EnumCandidates() が呼ばれました。\n");
      break;
    }
  
    // 文字列をセット
    m_text_store_cp->SetString(i_yomi);
    
    // ドキュメントのロックを行う。
    if( m_text_store_cp->LockDocument(TS_LF_READ) )
    {
      // 選択範囲の取得
      hr = m_context_cp->GetSelection(
             m_edit_cookie,
             TF_DEFAULT_SELECTION,
             numberof(selections),
             selections,
             &fetched_count
           );
      
      // ドキュメントのアンロック
      m_text_store_cp->UnlockDocument();
      
      if( FAILED(hr) )
      {
//        _RPTF1(_CRT_WARN, "選択範囲の取得に失敗しました。エラーコード : 0x%08X.\n", hr);
        OutputDebugString("_CRT_WARN, 選択範囲の取得に失敗しました。エラーコード : 0x%08X.\n, hr");
        break;
      }
    }
    
    // 変換範囲を取得する。
    hr = m_reconversion_cp->QueryRange(selections[0].range, &range_cp, &is_converted);
    if( FAILED(hr) || range_cp == NULL )
    {
//      _RPTF1(_CRT_WARN, "変換範囲の取得に失敗しました。エラーコード : 0x%08X.\n", hr);
      OutputDebugString("_CRT_WARN, 変換範囲の取得に失敗しました。エラーコード : 0x%08X.\n, hr");
      break;
    }

    // 再変換を行う
    hr = m_reconversion_cp->GetReconversion(selections[0].range, &cand_list_cp);
    if( FAILED(hr) || cand_list_cp == NULL )
    {
//      _RPTF1(_CRT_WARN, "再変換に失敗しました。エラーコード : 0x%08X.\n", hr);
      OutputDebugString("_CRT_WARN, 再変換に失敗しました。エラーコード : 0x%08X.\n, hr");
      break;
    }
    
    // 候補数を取得する。
    hr = cand_list_cp->GetCandidateNum(&cand_length);
    if( FAILED(hr) )
    {
//      _RPTF1(_CRT_WARN, "候補数の取得に失敗しました。エラーコード : 0x%08X.\n", hr);
      OutputDebugString("_CRT_WARN, 候補数の取得に失敗しました。エラーコード : 0x%08X.\n, hr");
      break;
    }
    
    // 候補を戻り値にセットする。
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
  
  // クリーンアップ
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
*/

/*


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
