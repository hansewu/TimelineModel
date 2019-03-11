

#ifndef __MLT_EXT_CONSUMER_OBSERVER_H__
#define __MLT_EXT_CONSUMER_OBSERVER_H__

namespace Mlt
{
	class MLTPP_DECLSPEC ConsumerObserver 
	{
		public:
			ConsumerObserver();
			virtual ~ConsumerObserver();

			virtual void on_consumer_thread_create(){}
			virtual void on_consumer_thread_join() {}
			virtual void on_consumer_thread_started() {}
			virtual void on_consumer_thread_stopped() {}
			virtual void on_consumer_frame_show( mlt_frame frame ) {}
			virtual void on_consumer_frame_render(){}
			virtual void on_consumer_stopping() {}
			virtual void on_consumer_stopped() {}
	};
	
}

#endif // __MLT_EXT_CONSUMER_OBSERVER_H__
