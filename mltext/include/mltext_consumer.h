

#ifndef __MLT_EXT_CONSUMER_H__
#define __MLT_EXT_CONSUMER_H__

#include "MltConfig.h"

#include <framework/mlt.h>
#include "MltProperties.h"

namespace Mlt
{
	class Properties;
	class Producer;
	class Service;

	class MLTPP_DECLSPEC ExtConsumer 
	{
		private:
			Consumer m_Consumer;
		public:
			public:
			ExtConsumer( );
			ExtConssumer(bool isMulti); //for sdl audio only
			ExtConsumer( Profile& profile );
			ExtConsumer( Profile& profile, const char *id , const char *service = NULL );
			ExtConsumer( Service &consumer );
			ExtConsumer( ExtConsumer &consumer );
		//	ExtConsumer( mlt_consumer consumer );
			virtual ~Consumer( );
		//	virtual mlt_consumer get_consumer( );
		//	mlt_service get_service( );
			virtual int connect( Service &service );
			int run( );
			int start( );
			void purge( );
			int stop( );
			bool is_stopped( );
			int position( );

			int set_multi_consumer(int multi_index, const char *consumer_name);//MLT.consumer()->set("1", "avformat");
			
			int set_audio_buffer(int size, int multi_index = -1);
			/*
#ifdef Q_OS_WIN
                m_consumer->set("0.audio_buffer", 2048);
#else
                m_consumer->set("0.audio_buffer", 512);
#endif
*/
			int set_buffer(int count, int multi_index = -1);   //m_consumer->set("buffer", 25);
			int set_deinterlace_method(const char* method, int multi_index = -1);//MLT.consumer()->set("deinterlace_method", method);
			int set_target_name(const char *name, int multi_index = -1); //MLT.consumer()->set("1.target", target.toUtf8().constData());
			int set_prefill_state(int state); // m_consumer->set("prefill", 1);

			int set_keyer(int item); //???? keyer  m_consumer->set("keyer", property("keyer").toInt());
			int set_progressive(int progressive);

			int set_rescale_method(const char *method);
			
			/*
			                p->set("rescale", "nearest");
                break;
            case 1:
                p->set("rescale", "bilinear");
                break;
            case 2:
                p->set("rescale", "bicubic");
                break;
            default:
                p->set("rescale", "hyper");*/

			int set_strict_method(const char *method);//MLT.consumer()->set("1.strict", "experimental")
			int set_volume(double volume); //m_consumer->set("volume", volume);
			int set_image_format(const char *image_format);//m_consumer->set("mlt_image_format", "yuv422");
			int set_color_trc(const char *color_trc); //m_consumer->set("color_trc", Settings.playerGamma().toLatin1().constData());
			int set_terminate_on_pause(int enable);//m_consumer->set("terminate_on_pause", 0);
			int set_real_time(int enable);// m_consumer->set("real_time", realTime());
			int set_scrub_audio(int enable);//m_consumer->set("scrub_audio", scrubAudio);
			int set_refresh(int enable);//m_consumer->set("refresh", 1);

			
        
	};

	class MLTPP_DECLSPEC SDLAudioConsumer : public ExtConsumer
	{

		public:
			public:
			SDLAudioConsumer(bool isMulti); //for sdl audio only //reconfigure(bool isMulti)

			virtual ~SDLAudioConsumer( );

	};


}

#endif // __MLT_EXT_CONSUMER_H__
