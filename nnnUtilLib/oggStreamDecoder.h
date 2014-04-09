//
// oggStreamDecoder.h
//

#if !defined __NNNUTILLIB_OGGSTREAMDECODER__
#define __NNNUTILLIB_OGGSTREAMDECODER__

#include <vorbis/codec.h>

class COggStreamDecoder
{
public:
	COggStreamDecoder(LPVOID convbuffer);
	~COggStreamDecoder();
	void End(void);


	BOOL StartDecode(LPVOID file);
	BOOL StartDecode2(LPVOID file);
	int Decode(void);
	void EndDecode(void);

private:
	ogg_int16_t* m_convBuffer;
	LPVOID m_file;
//	HANDLE m_fileHandle;
	char* m_buffer;
	BOOL m_decodeStartFlag;


	char* m_srcData;
	short* m_decodedBuffer;
	int m_dataSize;
	int m_dataNokori;
	int m_convSize;

	ogg_sync_state m_oggSyncState; /* sync and verify incoming physical bitstream */
	ogg_page m_oggPage; /* one Ogg bitstream page.  Vorbis packets are inside */
	ogg_stream_state m_oggStreamState; /* take physical pages, weld into a logical stream of packets */
	ogg_packet m_oggPacket; /* one raw packet of data for decode */


	vorbis_info m_vorbisInfo; /* struct that stores all the static vorbis bitstream settings */
	vorbis_comment m_vorbisComment; /* struct that stores all the bitstream user comments */
	vorbis_dsp_state m_vorbisDspState; /* central working state for the packet->PCM decoder */
	vorbis_block m_vorbisBlock; /* local working space for packet->PCM decode */

//	ogg_sync_state oy; /* sync and verify incoming physical bitstream */
//	ogg_stream_state os; /* take physical pages, weld into a logical stream of packets */
//	ogg_page og; /* one Ogg bitstream page.  Vorbis packets are inside */
//	ogg_packet op; /* one raw packet of data for decode */
//	vorbis_info vi; /* struct that stores all the static vorbis bitstream settings */
//	vorbis_comment vc; /* struct that stores all the bitstream user comments */
//	vorbis_dsp_state vd; /* central working state for the packet->PCM decoder */
//	vorbis_block vb; /* local working space for packet->PCM decode */

	int m_eos;
	void MyErrorOut(LPSTR mes, LPSTR title = NULL);


	BOOL m_needRead;
	BOOL m_needSynth;
	BOOL m_packetCheckFlag;
};



#endif
/*_*/

