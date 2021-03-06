#if !defined __NYANLIB_LIBINCLUDE__
#define __NYANLIB_LIBINCLUDE__




#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"imm32.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"ddraw.lib")
#pragma comment(lib,"dsound.lib")
//#pragma comment(lib,"dsetup.lib")


#if defined _TINYAN3DLIB_
//3dlib

	#pragma comment(lib,"d3d9.lib")
	#pragma comment(lib,"d3dx9.lib")
	#pragma comment(lib,"dxerr9.lib")


	#if defined _DEBUG
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyan3DLibD.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGraphics3DLibD.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanPicture3DLibD.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGeo3DLibD.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffect3DLibD.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanWipe3DLibD.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanDirectX3DLibD.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanlib\\lib\\nnnUtil3DLibD.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnMiniGame3DLibD.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnn3DLibD.lib")

	#else
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyan3DLib.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGraphics3DLib.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanPicture3DLib.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGeo3DLib.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffect3DLib.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanWipe3DLib.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanDirectX3DLib.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanlib\\lib\\nnnUtil3DLib.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnMiniGame3DLib.lib")
		#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnn3DLib.lib")
	#endif

	#if _MSC_VER >= 1500
			#pragma comment(lib,"rpcrt4.lib")
	#endif

#else
//2dlib

	#if _MSC_VER >= 1700

		#if defined _DEBUG
/*
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGraphicsLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanPictureLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGeoLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectLib2012D.lib")

			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectNaturalLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectCharaLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectSpecialLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectScreenLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectWipeLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectGeoLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectTransformLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectMoveLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectAnimeLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectEtcLib2012D.lib")

			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanWipeLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanDirectXLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanlib\\lib\\nnnUtilLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnMiniGameLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnLib2012D.lib")
		#else
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGraphicsLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanPictureLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGeoLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectLib2012.lib")

			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectNaturalLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectCharaLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectSpecialLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectScreenLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectWipeLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectGeoLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectTransformLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectMoveLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectAnimeLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectEtcLib2012.lib")

			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanWipeLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanDirectXLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnUtilLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnMiniGameLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnLib2012.lib")
*/

			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanGraphicsLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanPictureLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanGeoLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectLib2012D.lib")

			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectNaturalLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectCharaLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectSpecialLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectScreenLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectWipeLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectGeoLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectTransformLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectMoveLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectAnimeLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectEtcLib2012D.lib")

			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanWipeLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanDirectXLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nnnUtilLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nnnMiniGameLib2012D.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nnnLib2012D.lib")
		#else
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanGraphicsLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanPictureLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanGeoLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectLib2012.lib")

			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectNaturalLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectCharaLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectSpecialLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectScreenLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectWipeLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectGeoLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectTransformLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectMoveLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectAnimeLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanEffectEtcLib2012.lib")

			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanWipeLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nyanDirectXLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nnnUtilLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nnnMiniGameLib2012.lib")
			#pragma comment(lib,"..\\..\\systemNNNLib\\nnnLib2012.lib")

		#endif

			#pragma comment(lib,"rpcrt4.lib")

	#else

		#if _MSC_VER >= 1500

			#if defined _DEBUG
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanLib2008D.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGraphicsLib2008D.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanPictureLib2008D.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGeoLib2008D.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectLib2008D.lib")

				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectNaturalLib2008D.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectCharaLib2008D.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectSpecialLib2008D.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectScreenLib2008D.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectWipeLib2008D.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectGeoLib2008D.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectTransformLib2008D.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectMoveLib2008D.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectAnimeLib2008D.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectEtcLib2008D.lib")

				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanWipeLib2008D.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanDirectXLib2008D.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanlib\\lib\\nnnUtilLib2008D.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnMiniGameLib2008D.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnLib2008D.lib")
			#else
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanLib2008.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGraphicsLib2008.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanPictureLib2008.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGeoLib2008.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectLib2008.lib")

				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectNaturalLib2008.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectCharaLib2008.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectSpecialLib2008.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectScreenLib2008.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectWipeLib2008.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectGeoLib2008.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectTransformLib2008.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectMoveLib2008.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectAnimeLib2008.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectEtcLib2008.lib")

				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanWipeLib2008.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanDirectXLib2008.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnUtilLib2008.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnMiniGameLib2008.lib")
				#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnLib2008.lib")
			#endif

				#pragma comment(lib,"rpcrt4.lib")

		#else

			#if _MSC_VER >= 1400

				#if defined _DEBUG
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanLib2005D.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGraphicsLib2005D.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanPictureLib2005D.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGeoLib2005D.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectLib2005D.lib")

					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectNaturalLib2005D.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectCharaLib2005D.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectSpecialLib2005D.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectScreenLib2005D.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectWipeLib2005D.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectGeoLib2005D.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectTransformLib2005D.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectMoveLib2005D.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectAnimeLib2005D.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectEtcLib2005D.lib")

					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanWipeLib2005D.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanDirectXLib2005D.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanlib\\lib\\nnnUtilLib2005D.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnMiniGameLib2005D.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnLib2005D.lib")
				#else
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanLib2005.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGraphicsLib2005.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanPictureLib2005.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGeoLib2005.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectLib2005.lib")

					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectNaturalLib2005.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectCharaLib2005.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectSpecialLib2005.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectScreenLib2005.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectWipeLib2005.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectGeoLib2005.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectTransformLib2005.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectMoveLib2005.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectAnimeLib2005.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectEtcLib2005.lib")

					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanWipeLib2005.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanDirectXLib2005.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnUtilLib2005.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnMiniGameLib2005.lib")
					#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnLib2005.lib")
				#endif
			#else

				#if !defined _MT

					#if defined _DEBUG
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanLibD.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGraphicsLibD.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanPictureLibD.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGeoLibD.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectLibD.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanWipeLibD.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanDirectXLibD.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnUtilLibD.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnMiniGameLibD.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnLibD.lib")
					#else
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanLib.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGraphicsLib.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanPictureLib.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGeoLib.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectLib.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanWipeLib.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanDirectXLib.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnUtilLib.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnMiniGameLib.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnLib.lib")
					#endif

				#else

					#if defined _DEBUG
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanLibDM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGraphicsLibDM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanPictureLibDM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGeoLibDM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectLibDM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanWipeLibDM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanDirectXLibDM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnUtilLibDM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnMiniGameLibDM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnLibDM.lib")
					#else
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanLibM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGraphicsLibM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanPictureLibM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanGeoLibM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanEffectLibM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanWipeLibM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nyanDirectXLibM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnUtilLibM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnMiniGameLibM.lib")
						#pragma comment(lib,"..\\..\\systemNNN\\nyanLib\\lib\\nnnLibM.lib")
					#endif

				#endif
			#endif
		#endif
	#endif
#endif


#if !defined _MT

	#if defined _DEBUG
	#pragma comment(lib,"libogg_static_d.lib")
	#pragma comment(lib,"libvorbis_static_d.lib")
//	#pragma comment(lib,"ogg_d.lib")
//	#pragma comment(lib,"vorbis_d.lib")
	#else
	#pragma comment(lib,"libogg_static.lib")
	#pragma comment(lib,"libvorbis_static.lib")
	//#pragma comment(lib,"ogg.lib")
	//#pragma comment(lib,"vorbis.lib")
	#endif

#else

	#if defined _DEBUG
	#pragma comment(lib,"libogg_static_d.lib")
	#pragma comment(lib,"libvorbis_static_d.lib")
//	#pragma comment(lib,"ogg_d.lib")
//	#pragma comment(lib,"vorbis_d.lib")
	#else
	#pragma comment(lib,"libogg_static.lib")
	#pragma comment(lib,"libvorbis_static.lib")
	//#pragma comment(lib,"ogg.lib")
	//#pragma comment(lib,"vorbis.lib")
	#endif

#endif


#pragma comment(lib,"Strmiids.lib")
//#pragma comment(lib,"xp32_strmbasd_d.lib")

#endif
/*_*/

