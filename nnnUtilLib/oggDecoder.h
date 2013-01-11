//
// oggDecoder.h
//

#if !defined __TINYAN_OGGDECODER__
#define __TINYAN_OGGDECODER__

#include <vorbis/codec.h>

class COggDecoder
{
public:
	COggDecoder();
	~COggDecoder();
	void End(void);

	int StartDecode(char* srcData,int dataSize, short* decodedBuffer);
	int Decode(int offset = 0);	//decode max 128k

	int DecodeAll(char* srcData,int dataSize, short* decodedBuffer);


	void EndDecode(void);
private:
	char* m_srcData;
	short* m_decodedBuffer;
	int m_dataSize;
	int m_dataNokori;
	int m_convSize;

	BOOL m_decodeStartFlag;

	ogg_sync_state oy; /* sync and verify incoming physical bitstream */
	ogg_stream_state os; /* take physical pages, weld into a logical stream of packets */
	ogg_page og; /* one Ogg bitstream page.  Vorbis packets are inside */
	ogg_packet op; /* one raw packet of data for decode */
	vorbis_info vi; /* struct that stores all the static vorbis bitstream settings */
	vorbis_comment vc; /* struct that stores all the bitstream user comments */
	vorbis_dsp_state vd; /* central working state for the packet->PCM decoder */
	vorbis_block vb; /* local working space for packet->PCM decode */

	int m_eos;
	char* m_buffer;

	void MyErrorOut(LPSTR mes, LPSTR title = NULL);
	
};



#endif
/*_*/

