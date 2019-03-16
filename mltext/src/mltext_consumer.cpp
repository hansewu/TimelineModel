#include <stdlib.h>
#include <string.h>

#include <mltext_consumer.h>
using namespace Mlt;

typedef void* ( *thread_function_t )( void* );

static void on_consumer_frame_show( mlt_properties owner, ExtConsumer* self, mlt_frame frame );
static void on_consumer_frame_render( mlt_properties owner, ExtConsumer* self, mlt_frame frame );
static void on_thread_create(mlt_properties owner, ExtConsumer* self, void** thread, int* priority, thread_function_t function, void* data );
static void on_thread_join(mlt_properties owner, ExtConsumer* self, void* thread);
static void on_thread_started(mlt_properties owner, ExtConsumer* self);
static void on_thread_stopped(mlt_properties owner, ExtConsumer* self);
static void on_consumer_stopping();
static void on_consumer_stopped();

//consumer-frame-show litsener
void on_consumer_frame_show( mlt_properties owner, ExtConsumer* self, mlt_frame frame)
{
	std::list<ConsumerObserver *> observers = self->consumer_observers();
	std::list<ConsumerObserver *>::iterator iter = observers.begin();
	while (iter != observers.end())
	{
		(*iter)->on_consumer_frame_show(frame);
	}
}

//consumer-frame-render litsener
void on_consumer_frame_render( mlt_properties owner, ExtConsumer* self, mlt_frame frame )
{

}

//consumer-thread-create litsener
void on_thread_create(mlt_properties owner, ExtConsumer* self,
    void** thread, int* priority, thread_function_t function, void* data )
{

}

//consumer-thread-join litsener
void on_thread_join(mlt_properties owner, ExtConsumer* self, void* thread)
{

}

//consumer-thread-started litsener
void on_thread_started(mlt_properties owner, ExtConsumer* self)
{

}

//consumer-thread-stopped litsener
void on_thread_stopped(mlt_properties owner, ExtConsumer* self)
{

}

//consumer-stopping litsener
void on_consumer_stopping()
{

}

//consumer-stopped litsener
void on_consumer_stopped()
{

}


ExtConsumer::ExtConsumer()
{
	m_Consumer = new Mlt::Consumer();
}

ExtConsumer::ExtConsumer(bool isMulti) //for sdl audio only
{
	if (isMulti)
		m_Consumer = new Mlt::Consumer();
	else
		m_Consumer = new Mlt::Consumer();
}

ExtConsumer::ExtConsumer( Profile& profile )
{
	m_Consumer = new Mlt::Consumer(profile);
}

ExtConsumer::ExtConsumer( Profile& profile, const char *id , const char *service )
{
	m_Consumer = new Mlt::Consumer(profile, id, service);
}

ExtConsumer::ExtConsumer( Service &consumer )
{
	m_Consumer = new Mlt::Consumer(consumer);
}

ExtConsumer::ExtConsumer( ExtConsumer &consumer )
{

}
//	ExtConsumer( mlt_consumer consumer );
ExtConsumer::~ExtConsumer( )
{
	if (m_Consumer)
		delete m_Consumer;
}
//	virtual mlt_consumer get_consumer( );
//	mlt_service get_service( );

void ExtConsumer::listen_event()
{
	m_Consumer->listen("consumer-frame-show", this, (mlt_listener) on_consumer_frame_show);
	m_Consumer->listen("consumer-frame-render", this, (mlt_listener) on_consumer_frame_render);
	m_Consumer->listen("consumer-thread-create", this, (mlt_listener) on_thread_create);
	m_Consumer->listen("consumer-thread-join", this, (mlt_listener) on_thread_join);
	m_Consumer->listen("consumer-thread-started", this, (mlt_listener) on_thread_started);
	m_Consumer->listen("consumer-thread-stopped", this, (mlt_listener) on_thread_stopped);
	m_Consumer->listen("consumer-stopping", this, (mlt_listener) on_consumer_stopping);
	m_Consumer->listen("consumer-stopped", this, (mlt_listener) on_consumer_stopped);
}

void ExtConsumer::add_consumer_observer( ConsumerObserver *observer )
{
	m_ConsumerObservers.push_back(observer);
}

void ExtConsumer::remove_consumer_observer( ConsumerObserver *observer )
{
	m_ConsumerObservers.remove(observer);
}

std::list<Mlt::ConsumerObserver *> ExtConsumer::consumer_observers()
{
	return m_ConsumerObservers;
}

int ExtConsumer::connect( Service &service )
{
	return m_Consumer->connect(service);
}

int ExtConsumer::run( )
{
	return m_Consumer->run();
}

int ExtConsumer::start( )
{
	return m_Consumer->start();
}

void ExtConsumer::purge( )
{
	m_Consumer->purge();
}

int ExtConsumer::stop( )
{
	return m_Consumer->stop();
}

bool ExtConsumer::is_stopped( )
{
	return m_Consumer->is_stopped();
}

int ExtConsumer::position( )
{
	return m_Consumer->position();
}

int ExtConsumer::set_multi_consumer(int multi_index, const char *consumer_name)//MLT.consumer()->set("1", "avformat");
{
	char idx[8];
	sprintf(idx, "%d", multi_index);
	m_Consumer->set(idx, consumer_name);
	return 0;
}


int ExtConsumer::set_audio_buffer(int size, int multi_index)
{
	if (multi_index < 0)
		m_Consumer->set("audio_buffer", size);
	else
	{
		char name[20];
		sprintf(name, "%d.audio_buffer", multi_index);
		m_Consumer->set(name, size);
	}

	return 0;
}
			/*
#ifdef Q_OS_WIN
                m_consumer->set("0.audio_buffer", 2048);
#else
                m_consumer->set("0.audio_buffer", 512);
#endif
*/
int ExtConsumer::set_buffer(int count, int multi_index)   //m_consumer->set("buffer", 25);
{
	if (multi_index < 0)
		m_Consumer->set("buffer", count);
	else
	{
		char name[20];
		sprintf(name, "%d.buffer", multi_index);
		m_Consumer->set(name, count);
	}

	return 0;
}

int ExtConsumer::set_deinterlace_method(const char* method, int multi_index)//MLT.consumer()->set("deinterlace_method", method);
{
	if (multi_index < 0)
		m_Consumer->set("deinterlace_method", method);
	else
	{
		char name[20];
		sprintf(name, "%d.deinterlace_method", multi_index);
		m_Consumer->set(name, method);
	}

	return 0;
}

int ExtConsumer::set_target_name(const char *name, int multi_index) //MLT.consumer()->set("1.target", target.toUtf8().constData());
{
	if (multi_index < 0)
		m_Consumer->set("target", name);
	else
	{
		char key[20];
		sprintf(key, "%d.target", multi_index);
		m_Consumer->set(key, name);
	}

	return 0;
}

int ExtConsumer::set_prefill_state(int state, int multi_index) // m_consumer->set("prefill", 1);
{
	if (multi_index < 0)
		m_Consumer->set("prefill", state);
	else
	{
		char key[20];
		sprintf(key, "%d.prefill", multi_index);
		m_Consumer->set(key, state);
	}

	return 0;
}

int ExtConsumer::set_keyer(int item, int multi_index) //???? keyer  m_consumer->set("keyer", property("keyer").toInt());
{
	if (multi_index < 0)
		m_Consumer->set("keyer", item);
	else
	{
		char key[20];
		sprintf(key, "%d.keyer", multi_index);
		m_Consumer->set(key, item);
	}

	return 0;
}

int ExtConsumer::set_progressive(int progressive, int multi_index)
{
	if (multi_index < 0)
		m_Consumer->set("progressive", progressive);
	else
	{
		char key[20];
		sprintf(key, "%d.progressive", multi_index);
		m_Consumer->set(key, progressive);
	}

	return 0;
}

int ExtConsumer::set_rescale_method(const char *method, int multi_index)
{
	if (multi_index < 0)
		m_Consumer->set("rescale", method);
	else
	{
		char key[20];
		sprintf(key, "%d.rescale", multi_index);
		m_Consumer->set(key, method);
	}

	return 0;
}

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

int ExtConsumer::set_strict_method(const char *method, int multi_index)//MLT.consumer()->set("1.strict", "experimental")
{
	if (multi_index < 0)
		m_Consumer->set("strict", method);
	else
	{
		char key[20];
		sprintf(key, "%d.strict", multi_index);
		m_Consumer->set(key, method);
	}

	return 0;
}

int ExtConsumer::set_volume(double volume, int multi_index) //m_consumer->set("volume", volume);
{
	if (multi_index < 0)
		m_Consumer->set("volume", volume);
	else
	{
		char key[20];
		sprintf(key, "%d.volume", multi_index);
		m_Consumer->set(key, volume);
	}

	return 0;
}

int ExtConsumer::set_image_format(const char *image_format, int multi_index)//m_consumer->set("mlt_image_format", "yuv422");
{
	if (multi_index < 0)
		m_Consumer->set("mlt_image_format", image_format);
	else
	{
		char key[20];
		sprintf(key, "%d.mlt_image_format", multi_index);
		m_Consumer->set(key, image_format);
	}

	return 0;
}

int ExtConsumer::set_color_trc(const char *color_trc, int multi_index)//m_consumer->set("color_trc", Settings.playerGamma().toLatin1().constData());
{
	if (multi_index < 0)
		m_Consumer->set("color_trc", color_trc);
	else
	{
		char key[20];
		sprintf(key, "%d.color_trc", multi_index);
		m_Consumer->set(key, color_trc);
	}

	return 0;
}

int ExtConsumer::set_terminate_on_pause(int enable, int multi_index)//m_consumer->set("terminate_on_pause", 0);
{
	if (multi_index < 0)
		m_Consumer->set("terminate_on_pause", enable);
	else
	{
		char key[20];
		sprintf(key, "%d.terminate_on_pause", multi_index);
		m_Consumer->set(key, enable);
	}

	return 0;
}

int ExtConsumer::set_real_time(int enable, int multi_index)// m_consumer->set("real_time", realTime());
{
	if (multi_index < 0)
		m_Consumer->set("terminate_on_pause", enable);
	else
	{
		char key[20];
		sprintf(key, "%d.terminate_on_pause", multi_index);
		m_Consumer->set(key, enable);
	}

	return 0;
}

int ExtConsumer::set_scrub_audio(int enable, int multi_index)//m_consumer->set("scrub_audio", scrubAudio);
{
	if (multi_index < 0)
		m_Consumer->set("scrub_audio", enable);
	else
	{
		char key[20];
		sprintf(key, "%d.scrub_audio", multi_index);
		m_Consumer->set(key, enable);
	}

	return 0;
}

int ExtConsumer::set_refresh(int enable, int multi_index)//m_consumer->set("refresh", 1);
{
	if (multi_index < 0)
		m_Consumer->set("refresh", enable);
	else
	{
		char key[20];
		sprintf(key, "%d.refresh", multi_index);
		m_Consumer->set(key, enable);
	}

	return 0;
}



////////////////////////////////////////////////////////////
//SDLAudioConsumer implementation
///////////////////////////////////////////////////////////
SDLAudioConsumer::SDLAudioConsumer(Profile& profile) : ExtConsumer(profile, "sdl_audio")
{

}
SDLAudioConsumer::~SDLAudioConsumer()
{

}




////////////////////////////////////////////////////////////
//AVFormatConsumer implementation
///////////////////////////////////////////////////////////
AVFormatConsumer::AVFormatConsumer(Profile& profile) : ExtConsumer(profile, "avformat")
{

}

AVFormatConsumer::~AVFormatConsumer()
{

}

void AVFormatConsumer::get_format_list(char **list, int *count)
{
	Mlt::Profile profile;
	Mlt::Consumer c(profile, "avformat");
	if (c.is_valid())
	{
	    c.set("f", "list");
	    c.set("acodec", "list");
	    c.set("vcodec", "list");
	    c.start();
	    c.stop();

	    Mlt::Properties* p = new Mlt::Properties(c.get_data("f"));
	    int nCount = p->count();
		if (nCount > 0)
		{
			*count = nCount;
			list = (char**)malloc(nCount * sizeof(char*));
		    for (int i = 0; i < nCount; i++)
		    {
		    	list[i] = (char *)malloc(32*sizeof(char));
		    	strcpy(list[i], p->get(i));
		    }
		    delete p;
		}
	}
}

void AVFormatConsumer::get_acodec_list(char **list, int *count)
{

}

void AVFormatConsumer::get_vcodec_list(char **list, int *count)
{

}