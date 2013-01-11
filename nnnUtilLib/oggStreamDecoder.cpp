//
// COggStreamDecoder
//

#include <windows.h>
#include "oggStreamDecoder.h"
#include <stdio.h>

#include <Math.h>



//44100*2*2
//176400


//8192byte(4096short) x 22 block
//
//+amari(1block)


/*
#if !defined _MT

	#if defined _DEBUG
	//#pragma comment(lib,"ogg_static_d.lib")
	//#pragma comment(lib,"vorbis_static_d.lib")
	#pragma comment(lib,"ogg_d.lib")
	#pragma comment(lib,"vorbis_d.lib")
	#else
	//#pragma comment(lib,"ogg_static.lib")
	//#pragma comment(lib,"vorbis_static.lib")
	#pragma comment(lib,"ogg.lib")
	#pragma comment(lib,"vorbis.lib")
	#endif

#else

	#if defined _DEBUG
	//#pragma comment(lib,"ogg_static_d.lib")
	//#pragma comment(lib,"vorbis_static_d.lib")
	#pragma comment(lib,"ogg_d.lib")
	#pragma comment(lib,"vorbis_d.lib")
	#else
	//#pragma comment(lib,"ogg_static.lib")
	//#pragma comment(lib,"vorbis_static.lib")
	#pragma comment(lib,"ogg.lib")
	#pragma comment(lib,"vorbis.lib")
	#endif

#endif
*/


//ogg_int16_t convbuffer[4096]; /* take 8k out of the data segment, not the stack */


COggStreamDecoder::COggStreamDecoder(LPVOID convbuffer)
{
	m_convBuffer = (ogg_int16_t*)convbuffer;
	m_decodeStartFlag = FALSE;
}



COggStreamDecoder::~COggStreamDecoder()
{
	End();
}

void COggStreamDecoder::End(void)
{
	if (m_decodeStartFlag)
	{
		EndDecode();
		m_decodeStartFlag = FALSE;
	}
}

BOOL COggStreamDecoder::StartDecode(LPVOID file)
{
	return FALSE;//old routine
}

BOOL COggStreamDecoder::StartDecode2(HANDLE handle)
{
//	m_file = file;
	m_fileHandle = handle;
	char mes[256];
	mes[0] = 0;

	m_eos = 0;

	if (m_decodeStartFlag)
	{
		EndDecode();
	}
	m_decodeStartFlag = TRUE;
	
	ogg_sync_init(&m_oggSyncState);
	m_buffer = ogg_sync_buffer(&m_oggSyncState,4096);
OutputDebugString("S");

//	int readSize = fread(m_buffer,sizeof(char),4096,m_file);
	int readSize;
	ReadFile(m_fileHandle,m_buffer,4096,(DWORD*)&readSize,NULL);
	ogg_sync_wrote(&m_oggSyncState,readSize);

	if(ogg_sync_pageout(&m_oggSyncState,&m_oggPage)!=1)
	{
		/* have we simply run out of data?  If so, we're done. */
		if(readSize<4096)
		{
			//end ‚±‚±‚É‚Í‚±‚È‚¢‚Í‚¸
			MyErrorOut("[error1inOggDecoder]");
			return FALSE;
		}
			
		MyErrorOut("Must not be Vorbis data","Error 1");
		return FALSE;
	}

	ogg_stream_init(&m_oggStreamState,ogg_page_serialno(&m_oggPage));




	vorbis_info_init(&m_vorbisInfo);
	vorbis_comment_init(&m_vorbisComment);



	if(ogg_stream_pagein(&m_oggStreamState,&m_oggPage)<0)
	{ 
		MyErrorOut("Error reading first page of Ogg bitstream data.\n");
		return FALSE;
	}


	if(ogg_stream_packetout(&m_oggStreamState,&m_oggPacket)!=1)
	{ 
		MyErrorOut("Error reading initial header packet.\n");
		return FALSE;
	}
    
	if(vorbis_synthesis_headerin(&m_vorbisInfo,&m_vorbisComment,&m_oggPacket)<0)
	{ 
		MyErrorOut("This Ogg bitstream does not contain Vorbis ");
		return FALSE;
	}


	int i=0;
	while(i<2)
	{
		while(i<2)
		{
			int result=ogg_sync_pageout(&m_oggSyncState,&m_oggPage);
			if(result==0)break; /* Need more data */
				/* Don't complain about missing or corrupt data yet.  We'll catch it at the packet output phase */
			if(result==1)
			{
				ogg_stream_pagein(&m_oggStreamState,&m_oggPage); /* we can ignore any errors here as they'll also become apparent at packetout */
				while(i<2)
				{
					result=ogg_stream_packetout(&m_oggStreamState,&m_oggPacket);
					if(result==0)break;
					if(result<0)
					{
						MyErrorOut("Corrupt secondary header.  Exiting.\n");
						return FALSE;
					}
			
					vorbis_synthesis_headerin(&m_vorbisInfo,&m_vorbisComment,&m_oggPacket);
					i++;
				}
			}
		}

		if (i<2)
		{
		/* no harm in not checking before adding more */
			m_buffer=ogg_sync_buffer(&m_oggSyncState,4096);




//			readSize = fread(m_buffer,sizeof(char),4096,m_file);
			ReadFile(m_fileHandle,m_buffer,4096,(DWORD*)&readSize,NULL);
OutputDebugString("A");

			if((readSize == 0) && (i<2))
			{
				MyErrorOut("End of file before finding all Vorbis headers!\n");
				return FALSE;
			}

			ogg_sync_wrote(&m_oggSyncState,readSize);
		}
	}
    


		/* Throw the comments plus a few lines about the bitstream we're
		   decoding */

	char** ppComment = m_vorbisComment.user_comments;
	while(*ppComment)
	{
#if defined _DEBUG
		OutputDebugString(*ppComment);
#endif
		++ppComment;
	}

#if defined _DEBUG
	wsprintf(mes,"Bitstream is %d channel, %ldHz\n",m_vorbisInfo.channels,m_vorbisInfo.rate);
	OutputDebugString(mes);
#endif
    

	m_convSize = 4096/m_vorbisInfo.channels;

    /* OK, got and parsed all three headers. Initialize the Vorbis
       packet->PCM decoder. */

	vorbis_synthesis_init(&m_vorbisDspState,&m_vorbisInfo); /* central decode state */
	vorbis_block_init(&m_vorbisDspState,&m_vorbisBlock);     /* local state for most of the decode */


//
	m_needRead = FALSE;
	m_needSynth = TRUE;
	m_packetCheckFlag = TRUE;

	return TRUE;	
}




int COggStreamDecoder::Decode(void)
{
//	int eos = 0;
//	int eof = 0;
	int decodeSize = 0;



	BOOL flg = TRUE;
	while (flg)
	{
		if (m_needRead)
		{
//OutputDebugString("*");
			m_buffer=ogg_sync_buffer(&m_oggSyncState,4096);
//			int readSize = fread(m_buffer,sizeof(char),4096,m_file);
			int readSize;
			ReadFile(m_fileHandle,m_buffer,4096,(DWORD*)&readSize,NULL);
			ogg_sync_wrote(&m_oggSyncState,readSize);
			m_needRead = FALSE;

//			if(readSize==0) return 0;//end of file

			int result = ogg_sync_pageout(&m_oggSyncState,&m_oggPage);
			if (result == 0)
			{
				m_needRead = TRUE;
				if(readSize==0) return 0;//end of file
			}
			else if (result < 0)
			{
				MyErrorOut("Corrupt or missing data in bitstream");
			}
			else
			{
				ogg_stream_pagein(&m_oggStreamState,&m_oggPage); /* can safely ignore errors at this point */
				m_packetCheckFlag = TRUE;
				m_needSynth = TRUE;
			}
			continue;
		}
		else
		{
			if (m_packetCheckFlag)
			{
				int result=ogg_stream_packetout(&m_oggStreamState,&m_oggPacket);

				if(result==0)
				{
					m_needRead = TRUE;
					continue;
				}
				else if (result < 0)
				{ /* missing or corrupt data at this page position *//* no reason to complain; already complained above */
				}
				else
				{
					m_packetCheckFlag = FALSE;
				}
			}

			if (m_needSynth)
			{
				if(vorbis_synthesis(&m_vorbisBlock,&m_oggPacket)==0) /* test for success! */
				{
					vorbis_synthesis_blockin(&m_vorbisDspState,&m_vorbisBlock);
					m_needSynth = FALSE;
				}
			}

			float** pcm;

			int samples = vorbis_synthesis_pcmout(&m_vorbisDspState,&pcm);
			if (samples > 0)
			{
				int j;
				int bout=(samples<m_convSize?samples:m_convSize);
				int channels = m_vorbisInfo.channels;
//OutputDebugString("+");


				for(int i=0;i<channels;i++)
				{
					ogg_int16_t* ptr = m_convBuffer+i;
					float* mono=pcm[i];
					for(j=0;j<bout;j++)
					{
						int val=(int)(mono[j]*32767.f);
						if(val>32767)
						{
							val=32767;
//								clipflag=1;
						}
						if(val<-32768)
						{
							val=-32768;
//								clipflag=1;
						}
						*ptr=val;
						ptr += channels;
					}
				}

				decodeSize = sizeof(short) * channels * bout;
				vorbis_synthesis_read(&m_vorbisDspState,bout);
				flg = FALSE;
			}
			else
			{
				m_needSynth = TRUE;
				m_packetCheckFlag = TRUE;
				continue;
			}
		}
	}



/*
	while(!eos)
	{
		while(!eos)
		{
			int result=ogg_sync_pageout(&m_oggSyncState,&m_oggPage);
			if(result==0)break; // need more data 
			if(result<0)
			{
				MyErrorOut("Corrupt or missing data in bitstream");
			}
			else
			{
				ogg_stream_pagein(&m_oggStreamState,&m_oggPage); // can safely ignore errors at this point 

				while(1)
				{
					result=ogg_stream_packetout(&m_oggStreamState,&m_oggPacket);

					if(result==0)break; // need more data 
					
					if(result<0)
					{ // missing or corrupt data at this page position  no reason to complain; already complained above 
					}
					else
					{
						/// we have a packet.  Decode it 
						float** pcm;
						int samples;
		  
						if(vorbis_synthesis(&m_vorbisBlock,&m_oggPacket)==0) // test for success! 
						{
							vorbis_synthesis_blockin(&m_vorbisDspState,&m_vorbisBlock);
						}

						while((samples=vorbis_synthesis_pcmout(&m_vorbisDspState,&pcm))>0)
						{
							int j;
//							int clipflag=0;
							int bout=(samples<m_convSize?samples:m_convSize);
							int channels = m_vorbisInfo.channels;
//char mes2[256];
//sprintf(mes2,"[decode %d]",bout);
//OutputDebugString(mes2);
OutputDebugString("+");

							for(int i=0;i<channels;i++)
							{
								ogg_int16_t* ptr = m_convBuffer+i;
								float* mono=pcm[i];
								for(j=0;j<bout;j++)
								{
									int val=(int)(mono[j]*32767.f);
									if(val>32767)
									{
										val=32767;
//										clipflag=1;
									}
									if(val<-32768)
									{
										val=-32768;
//										clipflag=1;
									}
									*ptr=val;
									ptr += channels;
								}
							}

							eos = 1;

							decodeSize = sizeof(short) * channels * bout;
							vorbis_synthesis_read(&m_vorbisDspState,bout);

							break;
						}	    
					}
					if (eos) break;
				}



				if(ogg_page_eos(&m_oggPage))eos=1;
			}
		}

		if(!eos)
		{
OutputDebugString("R");
			m_buffer=ogg_sync_buffer(&m_oggSyncState,4096);
			int readSize = fread(m_buffer,sizeof(char),4096,m_file);
			ogg_sync_wrote(&m_oggSyncState,readSize);
			if(readSize==0)
			{
				eos = 1;
				eof = 1;
			}
		}
	}
   
	if (eof)
	{
OutputDebugString("EndOfFile");
		EndDecode();
	}
*/

	return decodeSize;
}



void COggStreamDecoder::EndDecode(void)
{
	if (m_decodeStartFlag)
	{
	    ogg_stream_clear(&m_oggStreamState);
  
    /* ogg_page and ogg_packet structs always point to storage in
       libvorbis.  They're never freed or manipulated directly */
    
		vorbis_block_clear(&m_vorbisBlock);
		vorbis_dsp_clear(&m_vorbisDspState);
		vorbis_comment_clear(&m_vorbisComment);
		vorbis_info_clear(&m_vorbisInfo);  /* must be called last */

		ogg_sync_clear(&m_oggSyncState);

		m_decodeStartFlag = FALSE;
	}
}





void COggStreamDecoder::MyErrorOut(LPSTR mes, LPSTR title)
{
	char titleMessage[256];
	if (title != NULL)
	{
		int ln = strlen(title);
		if (ln>254) ln = 254;
		memcpy(titleMessage,title,ln);
		titleMessage[ln] = 0;
		titleMessage[ln+1] = 0;
	}
	else
	{
		char et[] = "ERROR";
		memcpy(titleMessage,et,strlen(et)+1);
	}
//	MessageBox(NULL,mes,titleMessage,MB_OK | MB_ICONEXCLAMATION);
	OutputDebugString(mes);
}



/*_*/

