

#ifndef __MLT_EXT_PRODUCER_H__
#define __MLT_EXT_PRODUCER_H__


#include "MltConfig.h"

#include <framework/mlt.h>
#include "MltProperties.h"



/** \brief Producer abstract service class
 *
 * A producer is a service that generates audio, video, and metadata.
 * Some day it may also generate text (subtitles). This is not to say
 * a producer "synthesizes," rather that is an origin of data within the
 * service network - that could be through synthesis or reading a stream.
 *
 * \extends mlt_service
 * \event \em producer-changed either service-changed was fired or the timing of the producer changed
 * \properties \em mlt_type the name of the service subclass, e.g. mlt_producer
 * \properties \em mlt_service the name of a producer subclass
 *
 *
 * \properties \em _position the current position of the play head, relative to the in point  已有接口
 * \properties \em _frame the current position of the play head, relative to the beginning of the resource  已有接口
 * \properties \em _speed the current speed factor, where 1.0 is normal  已有接口
 *
 * \properties \em aspect_ratio sample aspect ratio
 *
 * \properties \em length the duration of the cut in frames  已有接口
 *
 * \properties \em eof the end-of-file behavior, one of: pause, continue, loop
 *
 * \properties \em resource the file name, stream address, or the class name in angle brackets
 *
 * \properties \em _cut set if this producer is a "cut" producer  已有接口
 *
 * \properties \em mlt_mix stores the data for a "mix" producer
 *
 * \properties \em _cut_parent holds a reference to the cut's parent producer  有接口
 *
 * \properties \em ignore_points Set this to temporarily disable the in and out points.
 *
 * \properties \em use_clone holds a reference to a clone's producer, as created by mlt_producer_optimise   上层没用
 *
 * \properties \em _clone is the index of the clone in the list of clones stored on the clone's producer  上层没用
 * \properties \em _clones is the number of clones of the producer, as created by mlt_producer_optimise  上层没用
 * \properties \em _clone.{N} holds a reference to the N'th clone of the producer, as created by mlt_producer_optimise 上层没用
 *
 * \properties \em meta.* holds metadata - there is a loose taxonomy to be defined
 *
 * \properties \em set.* holds properties to set on a frame produced
 * \envvar \em MLT_DEFAULT_PRODUCER_LENGTH - the default duration of the producer in frames, defaults to 15000.
 * Most producers will set the producer length to something appropriate
 * like the real duration of an audio or video clip. However, some other things
 * like still images and generators do not have an intrinsic length besides one
 * or infinity. Those producers tend to not override the default length and one
 * expect the app or user to set the length. The default value of 15000 was chosen
 * to provide something useful - not too long or short and convenient to simply
 * set an out point without necessarily nedding to extend the length.
 * \todo define the media metadata taxonomy
 */

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
			void set_service_name(const char *service_name);//p.set("mlt_service", "avformat-novalidate");

			const char *get_xml(); //?? QString(m_producer->get("xml")) == "was here"
			
			char *get_resource_info();//if (m_producer->get("resource"))
            						//return Util::baseName(QString::fromUtf8(m_producer->get("resource")));
                        void set_resource(const char *resouce);//?? producer->set("resource", meta->name().toUtf8().constData());

			int get_original_type(); //m_producer->get_int("_original_type") != tractor_type
			
			char *get_mlt_type(); // seekable = !strcmp(m_producer->get("mlt_type"), "mlt_producer");
                        void set_mlt_type(const char *mlt_type);//?? MLT.producer()->set("mlt_type", "mlt_producer");

			int get_seekable(); //			seekable = m_producer->get_int("seekable");
			
                        double get_warp_speed(); //?? info->producer->get_double("warp_speed")  producer_timewarp

                        void set_aspect_ratio(double aspect_ratio);//sample aspect ratio
                        double get_aspect_ratio();//mlt_properties_set_double( properties, "aspect_ratio", mlt_properties_get_double( parent_props, "aspect_ratio" ) );

                        void set_eof_state(const char *eof_state);//mlt_properties_set( properties, "eof", "pause" );
                        const char *get_eof_state();

                        void *get_mlt_mix(*length = NULL);//??
                        void set_mlt_mix(void *data, int length=0);

                        void *get_mlt_mix_in(*length = NULL);//??
                        void set_mlt_mix_in(void *data, int length=0);

                        void *get_mlt_mix_out(*length = NULL);//??
                        void set_mlt_mix_out(void *data, int length=0);

                        const char *get_id();//?? //QString(info->producer->get("id")) == "black"
/*
                    if (clip->parent().get_data("mlt_mix"))
                    clip->parent().set("mlt_mix", NULL, 0);

                if (clip->get_data("mix_in"))
                    clip->set("mix_in", NULL, 0);

                if (clip->get_data("mix_out"))
                    clip->set("mix_out", NULL, 0);

*/
                        //Set this to temporarily disable the in and out points
                        int get_ignore_points();//?? //mlt_properties_get_int( properties, "ignore_points" );//MLT.producer()->set("ignore_points", 1);
                        void set_ignore_points(int ignore_points);

                        void set_length_direct(int length);// MLT.producer()->set("length", length);//mlt_producer_get_length  但没有直接的设置接口

                        void set_mute_on_pause(int state); //p.set("mute_on_pause", 0);  //avformat  avformat-novalidate

                        int get_ttl(); //???? if (m_tempProducer->get_int("ttl"))

                        const char *get_force_aspect_ratio(); //??
                        void set_force_aspect_ratio(const char *ratio); //??
                        //if (m_tempProducer->get("force_aspect_ratio") || new_sar != sar) {
                          //  m_tempProducer->set("force_aspect_ratio", QString::number(new_sar).toLatin1().constData());

                        //* \properties \em set.* holds properties to set on a frame produced
                        void set_frame_test_audio(int state);//            info->producer->set("set.test_audio", 0);

                        //holds metadata - there is a loose taxonomy to be defined
                        int get_meta_fx_cut(); // ???
                        void set_meta_fx_cut(int fx_cut);//               producer->get_int("meta.fx_cut")          producer->set("meta.fx_cut", 1);

                        int get_media_stream_count(); //int n = m_tempProducer->get_int("meta.media.nb_streams");  //avformat
                        int get_media_width();
                        int get_media_height();
                        double get_media_aspect_num();
                        double get_media_aspect_den();
                    //double new_sar = double(ui->aspectNumSpinBox->value() * m_tempProducer->get_int("meta.media.height")) /
                                //double(ui->aspectDenSpinBox->value() * m_tempProducer->get_int("meta.media.width"));
                                   //double sar = m_tempProducer->get_double("meta.media.sample_aspect_num");
                        //if (m_tempProducer->get_double("meta.media.sample_aspect_den") > 0)


    };

        class MLTPP_DECLSPEC ExtExProducer ： public ExtProducer
        {
        public:
                ExtExProducer( ExtProducer &producer );
                ExtExProducer( ExtExProducer &producer );
                virtual ~ExtExProducer( );

                //扩展的PRODUCER暂时允许直接用键值访问
                void set_property(const char *key, int value);
                void set_property(const char *key, const char *value);
                int get_property(const char *key);
                //AVFORMAT
                //    m_tempProducer->set("audio_index", ui->audioTrackComboBox->itemData(index).toInt());
                  //      m_tempProducer->set("video_index", ui->videoTrackComboBox->itemData(index).toInt());
                  //  int progressive = m_tempProducer->get_int("meta.media.progressive");
                 //   m_tempProducer->set("force_progressive", QString::number(index).toLatin1().constData());
                   //         int tff = m_tempProducer->get_int("meta.media.top_field_first");
                  //  m_tempProducer->set("force_tff", QString::number(index).toLatin1().constData());
                    //    m_tempProducer->set("video_delay", double(value) / 1000);

        };



}

#endif // __MLT_EXT_PRODUCER_H__



/*
 *
 *
//image producer
 //   ui->aspectNumSpinBox->setValue(p->get_int(kAspectRatioNumerator));
 //   ui->aspectDenSpinBox->setValue(p->get_int(kAspectRatioDenominator));

    //    m_tempProducer->set(kAspectRatioNumerator, ui->aspectNumSpinBox->text().toLatin1().constData());
    //    m_tempProducer->set(kAspectRatioDenominator, ui->aspectDenSpinBox->text().toLatin1().constData());
char *get_error_info(); //??producer->get_int("error")
                        int  get_force_seekable(); // if (m_producer->get("force_seekable")) {
                                                        //seekable = m_producer->get_int("force_seekable");
*/
                        /*
                        char *get_moviemator_info(); // m_producer->get("moviemator")
                        int get_virtual_clip(); //??? !m_producer->get_int(kShotcutVirtualClip)"moviemator:virtual"
                        char *get_detail_info(); //?? result = info->producer->get("moviemator:detail");
                        char *get_Caption_info();//??  result = info->producer->get(kShotcutCaptionProperty);
                        char *get_hash_info(); //?? if (!info->producer->get(kShotcutHashProperty))
                        char *get_transition_info();//??? if (m_producer->get(kShotcutTransitionProperty))
            char *get_track_info();//???if (m_producer->get(kTrackNameProperty))
                                                //return tr("for Track: %1").arg(QString::fromUtf8(m_producer->get(kTrackNameProperty)));
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

                         info->producer->set(kFilterInProperty, info->frame_in);
        info->producer->set(kFilterOutProperty, info->frame_out);
if (producer.get(kFilterInProperty))
        // Shots on the timeline will set the producer to the cut parent.
        // However, we want time-based filters such as fade in/out to use
        // the cut's in/out and not the parent's.
        return producer.get_int(kFilterInProperty);

producer->get_int(kMultitrackItemProperty)
p->set(kMultitrackItemProperty, producer->get(kMultitrackItemProperty));

//ui->notesTextEdit->setPlainText(QString::fromUtf8(m_tempProducer->get(kCommentProperty)));  //avformat

//MLT.producer()->get_int(kBackgroundCaptureProperty)  //Avfoundation

                        */
