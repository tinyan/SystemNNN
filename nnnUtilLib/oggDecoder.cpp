//
// COggDecoder
//

#include <windows.h>

#include "oggDecoder.h"


#include <stdio.h>


#include <Math.h>







/*

#if !defined _MT

	#if defined _DEBUG
	//#pragma comment(lib,"ogg_static_d.lib")
	//#pragma comment(lib,"vorbis_static_d.lib")
	#pragma comment(lib,"ogg_d.lib")
	#pragma comment(lib,"vorbis_d.lib")
	#else
	#pragma comment(lib,"ogg_static.lib")
	#pragma comment(lib,"vorbis_static.lib")
	//#pragma comment(lib,"ogg.lib")
	//#pragma comment(lib,"vorbis.lib")
	#endif

#else

	#if defined _DEBUG
	//#pragma comment(lib,"ogg_static_d.lib")
	//#pragma comment(lib,"vorbis_static_d.lib")
	#pragma comment(lib,"ogg_d.lib")
	#pragma comment(lib,"vorbis_d.lib")
	#else
	#pragma comment(lib,"ogg_static.lib")
	#pragma comment(lib,"vorbis_static.lib")
	//#pragma comment(lib,"ogg.lib")
	//#pragma comment(lib,"vorbis.lib")
	#endif

#endif

*/


ogg_int16_t convbuffer[4096]; /* take 8k out of the data segment, not the stack */


COggDecoder::COggDecoder()
{
	m_decodeStartFlag = FALSE;

}

COggDecoder::~COggDecoder()
{
	End();
}

void COggDecoder::End(void)
{
	if (m_decodeStartFlag)
	{
	//	EndDecode();
		m_decodeStartFlag = FALSE;
	}
}

int COggDecoder::DecodeAll(char* srcData,int dataSize, short* decodedBuffer)
{
//OutputDebugString("[StartDecode]");
	int offset = StartDecode(srcData,dataSize,decodedBuffer);
	BOOL flg = TRUE;
	while (flg)
	{
//OutputDebugString("[inDecode]");
		int sz = Decode(offset);
		if (sz <= 0) flg = FALSE;
		offset += sz;
	}

//char mes[256];
//sprintf(mes,"%X",offset);
//OutputDebugString(mes);
	return offset;


}



int COggDecoder::StartDecode(char* srcData,int dataSize, short* decodedBuffer)
{
	m_srcData = srcData;
	m_decodedBuffer = decodedBuffer;
	m_dataSize = dataSize;
	m_dataNokori = dataSize;

	m_eos = 0;
//	m_moveData = 0;


	if (m_decodeStartFlag)
	{
	//	EndDecode();
	}
	m_decodeStartFlag = TRUE;
	
	ogg_sync_init(&oy);
	m_buffer = ogg_sync_buffer(&oy,4096);

	int moveSize = m_dataNokori;
	if (moveSize>4096) moveSize = 4096;

	if (moveSize>0)
	{
		memcpy(m_buffer,m_srcData + m_dataSize - m_dataNokori,moveSize);
	}

	int bytes = moveSize;

	m_dataNokori -= moveSize;

	ogg_sync_wrote(&oy,bytes);

	if(ogg_sync_pageout(&oy,&og)!=1)
	{
		/* have we simply run out of data?  If so, we're done. */
		if(bytes<4096)
		{
			//end ‚±‚±‚É‚Í‚±‚È‚¢‚Í‚¸
//OutputDebugString("[error1inOggDecoder]");
			return 0;
//			break;
		}
			
		MyErrorOut("Must not be Vorbis data","Error 1");
//MessageBox(NULL,"Must not be Vorbis data","Error 1",MB_OK);
//OutputDebugString("[Error 1:Must not be Vorbis data]");
		return 0;
	}
	
	ogg_stream_init(&os,ogg_page_serialno(&og));

	vorbis_info_init(&vi);
	vorbis_comment_init(&vc);
	if(ogg_stream_pagein(&os,&og)<0)
	{ 
		MyErrorOut("Error reading first page of Ogg bitstream data.\n");
		return 0;
		/* error; stream version mismatch perhaps */
//		fprintf(stderr,"Error reading first page of Ogg bitstream data.\n");
//		exit(1);
	}
    
	if(ogg_stream_packetout(&os,&op)!=1)
	{ 
		MyErrorOut("Error reading initial header packet.\n");
		return 0;
	}
    
	if(vorbis_synthesis_headerin(&vi,&vc,&op)<0)
	{ 
		MyErrorOut("This Ogg bitstream does not contain Vorbis ");
		return 0;
	}


	int i=0;
	while(i<2)
	{
		while(i<2)
		{
			int result=ogg_sync_pageout(&oy,&og);
			if(result==0)break; /* Need more data */
				/* Don't complain about missing or corrupt data yet.  We'll catch it at the packet output phase */
			if(result==1)
			{
				ogg_stream_pagein(&os,&og); /* we can ignore any errors here as they'll also become apparent at packetout */
				while(i<2)
				{
					result=ogg_stream_packetout(&os,&op);
					if(result==0)break;
					if(result<0)
					{
						MyErrorOut("Corrupt secondary header.  Exiting.\n");
						return 0;
					}
			
					vorbis_synthesis_headerin(&vi,&vc,&op);
					i++;
				}
			}
		}
		if (i<2)
		{
	/* no harm in not checking before adding more */
			m_buffer=ogg_sync_buffer(&oy,4096);
	//		bytes=fread(buffer,1,4096,stdin);
			moveSize = m_dataNokori;
			if (moveSize>4096) moveSize = 4096;
			memcpy(m_buffer,m_srcData + m_dataSize - m_dataNokori,moveSize);
			bytes = moveSize;
			m_dataNokori -= moveSize;

			if(bytes==0 && i<2)
			{
				MyErrorOut("End of file before finding all Vorbis headers!\n");
				return 0;
			}

			ogg_sync_wrote(&oy,bytes);
		}
	}
    
		/* Throw the comments plus a few lines about the bitstream we're
		   decoding */
	{
		char **ptr=vc.user_comments;
		while(*ptr)
		{
//OutputDebugString(*ptr);
//				fprintf(stderr,"%s\n",*ptr);
			++ptr;
		}

//char mes[256];
//sprintf(mes,"\nBitstream is %d channel, %ldHz\n",vi.channels,vi.rate);
//OutputDebugString(mes);

//		fprintf(stderr,"\nBitstream is %d channel, %ldHz\n",vi.channels,vi.rate);
//		fprintf(stderr,"Encoded by: %s\n\n",vc.vendor);
	}
    
	m_convSize = 4096/vi.channels;

    /* OK, got and parsed all three headers. Initialize the Vorbis
       packet->PCM decoder. */
	vorbis_synthesis_init(&vd,&vi); /* central decode state */
	vorbis_block_init(&vd,&vb);     /* local state for most of the decode
*/



	return Decode(0);
//	return Decode(44);
}


int COggDecoder::Decode(int offset)
{
	int eos = 0;

	int makedSize = offset;

	int decodedSize = 0;

	while(!eos)
	{
		while(!eos)
		{
			int result=ogg_sync_pageout(&oy,&og);
			if(result==0)break; /* need more data */
			if(result<0)
			{
				MyErrorOut("Corrupt or missing data in bitstream");
			}
			else
			{
				ogg_stream_pagein(&os,&og); /* can safely ignore errors at this point */

				while(1)
				{
					result=ogg_stream_packetout(&os,&op);

					if(result==0)break; /* need more data */
					
					if(result<0)
					{ /* missing or corrupt data at this page position *//* no reason to complain; already complained above */
					}
					else
					{
						/* we have a packet.  Decode it */
						float **pcm;
						int samples;
		  
						if(vorbis_synthesis(&vb,&op)==0) /* test for success! */
						{
							vorbis_synthesis_blockin(&vd,&vb);
						}

						while((samples=vorbis_synthesis_pcmout(&vd,&pcm))>0)
						{
							int j;
							int clipflag=0;
							int bout=(samples<m_convSize?samples:m_convSize);

							int channels = vi.channels;

							for(int i=0;i<channels;i++)
							{
								ogg_int16_t* ptr = convbuffer+i;
								float* mono=pcm[i];
								for(j=0;j<bout;j++)
								{
									int val=(int)(mono[j]*32767.f);
									if(val>32767)
									{
										val=32767;
										clipflag=1;
									}
									if(val<-32768)
									{
										val=-32768;
										clipflag=1;
									}
									*ptr=val;
									ptr += channels;
								}
							}
							int outputDataSize = sizeof(short) * channels * bout;
							memcpy(m_decodedBuffer + makedSize/2 ,convbuffer,outputDataSize);
							vorbis_synthesis_read(&vd,bout);
							makedSize += outputDataSize;
							decodedSize += outputDataSize;

//							if (makedSize>=1024*128) return makedSize;

//							if (decodedSize>=1024*128)
//							{
//								OutputDebugString("[128k]");
//								return decodedSize;
//							}


						}	    
					}
				}

				if(ogg_page_eos(&og))eos=1;
			}
		}

		if(!eos)
		{
			m_buffer=ogg_sync_buffer(&oy,4096);
			int moveSize = m_dataNokori;
			if (moveSize>4096) moveSize = 4096;
			if (moveSize>0)
			{
				memcpy(m_buffer,m_srcData+m_dataSize-m_dataNokori,moveSize);
			}
			int bytes = moveSize;
			m_dataNokori -= moveSize;

			ogg_sync_wrote(&oy,bytes);
			if(bytes==0)eos=1;
		}
	}
    
//OutputDebugString("[LAST]");
	EndDecode();

	return decodedSize;
//	return makedSize;
}


void COggDecoder::EndDecode(void)
{
	if (m_decodeStartFlag)
	{


	    ogg_stream_clear(&os);
  
    /* ogg_page and ogg_packet structs always point to storage in
       libvorbis.  They're never freed or manipulated directly */
    
		vorbis_block_clear(&vb);
		vorbis_dsp_clear(&vd);
		vorbis_comment_clear(&vc);
		vorbis_info_clear(&vi);  /* must be called last */







		ogg_sync_clear(&oy);

		m_decodeStartFlag = FALSE;
	}
}


void COggDecoder::MyErrorOut(LPSTR mes, LPSTR title)
{
	char titleMessage[256];
	if (title != NULL)
	{
		int ln = (int)strlen(title);
		if (ln>254) ln = 254;
		memcpy(titleMessage,title,ln);
		titleMessage[ln] = 0;
		titleMessage[ln+1] = 0;
	}
	else
	{
		char et[] = "ERROR";
		memcpy(titleMessage,et,(int)strlen(et)+1);
	}
//	MessageBox(NULL,mes,titleMessage,MB_OK | MB_ICONEXCLAMATION);
	OutputDebugString(mes);
}



/*_*/

