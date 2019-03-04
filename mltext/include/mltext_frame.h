

#ifndef __MLT_EXT_FRAME_H__
#define __MLT_EXT_FRAME_H__

#include "MltConfig.h"

#include <framework/mlt.h>
#include "MltProperties.h"

namespace Mlt
{
	class Properties;
	class Producer;
	class Service;

	class MLTPP_DECLSPEC ExtFrame 
	{
		private:
			Frame m_Frame;
		public:
			ExtFrame();
			
			ExtFrame( Frame &frame );
			ExtFrame( const Frame &frame );
			virtual ~ExtFrame( );

			ExtFrame& operator=( const ExtFrame &frame );

			set_movit_use_texture(int use_texture);//frame.set("movit.convert.use_texture", 1);
            //frame->set("rescale.interp", "bilinear");
            //frame->set("deinterlace_method", "onefield");
            //frame->set("top_field_first", -1);

			uint8_t *get_image( mlt_image_format &format, int &w, int &h, int writable = 0 );
			unsigned char *fetch_image( mlt_image_format format, int w, int h, int writable = 0 );
			void *get_audio( mlt_audio_format &format, int &frequency, int &channels, int &samples );
			unsigned char *get_waveform( int w, int h );

			Producer *get_original_producer( );
			int get_position( );

			int is_test_audio(); //frame->get_int("test_audio")
			unsigned char *get_alpha_data(); //data = d->f.get_data("alpha", size );

			int get_rendered_state(); //frame.get_int("rendered")
			int get_image_format(); // (mlt_image_format)d->f.get_int( "format" );
			mlt_audio_format get_audio_format() const;
			//return (mlt_audio_format)d->f.get_int( "audio_format" );

			double get_audio_level(int index); 
			//const char* key[2] = { "meta.media.audio_level.0", "meta.media.audio_level.1"};
			//frame->get_double(key[channel])

			int get_image_width() const
		    //return d->f.get_int( "width" );

			int get_image_height() const
    		//return d->f.get_int( "height" );

			int get_audio_channels() const
    		//return d->f.get_int( "audio_channels" );

			int get_audio_frequency() const
    		//return d->f.get_int( "audio_frequency" );

			int get_audio_samples() const
    		//return d->f.get_int( "audio_samples" );


			//virtual mlt_frame get_frame( );
			//mlt_properties get_properties( );

			//mlt_properties get_unique_properties( Service &service );
			//int set_image( uint8_t *image, int size, mlt_destructor destroy );
			//int set_alpha( uint8_t *alpha, int size, mlt_destructor destroy );



	};
}

#endif // __MLT_EXT_FRAME_H__
