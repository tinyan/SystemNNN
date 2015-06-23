//
//
//

#if !defined __NNNUTILLIB_MYIME__
#define __NNNUTILLIB_MYIME__

#include <msctf.h>
#include <msaatext.h>
#include <ctffunc.h>


class CNameList;

class CMyTextStore;


class CMyIME
{
public:
	CMyIME();
	~CMyIME();
	void End(void);


	LPSTR Start(LPSTR text);
	LPSTR GetNext(void);




	typedef bool (*EnumCandidatesCallbackP)(int             i_index,
                                        int             i_number_of_candidates,
                                        const wchar_t*  i_candidate,
                                        void*           io_param
                                       );



	static CMyIME* m_this;

	static bool EnumCandidatesCallback(
	  int             i_index,
	  int             i_number_of_candidates,
	  const wchar_t*  i_candidate,
	  void*           io_param
	);
	bool MyCallback(
	  int             i_index,
	  int             i_number_of_candidates,
	  const wchar_t*  i_candidate,
	  void*           io_param
	);

	bool Cleanup(void);

//! �������ɐ����������ǂ������ׂ�B
	bool IsOpened(void);

//! �t�H�[�J�X�̎擾�B
	bool SetFocus(void);

//! �ϊ���⃊�X�g��񋓂���B
	bool EnumCandidates(
							const wchar_t*            i_yomi,
							EnumCandidatesCallbackP   i_callback,
							void*                     io_param
);



	BOOL CheckKanjiOnly(LPSTR mes);


private:
	int m_max;
	char* m_buffer;
	int m_bufferMax;
	int m_bufferLength;
	int m_number;

	BOOL m_opened;
//	CMyTextStore* m_textStore;


	//! �R�s�[�R���X�g���N�^�͎g�p�֎~
	CMyIME(const CMyIME&);
	//! ������Z�q�͎g�p�֎~
	const CMyIME& operator=(const CMyIME&);


	ITfThreadMgr*         m_thread_mgr_cp;
	ITfDocumentMgr*       m_document_mgr_cp;
	ITfContext*           m_context_cp;
	ITfFunctionProvider*  m_function_provider_cp;
	CMyTextStore*      m_text_store_cp;
	ITfFnReconversion*    m_reconversion_cp;
	TfEditCookie          m_edit_cookie;

};


#endif
/*_*/
