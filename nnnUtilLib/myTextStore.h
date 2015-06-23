//
//
//

#if !defined __NNNUTILLIB_MYTEXTSTORE__
#define __NNNUTILLIB_MYTEXTSTORE__


#include <olectl.h>
#include <msctf.h>
#include <msaatext.h>

class CMyTextStore : public ITextStoreACP
{
//! 変換候補リスト取得用のテキストストア
public:
  //! オブジェクトの生成
  static HRESULT CreateInstance(CMyTextStore*& o_text_store_cp);
  //! デストラクタ
  virtual ~CMyTextStore();

  //! ドキュメントのロックを行う。成功した場合 true, 失敗した場合 false を返す。
  bool LockDocument(DWORD i_lock_flags);
  //! ドキュメントのロックを解除する。ロックしてない状況で呼ばないこと。
  bool UnlockDocument();
  //! ドキュメントをロック中か？
  bool IsLocked(DWORD i_lock_flags);
  //! 変換候補リストを取得したい文字列をセットする。
  bool SetString(const wchar_t* i_string);

  //==========================================================================
  // IUnknown から継承するメソッド
  //==========================================================================
  
  //! 参照カウントのインクリメント
  STDMETHOD_ (DWORD, AddRef)();
  //! 参照カウントのデクリメントおよび解放
  STDMETHOD_ (DWORD, Release)();
  //! インターフェイスの問い合わせ
  STDMETHOD (QueryInterface)(REFIID, LPVOID*);

  //==========================================================================
  // ITextStoreACP から継承するメソッド
  //==========================================================================
  
  //! シンクの登録を行う。
  STDMETHODIMP AdviseSink(
    REFIID      i_riid,
    IUnknown*   io_unknown_cp,
    DWORD       i_mask
  );
  //! シンクの登録を解除する。
  STDMETHODIMP UnadviseSink(
    IUnknown*   io_unknown_cp
  );
  //! ドキュメントをロックして登録済みシンクのメソッドをコールする。
  STDMETHODIMP RequestLock(
    DWORD       i_lock_flags,
    HRESULT*    o_session_result_p
  );
  //! ドキュメントのステータスを取得する。
  STDMETHODIMP GetStatus(
    TS_STATUS*  o_document_status_p
  );
  //! ドキュメントの選択範囲を取得する。
  STDMETHODIMP GetSelection(
    ULONG               i_index,
    ULONG               i_selection_buffer_length,
    TS_SELECTION_ACP*   o_selections,
    ULONG*              o_fetched_length_p
  );
  //! テキストを取得する。
  STDMETHODIMP GetText(
    LONG          i_start_index,
    LONG          i_end_index,
    WCHAR*        o_plain_text,
    ULONG         i_plain_text_length,
    ULONG*        o_plain_text_length_p,
    TS_RUNINFO*   o_run_info_p,
    ULONG         i_run_info_length,
    ULONG*        o_run_info_length_p,
    LONG*         o_next_unread_char_pos_p
  );

  //! テキストのインサートまたは選択範囲の変更が可能か問い合わせる。
  STDMETHODIMP QueryInsert(
    LONG    i_start_index,
    LONG    i_end_index,
    ULONG   i_length,
    LONG*   o_start_index_p,
    LONG*   o_end_index_p
  );

  //==========================================================================
  // 実装しないメソッド。E_NOTIMPL を返す。 
  //==========================================================================

  STDMETHODIMP GetActiveView(
    TsViewCookie*
  );
  STDMETHODIMP SetSelection(
    ULONG, const TS_SELECTION_ACP*
  );
  STDMETHODIMP SetText(
    DWORD, LONG, LONG, const WCHAR*, ULONG, TS_TEXTCHANGE*
  );
  STDMETHODIMP GetFormattedText(
    LONG, LONG, IDataObject**
  );
  STDMETHODIMP RequestSupportedAttrs(
    DWORD, ULONG, const TS_ATTRID*
  );
  STDMETHODIMP RequestAttrsAtPosition(
    LONG, ULONG, const TS_ATTRID*, DWORD
  );
  STDMETHODIMP RetrieveRequestedAttrs(
    ULONG, TS_ATTRVAL*, ULONG*
  );
  STDMETHODIMP GetEndACP(
    LONG*
  );
  STDMETHODIMP GetTextExt(
    TsViewCookie, LONG, LONG, RECT*, BOOL*
  );
  STDMETHODIMP GetScreenExt(
    TsViewCookie, RECT*
  );
  STDMETHODIMP GetWnd(
    TsViewCookie, HWND*
  );
  STDMETHODIMP InsertTextAtSelection(
    DWORD, const WCHAR*, ULONG, LONG*, LONG*, TS_TEXTCHANGE*
  );
  STDMETHODIMP RequestAttrsTransitioningAtPosition(
    LONG, ULONG, const TS_ATTRID*, DWORD
  );
  STDMETHODIMP FindNextAttrTransition(
    LONG, LONG, ULONG, const TS_ATTRID*, DWORD, LONG*, BOOL*, LONG*
  );
  STDMETHODIMP GetEmbedded(
    LONG, REFGUID, REFIID, IUnknown**
  );
  STDMETHODIMP QueryInsertEmbedded(
    const GUID*, const FORMATETC*, BOOL*
  );
  STDMETHODIMP InsertEmbedded(
    DWORD, LONG, LONG, IDataObject*, TS_TEXTCHANGE*
  );
  STDMETHODIMP GetACPFromPoint(
    TsViewCookie, const POINT*, DWORD, LONG*
  );
  STDMETHODIMP InsertEmbeddedAtSelection(
    DWORD, IDataObject*, LONG*, LONG*, TS_TEXTCHANGE*
  );

protected:
  //! コンストラクタ。CreateInstance() かサブクラスからのみ呼び出し可能。
  CMyTextStore();

private:
  //! コピーコンストラクタは使用禁止とする。
  CMyTextStore(const CMyTextStore&);
  //! 代入演算子は使用禁止とする。
  const CMyTextStore& operator=(const CMyTextStore&);

  //==========================================================================
  // メンバ
  //==========================================================================
protected:
  ULONG               m_ref_count;    //!< 参照カウント
  wchar_t             m_text[128];    //!< 変換したい文字列の格納領域
  ITextStoreACPSink*  m_sink_cp;      //!< AdviseSink() で登録されたシンク
  DWORD               m_sink_mask;    //!< AdviseSink() に渡されたマスク
  volatile LONG       m_lock_count;   //!< ロックカウント
  volatile DWORD      m_lock_flags;   //!< ロックのタイプ(RW)
};


#endif
/*_*/
