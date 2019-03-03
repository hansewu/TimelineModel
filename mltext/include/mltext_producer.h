

#ifndef __MLT_EXT_PRODUCER_H__
#define __MLT_EXT_PRODUCER_H__

#include "MltConfig.h"

#include <framework/mlt.h>
#include "MltProperties.h"

namespace Mlt
{
	class Properties;
	class Producer;
	class Service;

	class MLTPP_DECLSPEC ExtProducer 
	{
		private:
			Producer m_Producer;
		public:
			ExtProducer( Producer &producer );
			ExtProducer( ExtProducer &producer );
			virtual ~ExtProducer( );
		//	virtual mlt_producer get_producer( );
			Producer &parent( );
		//	mlt_producer get_parent( );
		//	mlt_service get_service( );
			int seek( int position );
			int seek( const char* time );
			int position( );
			int frame( );
			char* frame_time( mlt_time_format = mlt_time_smpte_df );
			int set_speed( double speed );
			int pause( );
			double get_speed( );
			double get_fps( );
			int set_in_and_out( int in, int out );
			int get_in( );
			int get_out( );
			int get_length( );
			char* get_length_time( mlt_time_format = mlt_time_smpte_df );
			int get_playtime( );
			Producer *cut( int in = 0, int out = -1 );
			bool is_cut( );
			bool is_blank( );
			bool same_clip( Producer &that );
			bool runs_into( Producer &that );
			void optimise( );
			int clear( );

			const char *get_service_name(); //if (!qstrcmp(m_producer->get("mlt_service"), "avformat"))
			const char *get_xml(); //?? QString(m_producer->get("xml")) == "was here"
			char *get_error_info(); //??producer->get_int("error")
			char *get_resource_info();//if (m_producer->get("resource"))
            						//return Util::baseName(QString::fromUtf8(m_producer->get("resource")));

			int get_original_type(); //m_producer->get_int("_original_type") != tractor_type
			char *get_moviemator_info(); // m_producer->get("moviemator")
			
			int  get_force_seekable(); // if (m_producer->get("force_seekable")) {
            						//seekable = m_producer->get_int("force_seekable");
			char *get_mlt_type(); // seekable = !strcmp(m_producer->get("mlt_type"), "mlt_producer");
			int get_seekable(); //			seekable = m_producer->get_int("seekable");

			int get_virtual_clip(); //??? !m_producer->get_int(kShotcutVirtualClip)"moviemator:virtual"
			char *get_detail_info(); //?? result = info->producer->get("moviemator:detail");
			char *get_Caption_info();//??  result = info->producer->get(kShotcutCaptionProperty);
			char *get_hash_info(); //?? if (!info->producer->get(kShotcutHashProperty))
			char *get_transition_info();//??? if (m_producer->get(kShotcutTransitionProperty))
            char *get_track_info();//???if (m_producer->get(kTrackNameProperty))
            					//return tr("for Track: %1").arg(QString::fromUtf8(m_producer->get(kTrackNameProperty)));
			
			double get_warp_speed(); // info->producer->get_double("warp_speed")

			char *get_template_info(); //QString resource(producer->get("moviemator:template"));
			char *get_image_name(); //producer->get("moviemator:imageName")
			char *get_transition_name(); //info->producer->get("moviemator:animationName")

			int get_filter_in_time(); //			    if (producer.get(kFilterInProperty))
        // Shots on the timeline will set the producer to the cut parent.
        // However, we want time-based filters such as fade in/out to use
        // the cut's in/out and not the parent's.
        //return producer.get_int(kFilterInProperty);

			int set_playlist_count(int count); //
			//MLT.producer()->set(kPlaylistIndexProperty, m_model.playlist()->count());
			//MLT.producer()->set(kPlaylistIndexProperty, 0, 0);
			int get_playlist_count();
			//if (info && MLT.producer()->get_int(kPlaylistIndexProperty) == index.row() + 1)
			
			void *get_thumbnail_data();//??? QImage* thumb = (QImage*) parent.get_data(kThumbnailInProperty);
			void set_get_thumbnail_data();//??? m_producer.set(kThumbnailInProperty, new QImage(image), 0, (mlt_destructor) deleteQImage, NULL);

			//kAudioLevelsProperty  ???


	};
}

#endif // __MLT_EXT_PRODUCER_H__
