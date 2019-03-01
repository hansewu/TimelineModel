

#ifndef __MLT_EXT_TRANSITION_H__
#define __MLT_EXT_TRANSITION_H__

#include "MltConfig.h"

#include <framework/mlt.h>
#include "MltProperties.h"

namespace Mlt
{
	class Properties;
	class Producer;
	class Service;

	class MLTPP_DECLSPEC ExtTransition 
	{
		private:
			Transition m_Transition;
		public:

			ExtTransition( Profile& profile, const char *id, const char *arg = NULL );
			ExtTransition( Service &transition );
			ExtTransition( Transition &transition );
			ExtTransition( mlt_transition transition );

			ExtTransitionn( ExtTransitionn &transition );
			virtual ~Transition( );
			//virtual mlt_transition get_transition( );
			//mlt_service get_service( );

			void set_in_and_out( int in, int out );
			void set_tracks( int a_track, int b_track );
			int connect( Producer &producer, int a_track, int b_track );
			int get_a_track( );
			int get_b_track( );
			int get_in( );
			int get_out( );
			int get_length( );
			int get_position( Frame &frame );
			double get_progress( Frame &frame );
			double get_progress_delta( Frame &frame );

			void disable();//transition->set("disable", (composite == Qt::Unchecked));
			int set_resouce(const char *resource);
//            transition->set("resource", "");
            //transition->set("resource", QString("%luma%1.pgm").arg(transitionIndex - 1, 2, 10, QChar('0')).toLatin1().constData());
        	const char *get_resouce();

			int set_progressive(int progressive);//transition->set("progressive", 1);
			int set_invert(int enable);//transition->set("invert", 0);
			int set_softness(int softness);//transition->set("softness", 0);
			int set_a_track(int a_track);//transition->set("a_track", a_track);


	};
}

#endif // __MLT_EXT_TRANSITION_H__
