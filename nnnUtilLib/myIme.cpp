//
//
//

#include <windows.h>

#include "..\nyanLib\include\\commonMacro.h"

#include "nameList.h"
#include "myTextStore.h"
#include "myIme.h"

char m_test[][64]=
{
	"候補１",
	"候補２",	
	"候補３",
};

CMyIME::CMyIME()
{
}

CMyIME::~CMyIME()
{
	End();
}

void CMyIME::End(void)
{
	
}


LPSTR CMyIME::Start(LPSTR text)
{
	m_dummy = 0;
	m_max = 3;
	return m_test[m_dummy];
}

LPSTR CMyIME::GetNext(void)
{
	m_dummy++;
	m_dummy %= m_max;
	return m_test[m_dummy];
}

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
ReconvTextStore.h
   1 : #ifndef __RECONV_TEXT_STORE_H_INCLUDED__
   2 : #define __RECONV_TEXT_STORE_H_INCLUDED__
   3 : #include <olectl.h>
   4 : #include <msctf.h>
   5 : #include <msaatext.h>
   6 : 
   7 : 
   8 : //! 変換候補リスト取得用のテキストストア
   9 : class ReconvTextStore : public ITextStoreACP
  10 : {
  11 : public:
  12 :   //! オブジェクトの生成
  13 :   static HRESULT CreateInstance(ReconvTextStore*& o_text_store_cp);
  14 :   //! デストラクタ
  15 :   virtual ~ReconvTextStore();
  16 : 
  17 :   //! ドキュメントのロックを行う。成功した場合 true, 失敗した場合 false を返す。
  18 :   bool LockDocument(DWORD i_lock_flags);
  19 :   //! ドキュメントのロックを解除する。ロックしてない状況で呼ばないこと。
  20 :   bool UnlockDocument();
  21 :   //! ドキュメントをロック中か？
  22 :   bool IsLocked(DWORD i_lock_flags);
  23 :   //! 変換候補リストを取得したい文字列をセットする。
  24 :   bool SetString(const wchar_t* i_string);
  25 : 
  26 :   //==========================================================================
  27 :   // IUnknown から継承するメソッド
  28 :   //==========================================================================
  29 :   
  30 :   //! 参照カウントのインクリメント
  31 :   STDMETHOD_ (DWORD, AddRef)();
  32 :   //! 参照カウントのデクリメントおよび解放
  33 :   STDMETHOD_ (DWORD, Release)();
  34 :   //! インターフェイスの問い合わせ
  35 :   STDMETHOD (QueryInterface)(REFIID, LPVOID*);
  36 : 
  37 :   //==========================================================================
  38 :   // ITextStoreACP から継承するメソッド
  39 :   //==========================================================================
  40 :   
  41 :   //! シンクの登録を行う。
  42 :   STDMETHODIMP AdviseSink(
  43 :     REFIID      i_riid,
  44 :     IUnknown*   io_unknown_cp,
  45 :     DWORD       i_mask
  46 :   );
  47 :   //! シンクの登録を解除する。
  48 :   STDMETHODIMP UnadviseSink(
  49 :     IUnknown*   io_unknown_cp
  50 :   );
  51 :   //! ドキュメントをロックして登録済みシンクのメソッドをコールする。
  52 :   STDMETHODIMP RequestLock(
  53 :     DWORD       i_lock_flags,
  54 :     HRESULT*    o_session_result_p
  55 :   );
  56 :   //! ドキュメントのステータスを取得する。
  57 :   STDMETHODIMP GetStatus(
  58 :     TS_STATUS*  o_document_status_p
  59 :   );
  60 :   //! ドキュメントの選択範囲を取得する。
  61 :   STDMETHODIMP GetSelection(
  62 :     ULONG               i_index,
  63 :     ULONG               i_selection_buffer_length,
  64 :     TS_SELECTION_ACP*   o_selections,
  65 :     ULONG*              o_fetched_length_p
  66 :   );
  67 :   //! テキストを取得する。
  68 :   STDMETHODIMP GetText(
  69 :     LONG          i_start_index,
  70 :     LONG          i_end_index,
  71 :     WCHAR*        o_plain_text,
  72 :     ULONG         i_plain_text_length,
  73 :     ULONG*        o_plain_text_length_p,
  74 :     TS_RUNINFO*   o_run_info_p,
  75 :     ULONG         i_run_info_length,
  76 :     ULONG*        o_run_info_length_p,
  77 :     LONG*         o_next_unread_char_pos_p
  78 :   );
  79 : 
  80 :   //! テキストのインサートまたは選択範囲の変更が可能か問い合わせる。
  81 :   STDMETHODIMP QueryInsert(
  82 :     LONG    i_start_index,
  83 :     LONG    i_end_index,
  84 :     ULONG   i_length,
  85 :     LONG*   o_start_index_p,
  86 :     LONG*   o_end_index_p
  87 :   );
  88 : 
  89 :   //==========================================================================
  90 :   // ReconvTextStore では実装しないメソッド。E_NOTIMPL を返す。 
  91 :   //==========================================================================
  92 : 
  93 :   STDMETHODIMP GetActiveView(
  94 :     TsViewCookie*
  95 :   );
  96 :   STDMETHODIMP SetSelection(
  97 :     ULONG, const TS_SELECTION_ACP*
  98 :   );
  99 :   STDMETHODIMP SetText(
 100 :     DWORD, LONG, LONG, const WCHAR*, ULONG, TS_TEXTCHANGE*
 101 :   );
 102 :   STDMETHODIMP GetFormattedText(
 103 :     LONG, LONG, IDataObject**
 104 :   );
 105 :   STDMETHODIMP RequestSupportedAttrs(
 106 :     DWORD, ULONG, const TS_ATTRID*
 107 :   );
 108 :   STDMETHODIMP RequestAttrsAtPosition(
 109 :     LONG, ULONG, const TS_ATTRID*, DWORD
 110 :   );
 111 :   STDMETHODIMP RetrieveRequestedAttrs(
 112 :     ULONG, TS_ATTRVAL*, ULONG*
 113 :   );
 114 :   STDMETHODIMP GetEndACP(
 115 :     LONG*
 116 :   );
 117 :   STDMETHODIMP GetTextExt(
 118 :     TsViewCookie, LONG, LONG, RECT*, BOOL*
 119 :   );
 120 :   STDMETHODIMP GetScreenExt(
 121 :     TsViewCookie, RECT*
 122 :   );
 123 :   STDMETHODIMP GetWnd(
 124 :     TsViewCookie, HWND*
 125 :   );
 126 :   STDMETHODIMP InsertTextAtSelection(
 127 :     DWORD, const WCHAR*, ULONG, LONG*, LONG*, TS_TEXTCHANGE*
 128 :   );
 129 :   STDMETHODIMP RequestAttrsTransitioningAtPosition(
 130 :     LONG, ULONG, const TS_ATTRID*, DWORD
 131 :   );
 132 :   STDMETHODIMP FindNextAttrTransition(
 133 :     LONG, LONG, ULONG, const TS_ATTRID*, DWORD, LONG*, BOOL*, LONG*
 134 :   );
 135 :   STDMETHODIMP GetEmbedded(
 136 :     LONG, REFGUID, REFIID, IUnknown**
 137 :   );
 138 :   STDMETHODIMP QueryInsertEmbedded(
 139 :     const GUID*, const FORMATETC*, BOOL*
 140 :   );
 141 :   STDMETHODIMP InsertEmbedded(
 142 :     DWORD, LONG, LONG, IDataObject*, TS_TEXTCHANGE*
 143 :   );
 144 :   STDMETHODIMP GetACPFromPoint(
 145 :     TsViewCookie, const POINT*, DWORD, LONG*
 146 :   );
 147 :   STDMETHODIMP InsertEmbeddedAtSelection(
 148 :     DWORD, IDataObject*, LONG*, LONG*, TS_TEXTCHANGE*
 149 :   );
 150 : 
 151 : protected:
 152 :   //! コンストラクタ。CreateInstance() かサブクラスからのみ呼び出し可能。
 153 :   ReconvTextStore();
 154 : 
 155 : private:
 156 :   //! コピーコンストラクタは使用禁止とする。
 157 :   ReconvTextStore(const ReconvTextStore&);
 158 :   //! 代入演算子は使用禁止とする。
 159 :   const ReconvTextStore& operator=(const ReconvTextStore&);
 160 : 
 161 :   //==========================================================================
 162 :   // メンバ
 163 :   //==========================================================================
 164 : protected:
 165 :   ULONG               m_ref_count;    //!< 参照カウント
 166 :   wchar_t             m_text[128];    //!< 変換したい文字列の格納領域
 167 :   ITextStoreACPSink*  m_sink_cp;      //!< AdviseSink() で登録されたシンク
 168 :   DWORD               m_sink_mask;    //!< AdviseSink() に渡されたマスク
 169 :   volatile LONG       m_lock_count;   //!< ロックカウント
 170 :   volatile DWORD      m_lock_flags;   //!< ロックのタイプ(RW)
 171 : };
 172 : 
 173 : 
 174 : #endif  // #ifndef __RECONV_TEXT_STORE_H_INCLUDED__
 
 　では定義のほうを見ていきましょう。 

AddRef(), Release()

　COM のお約束の処理です。AddRef() は参照カウントをインクリメントし、Release() は参照カウントをデク リメントし、0 になった場合は delete で自身を解放します。 
ReconvTextStore.cpp
 137 : //! 参照カウントのインクリメント
 138 : STDMETHODIMP_(DWORD) ReconvTextStore::AddRef()
 139 : {
 140 :   return ++m_ref_count;
 141 : }


ReconvTextStore.cpp
 147 : //! 参照カウントのデクリメントおよび解放
 148 : STDMETHODIMP_(DWORD) ReconvTextStore::Release()
 149 : {
 150 :   DWORD retval = --m_ref_count;
 151 :   
 152 :   if( retval == 0 )
 153 :     delete this;
 154 : 
 155 :   return retval;
 156 : }

 QueryInterface()

　REFIID で要求するインターフェイスのIDが渡されるのでそれに応じて 2 番目の引数を通じて返してやります。 これもほとんどお約束の処理です。 
ReconvTextStore.cpp
 162 : //! インターフェイスの問い合わせ
 163 : STDMETHODIMP ReconvTextStore::QueryInterface(
 164 :   REFIID    i_riid,
 165 :   LPVOID*   o_interface_cp_p
 166 : )
 167 : {
 168 :   HRESULT   retval = E_FAIL;
 169 : 
 170 :   do
 171 :   {
 172 :     if( IsBadWritePtr(o_interface_cp_p, sizeof(LPVOID)) )
 173 :     {
 174 :       retval = E_INVALIDARG;
 175 :       break;
 176 :     }
 177 : 
 178 :     if( IsEqualIID(i_riid, IID_IUnknown) || IsEqualIID(i_riid, IID_ITextStoreACP) )
 179 :     {
 180 :       retval = S_OK;
 181 :       *o_interface_cp_p = (ITextStoreACP*)this;
 182 :       // 成功した場合は参照カウントを増やす
 183 :       AddRef();
 184 :     }
 185 :     else
 186 :     {
 187 :       *o_interface_cp_p = NULL;
 188 :       retval = E_NOINTERFACE;
 189 :     }
 190 :   }
 191 :   while( 0 );
 192 :   
 193 :   return retval;
 194 : }



 AdviseSink()

　名前からは何をするものなのか分かりにくいのですが、端的に言えばコールバックの登録です。テキストストアは、ドキュメントの変更などイベントが発生した時に、登録されているシンクの対応するメソッドを呼び出してやらなければいけません。TSF マネージャーにテキストストアを登録すると、TSF マネージャーから呼び出されます。
 　1番目の引数は登録したいシンクのインターフェイスID、2番目の引数は登録するシンクへのポインタ、3番目の引数はコールバックして欲しいイベントの種類を指定するフラグです。
 　サンプルの tsfapp 同様、1つのシンクだけしか登録できないようにします。登録要求のあったシンクをメンバ変数の m_sink_cp に、マスクを m_sink_mask に保存しておきます。 
ReconvTextStore.cpp
 229 : //! シンクの登録を行う。
 230 : STDMETHODIMP ReconvTextStore::AdviseSink(
 231 :   REFIID      i_riid,
 232 :   IUnknown*   io_unknown_cp,
 233 :   DWORD       i_mask
 234 : )
 235 : {
 236 :   HRESULT   retval    = E_FAIL;
 237 :   
 238 :   do
 239 :   {
 240 :     // io_unknown_cp に正しいポインタが渡されたかチェックする。
 241 :     // また、登録できるシンクは ITextStoreACPSink だけ。
 242 :     if( IsBadReadPtr(io_unknown_cp, sizeof(IUnknown*))
 243 :     ||  IsEqualIID(i_riid, IID_ITextStoreACPSink) == false )
 244 :     {
 245 :       _RPTF0(_CRT_WARN, "*** Error *** bad ptr or object.\n");
 246 :       retval = E_INVALIDARG;
 247 :       break;
 248 :     }
 249 :     
 250 :     // 既に登録されているシンクと同じ場合はマスクの更新を行う。
 251 :     if( IsEqualObject(m_sink_cp, io_unknown_cp) )
 252 :     {
 253 :       m_sink_mask = i_mask;
 254 :       retval = S_OK;
 255 :     }
 256 :     // 既にシンクが登録されている場合は失敗。
 257 :     else if( m_sink_cp )
 258 :     {
 259 :       _RPTF0(_CRT_WARN, "*** Error *** sink already exists.\n");
 260 :       retval = CONNECT_E_ADVISELIMIT;
 261 :     }
 262 :     // 新しく登録
 263 :     else
 264 :     {
 265 :       // ITextStoreACPSink インターフェイスを取得する。
 266 :       retval = io_unknown_cp->QueryInterface(
 267 :                  IID_ITextStoreACPSink,
 268 :                  (void**)&m_sink_cp
 269 :                );
 270 :       // 成功した場合はマスクを保存する。
 271 :       if( SUCCEEDED(retval) )
 272 :         m_sink_mask = i_mask;
 273 :     }
 274 :   }
 275 :   while( 0 );
 276 :   
 277 :   return retval;
 278 : }


 UnadviseSink()

　シンクの登録を解除します。1番目の引数は解除したいシンクへのポインタです。 
ReconvTextStore.cpp
 284 : //! シンクの登録を解除する。
 285 : STDMETHODIMP ReconvTextStore::UnadviseSink(
 286 :   IUnknown*   io_unknown_cp
 287 : )
 288 : {
 289 :   HRESULT     retval      = E_FAIL;
 290 :   IUnknown*   unk_id_cp   = NULL;
 291 :   
 292 :   do
 293 :   {
 294 :     // 有効なポインタが渡されたか調べる。
 295 :     if( IsBadReadPtr(io_unknown_cp, sizeof(void*)) )
 296 :     {
 297 :       _RPTF0(_CRT_WARN, "*** Error *** io_unknown_cp is bad ptr.\n");
 298 :       retval = E_INVALIDARG;
 299 :       break;
 300 :     }
 301 :   
 302 :     // 登録されていないシンクの場合はエラー。
 303 :     if( IsEqualObject(io_unknown_cp, m_sink_cp) == false )
 304 :     {
 305 :       _RPTF0(_CRT_WARN, "*** Error *** no connection.\n");
 306 :       retval = CONNECT_E_NOCONNECTION;
 307 :       break;
 308 :     }
 309 : 
 310 :     // 解放
 311 :     RELEASE(m_sink_cp);
 312 :     m_sink_mask = 0;
 313 :     retval = S_OK;
 314 :   }
 315 :   while( 0 );
 316 :   
 317 :   return retval;
 318 : }


 RequestLock()

　ドキュメントに対してロックを要求し、ロックが成功した場合に登録してあるシンクの OnLockGranted() メソッドを 呼ぶメソッドです。
 　TSF では複数のテキストサービスから同時に入力がくる可能性があります。例えばキーボードを押しながら音声入力を 行った場合などです。他にも、アプリケーション側でドキュメントを読み込んだり変更したい場合だってあります。 そのような場合に一つのドキュメントに対して各々が好き勝手にアクセスできてしまっては困ります。
 　TSF の作法では自身が管理していないドキュメントへアクセスするには必ず RequestLock() でロック要求を出して、 呼び出された OnLockGranted() メソッドの中で行います。OnLockGranted() を直訳すると「ロックが認められた時」 なのでそのままですね。
 　ロックされていない状況でドキュメントにアクセスするメソッドが呼ばれた場合、テキストストアは TS_E_NOLOCK エラーを返す必要があります。
 　なお、RequestLock() に対応するアンロックの要求というのはありません。テキストストアは OnLockGranted() から 制御が返されたらドキュメントへのアクセスが終了したということでロックを解除します。
 　自身の管理しているドキュメントへアクセスする場合には上記の作法に従う (OnLockGranted() 内でのみドキュメントへアクセスする)必要はないようです。

 　1番目の引数は読取専用や読み書きの両方を行うといったロックのタイプを表すフラグです。
 　2番目の引数はシンクの OnLockGranted() メソッドの戻り値の格納先です。

ReconvTextStore.cpp
 324 : //! ドキュメントをロックして登録済みシンクのメソッドをコールする。
 325 : STDMETHODIMP ReconvTextStore::RequestLock(
 326 :   DWORD       i_lock_flags,
 327 :   HRESULT*    o_session_result_p
 328 : )
 329 : {
 330 :   HRESULT   retval      = E_FAIL;
 331 :   LONG      lock_count  = InterlockedIncrement(&m_lock_count);
 332 :   
 333 :   do
 334 :   {
 335 :     // シンクが登録されていない場合はエラー
 336 :     if( m_sink_cp == NULL )
 337 :     {
 338 :       _RPTF0(_CRT_WARN, "*** Error *** m_sink_cp is NULL.\n");
 339 :       retval = E_UNEXPECTED;
 340 :       break;
 341 :     }
 342 :     
 343 :     // 有効な引数か？
 344 :     if( IsBadWritePtr(o_session_result_p, sizeof(HRESULT)) )
 345 :     {
 346 :       _RPTF0(_CRT_WARN, "*** Error *** o_session_result_p is bad ptr.\n");
 347 :       retval = E_INVALIDARG;
 348 :       break;
 349 :     }
 350 :     
 351 :     *o_session_result_p = E_FAIL;
 352 : 
 353 :     // ロックに失敗した場合。
 354 :     if( lock_count != 1 )
 355 :     {
 356 :       _RPTF1(_CRT_WARN, "*** Error *** unable to lock. count : %d.\n", lock_count);
 357 : 
 358 :       // 同期ロックを要求。
 359 :       if( (i_lock_flags & TS_LF_SYNC) == TS_LF_SYNC )
 360 :         *o_session_result_p = TS_E_SYNCHRONOUS;
 361 :       else  // 非同期要求
 362 :         *o_session_result_p = E_NOTIMPL;
 363 : 
 364 :       retval = S_OK;  // 戻り値は S_OK
 365 :       break;
 366 :     }
 367 :     
 368 :     // OnLockGranted() をコールする。
 369 :     m_lock_flags = i_lock_flags;
 370 :     try
 371 :     {
 372 :       *o_session_result_p = m_sink_cp->OnLockGranted(i_lock_flags);
 373 :     }
 374 :     catch(...)
 375 :     {
 376 :       _RPTF0(_CRT_WARN, "*** ERROR *** exception occured.\n");
 377 :       *o_session_result_p = E_FAIL;
 378 :     }
 379 :     m_lock_flags = 0;
 380 : 
 381 :     retval = S_OK;
 382 :   }
 383 :   while( 0 );
 384 :   
 385 :   InterlockedDecrement(&m_lock_count);
 386 :   
 387 :   return retval;
 388 : }


 ReconvTextStore.cpp
  42 : //! ドキュメントのロックを行う。成功した場合 true, 失敗した場合 false を返す。
  43 : bool ReconvTextStore::LockDocument(DWORD i_lock_flags)
  44 : {
  45 :   bool    retval      = false;
  46 :   LONG    lock_count  = InterlockedIncrement(&m_lock_count);
  47 :   
  48 :   if( lock_count == 1 )
  49 :   {
  50 :     m_lock_flags  = i_lock_flags;
  51 :     retval        = true;
  52 :   }
  53 :   else
  54 :   {
  55 :     InterlockedDecrement(&m_lock_count);
  56 :   }
  57 :   
  58 :   return retval;
  59 : }


ReconvTextStore.cpp
  65 : //! ドキュメントのロックを解除する。ロックしてない状況で呼ばないこと。
  66 : bool ReconvTextStore::UnlockDocument()
  67 : {
  68 :   bool    retval      = false;
  69 :   
  70 :   if( m_lock_flags )
  71 :   {
  72 :     m_lock_flags = 0;
  73 :     retval = true;
  74 :     InterlockedDecrement(&m_lock_count);
  75 :   }
  76 :   
  77 :   return retval;
  78 : }


ReconvTextStore.cpp
  84 : //! ドキュメントをロック中か？
  85 : bool ReconvTextStore::IsLocked(DWORD i_lock_flags)
  86 : {
  87 :   return (m_lock_flags & i_lock_flags) == i_lock_flags;
  88 : }


SetString()

　変換候補リストを取得したい文字列をテキストストアに突っ込むメソッドです。 
ReconvTextStore.cpp
  94 : //! 変換候補リストを取得したい文字列をセットする。
  95 : bool ReconvTextStore::SetString(const wchar_t* i_string)
  96 : {
  97 :   bool    retval      = false;
  98 :   
  99 :   do
 100 :   {
 101 :     if( IsBadReadPtr(i_string, sizeof(wchar_t)) )
 102 :     {
 103 :       _RPTF0(_CRT_WARN, "*** ERROR *** i_string is bad ptr.\n");
 104 :       break;
 105 :     }
 106 : 
 107 :     if( LockDocument(TS_LF_READWRITE) == false )
 108 :     {
 109 :       _RPTF0(_CRT_WARN, "*** Error *** unable to lock.\n");
 110 :       break;
 111 :     }
 112 : 
 113 :     TS_TEXTCHANGE text_change = { 0 };
 114 :     text_change.acpStart  = 0;
 115 :     text_change.acpOldEnd = lstrlen(m_text);
 116 :     text_change.acpNewEnd = lstrlen(i_string);
 117 :     
 118 :     lstrcpyn(m_text, i_string, numberof(m_text) - 1);
 119 :     UnlockDocument();
 120 :       
 121 :     if( m_sink_cp && (m_sink_mask & TS_AS_TEXT_CHANGE) )
 122 :       m_sink_cp->OnTextChange(0, &text_change);
 123 : 
 124 :     retval = true;
 125 :   }
 126 :   while( 0 );
 127 :   
 128 :   return retval;
 129 : }


 GetStatus()

　ドキュメントのステータスを返すメソッドです。ステータスとは読取専用や処理中などの状態のことです。 他にも複数の選択を許可するかどうかを返さなければいけません。今回、テキストサービスから入力を受け付ける 必要はありませんので、読取専用、一つの選択しか許可しない、と返します。 
ReconvTextStore.cpp
 394 : //! ドキュメントのステータスを取得する。
 395 : STDMETHODIMP ReconvTextStore::GetStatus(
 396 :   TS_STATUS*  o_document_status_p
 397 : )
 398 : {
 399 :   HRESULT   retval = E_INVALIDARG;
 400 :   
 401 :   do
 402 :   {
 403 :     if( IsBadWritePtr(o_document_status_p, sizeof TS_STATUS) )
 404 :     {
 405 :       _RPTF0(_CRT_WARN, "*** ERROR *** o_document_status_p is bad ptr.\n");
 406 :       retval = E_INVALIDARG;
 407 :       break;
 408 :     }
 409 :     
 410 :     o_document_status_p->dwDynamicFlags = TS_SD_READONLY;
 411 :     // 一つの選択しか許可しない
 412 :     o_document_status_p->dwStaticFlags = TS_SS_REGIONS;
 413 :     
 414 :     retval = S_OK;
 415 :   }
 416 :   while( 0 );
 417 : 
 418 :   return retval;
 419 : }


GetSelection()

　ドキュメントの選択範囲を返すメソッドです。 終了位置の文字は含みません。「あいうえお」で「うえ」を選択して いる場合は開始位置が 2 、終了位置が 4 となります。
 　ドキュメントにアクセスするメソッドなのでロック状態でない場合は TS_E_NOLOCK を返します。 
ReconvTextStore.cpp
 425 : //! ドキュメントの選択範囲を取得する。
 426 : STDMETHODIMP ReconvTextStore::GetSelection(
 427 :   ULONG               i_index,
 428 :   ULONG               i_selection_buffer_length,
 429 :   TS_SELECTION_ACP*   o_selections,
 430 :   ULONG*              o_fetched_length_p
 431 : )
 432 : {
 433 :   HRESULT   retval = E_INVALIDARG;
 434 :   
 435 :   do
 436 :   {
 437 :     if( IsBadWritePtr(o_selections, sizeof TS_SELECTION_ACP)
 438 :     ||  IsBadWritePtr(o_fetched_length_p, sizeof(ULONG)) )
 439 :     {
 440 :       _RPTF0(_CRT_WARN, "*** ERROR *** invalid parameter.\n");
 441 :       retval = E_INVALIDARG;
 442 :       break;
 443 :     }
 444 :     
 445 :     *o_fetched_length_p = 0;
 446 :     
 447 :     if( IsLocked(TS_LF_READ) == false )
 448 :     {
 449 :       _RPTF0(_CRT_WARN, "*** ERROR *** no lock.\n");
 450 :       retval = TS_E_NOLOCK;
 451 :       break;
 452 :     }
 453 :     
 454 :     if( i_index != TF_DEFAULT_SELECTION && i_index > 0 )
 455 :     {
 456 :       _RPTF0(_CRT_WARN, "*** ERROR *** i_index is not valid.\n");
 457 :       retval = E_INVALIDARG;
 458 :       break;
 459 :     }
 460 :     
 461 :     memset(o_selections, 0, sizeof(o_selections[0]));
 462 :     o_selections[0].acpStart = 0;
 463 :     if( m_text[0] )
 464 :       o_selections[0].acpEnd = lstrlen(m_text);
 465 :     else
 466 :       o_selections[0].acpEnd = 0;
 467 :     o_selections[0].style.fInterimChar  = FALSE;
 468 :     o_selections[0].style.ase           = TS_AE_START;
 469 : 
 470 :     *o_fetched_length_p = 1;
 471 :     retval = S_OK;
 472 :   }
 473 :   while( 0 );
 474 :   
 475 :   return retval;
 476 : }


GetText()

　ドキュメントの指定した範囲の文字列を返すメソッドです。GetSelection() と同様に終了位置の文字は含みません。終了位置が -1 の場合は終わりまで、という意味になります。
 　ドキュメントにアクセスするメソッドなのでロック状態でない場合は TS_E_NOLOCK を返します。 
ReconvTextStore.cpp
 482 : //! テキストを取得する。
 483 : STDMETHODIMP ReconvTextStore::GetText(
 484 :   LONG          i_start_index,
 485 :   LONG          i_end_index,
 486 :   WCHAR*        o_plain_text,
 487 :   ULONG         i_plain_text_length,
 488 :   ULONG*        o_plain_text_length_p,
 489 :   TS_RUNINFO*   o_run_info_p,
 490 :   ULONG         i_run_info_length,
 491 :   ULONG*        o_run_info_length_p,
 492 :   LONG*         o_next_unread_char_pos_p
 493 : )
 494 : {
 495 :   HRESULT   retval = E_INVALIDARG;
 496 :   
 497 :   do
 498 :   {
 499 :     if( IsLocked(TS_LF_READ) == false )
 500 :     {
 501 :       retval = TS_E_NOLOCK;
 502 :       break;
 503 :     }
 504 :     
 505 :     ULONG   text_length = lstrlen(m_text);
 506 :     ULONG   copy_length = min(text_length, i_plain_text_length);
 507 :     
 508 :     // 文字列を格納。コピー先は L'\0' で終わっている必要は無い。
 509 :     if( IsBadWritePtr(o_plain_text, i_plain_text_length * sizeof(wchar_t)) == FALSE )
 510 :     {
 511 :       memset(o_plain_text, 0, i_plain_text_length * sizeof(wchar_t));
 512 :       memcpy(o_plain_text, m_text, copy_length * sizeof(wchar_t));
 513 :     }
 514 :     
 515 :     // 格納した文字列の文字数を格納。
 516 :     if( IsBadWritePtr(o_plain_text_length_p, sizeof ULONG) == FALSE )
 517 :     {
 518 :       *o_plain_text_length_p = copy_length;
 519 :     }
 520 :     
 521 :     // RUNINFO を格納。
 522 :     if( IsBadWritePtr(o_run_info_p, sizeof TS_RUNINFO) == FALSE )
 523 :     {
 524 :       o_run_info_p[0].type   = TS_RT_PLAIN;
 525 :       o_run_info_p[0].uCount = text_length;
 526 :     }
 527 :     
 528 :     // RUNINFO を格納した数を格納。
 529 :     if( IsBadWritePtr(o_run_info_length_p, sizeof ULONG) == FALSE )
 530 :       *o_run_info_length_p = 1;
 531 :     
 532 :     // 次の文字の位置を格納。
 533 :     if( IsBadWritePtr(o_next_unread_char_pos_p, sizeof LONG) == FALSE )
 534 :       *o_next_unread_char_pos_p = i_start_index + text_length;
 535 :     
 536 :     retval = S_OK;
 537 :   }
 538 :   while( 0 );
 539 :   
 540 :   return retval;
 541 : }


 QueryInsert()

　ドキュメントに対してインサートまたは選択範囲の変更が可能か問い合わせるメソッドです。これを実装してやらないと ITfFnReconversion の一部のメソッドが失敗してしまいます。ドキュメントのステータスによらず、操作が有効かどうかを問い合わせるメソッドみたいですね。 
ReconvTextStore.cpp
 547 : //! テキストのインサートまたは選択範囲の変更が可能か問い合わせる。
 548 : STDMETHODIMP ReconvTextStore::QueryInsert(
 549 :   LONG    i_start_index,
 550 :   LONG    i_end_index,
 551 :   ULONG   i_length,
 552 :   LONG*   o_start_index_p,
 553 :   LONG*   o_end_index_p
 554 : )
 555 : {
 556 :   HRESULT retval = E_FAIL;
 557 : 
 558 :   if( i_start_index < 0
 559 :   ||  i_start_index > i_end_index
 560 :   ||  i_end_index   > lstrlen(m_text) )
 561 :   {
 562 :     retval = E_INVALIDARG;
 563 :   }
 564 :   else
 565 :   {
 566 :     if( o_start_index_p )
 567 :       *o_start_index_p = i_start_index;
 568 :     
 569 :     if( o_end_index_p )
 570 :       *o_end_index_p   = i_end_index;
 571 : 
 572 :     retval = S_OK;
 573 :   }
 574 :   
 575 :   return retval;
 576 : }


　今回、テキストストアに実装したメソッドは以上です。他は E_NOTEMPL エラーを返すだけです。テキストサービスから入力を受け付けたい場合は他にいろいろと実装してやらなければいけませんし、メッセージループにも手を加えなければいけません。 



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
