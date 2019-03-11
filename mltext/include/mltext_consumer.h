

#ifndef __MLT_EXT_CONSUMER_H__
#define __MLT_EXT_CONSUMER_H__

#include "MltConfig.h"

#include <framework/mlt.h>
#include "MltProperties.h"
#include "mltext_consumer_observer.h"

namespace Mlt
{
	class Properties;
	class Producer;
	class Service;

	class MLTPP_DECLSPEC ExtConsumer 
	{
		private:
			Consumer m_Consumer;
			std::list<ConsumerObserver *> m_ConsumerObservers;
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
			void add_consumer_observer( ConsumerObserver *observer );
			void remove_consumer_observer( ConsumerObserver *observer );
			std::list<ConsumerObserver *> consumer_observers();
			
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
			int set_prefill_state(int state, int multi_index = -1); // m_consumer->set("prefill", 1);

			int set_keyer(int item, int multi_index = -1); //???? keyer  m_consumer->set("keyer", property("keyer").toInt());
			int set_progressive(int progressive, int multi_index = -1);

			int set_rescale_method(const char *method, int multi_index = -1);
			
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

			int set_strict_method(const char *method, int multi_index = -1);//MLT.consumer()->set("1.strict", "experimental")
			int set_volume(double volume, int multi_index = -1); //m_consumer->set("volume", volume);
			int set_image_format(const char *image_format, int multi_index = -1);//m_consumer->set("mlt_image_format", "yuv422");
			int set_color_trc(const char *color_trc, int multi_index = -1); //m_consumer->set("color_trc", Settings.playerGamma().toLatin1().constData());
			int set_terminate_on_pause(int enable, int multi_index = -1);//m_consumer->set("terminate_on_pause", 0);
			int set_real_time(int enable, int multi_index = -1);// m_consumer->set("real_time", realTime());
			int set_scrub_audio(int enable, int multi_index = -1);//m_consumer->set("scrub_audio", scrubAudio);
			int set_refresh(int enable, int multi_index = -1);//m_consumer->set("refresh", 1);
		private:
			void listen_event();
			static void on_frame_show(mlt_consumer, void* self, mlt_frame frame);
        
	};

	class MLTPP_DECLSPEC SDLAudioConsumer : public ExtConsumer
	{

		public:
			public:
			SDLAudioConsumer(Profile& profile); //for sdl audio only //reconfigure(bool isMulti)

			virtual ~SDLAudioConsumer( );

	};

	class MLTPP_DECLSPEC AVFormatConsumer : public ExtConsumer
	{

		public:
			public:
			AVFormatConsumer(Profile& profile); 

			virtual ~AVFormatConsumer();
	
			void get_format_list(char **list, int *count);
			void get_acodec_list(char **list, int *count);
			void get_vcodec_list(char **list, int *count);
	};

}

#endif // __MLT_EXT_CONSUMER_H__
