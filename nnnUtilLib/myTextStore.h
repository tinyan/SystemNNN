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
//! �ϊ���⃊�X�g�擾�p�̃e�L�X�g�X�g�A
public:
  //! �I�u�W�F�N�g�̐���
  static HRESULT CreateInstance(CMyTextStore*& o_text_store_cp);
  //! �f�X�g���N�^
  virtual ~CMyTextStore();

  //! �h�L�������g�̃��b�N���s���B���������ꍇ true, ���s�����ꍇ false ��Ԃ��B
  bool LockDocument(DWORD i_lock_flags);
  //! �h�L�������g�̃��b�N����������B���b�N���ĂȂ��󋵂ŌĂ΂Ȃ����ƁB
  bool UnlockDocument();
  //! �h�L�������g�����b�N�����H
  bool IsLocked(DWORD i_lock_flags);
  //! �ϊ���⃊�X�g���擾��������������Z�b�g����B
  bool SetString(const wchar_t* i_string);

  //==========================================================================
  // IUnknown ����p�����郁�\�b�h
  //==========================================================================
  
  //! �Q�ƃJ�E���g�̃C���N�������g
  STDMETHOD_ (DWORD, AddRef)();
  //! �Q�ƃJ�E���g�̃f�N�������g����щ��
  STDMETHOD_ (DWORD, Release)();
  //! �C���^�[�t�F�C�X�̖₢���킹
  STDMETHOD (QueryInterface)(REFIID, LPVOID*);

  //==========================================================================
  // ITextStoreACP ����p�����郁�\�b�h
  //==========================================================================
  
  //! �V���N�̓o�^���s���B
  STDMETHODIMP AdviseSink(
    REFIID      i_riid,
    IUnknown*   io_unknown_cp,
    DWORD       i_mask
  );
  //! �V���N�̓o�^����������B
  STDMETHODIMP UnadviseSink(
    IUnknown*   io_unknown_cp
  );
  //! �h�L�������g�����b�N���ēo�^�ς݃V���N�̃��\�b�h���R�[������B
  STDMETHODIMP RequestLock(
    DWORD       i_lock_flags,
    HRESULT*    o_session_result_p
  );
  //! �h�L�������g�̃X�e�[�^�X���擾����B
  STDMETHODIMP GetStatus(
    TS_STATUS*  o_document_status_p
  );
  //! �h�L�������g�̑I��͈͂��擾����B
  STDMETHODIMP GetSelection(
    ULONG               i_index,
    ULONG               i_selection_buffer_length,
    TS_SELECTION_ACP*   o_selections,
    ULONG*              o_fetched_length_p
  );
  //! �e�L�X�g���擾����B
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

  //! �e�L�X�g�̃C���T�[�g�܂��͑I��͈͂̕ύX���\���₢���킹��B
  STDMETHODIMP QueryInsert(
    LONG    i_start_index,
    LONG    i_end_index,
    ULONG   i_length,
    LONG*   o_start_index_p,
    LONG*   o_end_index_p
  );

  //==========================================================================
  // �������Ȃ����\�b�h�BE_NOTIMPL ��Ԃ��B 
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
  //! �R���X�g���N�^�BCreateInstance() ���T�u�N���X����̂݌Ăяo���\�B
  CMyTextStore();

private:
  //! �R�s�[�R���X�g���N�^�͎g�p�֎~�Ƃ���B
  CMyTextStore(const CMyTextStore&);
  //! ������Z�q�͎g�p�֎~�Ƃ���B
  const CMyTextStore& operator=(const CMyTextStore&);

  //==========================================================================
  // �����o
  //==========================================================================
protected:
  ULONG               m_ref_count;    //!< �Q�ƃJ�E���g
  wchar_t             m_text[128];    //!< �ϊ�������������̊i�[�̈�
  ITextStoreACPSink*  m_sink_cp;      //!< AdviseSink() �œo�^���ꂽ�V���N
  DWORD               m_sink_mask;    //!< AdviseSink() �ɓn���ꂽ�}�X�N
  volatile LONG       m_lock_count;   //!< ���b�N�J�E���g
  volatile DWORD      m_lock_flags;   //!< ���b�N�̃^�C�v(RW)
};


#endif
/*_*/
