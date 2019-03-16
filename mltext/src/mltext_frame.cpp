
#include <mltext_frame.h>
using namespace Mlt;

ExtFrame::ExtFrame()
{
	
}

ExtFrame::ExtFrame( Frame &frame )
{

}

ExtFrame::ExtFrame( const Frame &frame )
{

}

ExtFrame::~ExtFrame( )
{

}

ExtFrame& ExtFrame::operator=( const ExtFrame &frame )
{
	return *this;
}

void ExtFrame::set_movit_use_texture(int use_texture)//frame.set("movit.convert.use_texture", 1);
{

}
//frame->set("rescale.interp", "bilinear");
//frame->set("deinterlace_method", "onefield");
//frame->set("top_field_first", -1);

uint8_t *ExtFrame::get_image( mlt_image_format &format, int &w, int &h, int writable )
{

	return NULL;
}

unsigned char *ExtFrame::fetch_image( mlt_image_format format, int w, int h, int writable )
{
	return NULL;
}

void *ExtFrame::get_audio( mlt_audio_format &format, int &frequency, int &channels, int &samples )
{
	return NULL;
}

unsigned char *ExtFrame::get_waveform( int w, int h )
{
	return NULL;
}

Producer *ExtFrame::get_original_producer( )
{
	return NULL;
}

int ExtFrame::get_position( )
{
	return -1;
}

int ExtFrame::is_test_audio() //frame->get_int("test_audio")
{
	return 0;
}

unsigned char *ExtFrame::get_alpha_data() //data = d->f.get_data("alpha", size );
{
	return NULL;
}

int ExtFrame::get_rendered_state() //frame.get_int("rendered")
{
	return 0;
}

mlt_image_format ExtFrame::get_image_format()// (mlt_image_format)d->f.get_int( "format" );
{
	return mlt_image_none;
}

mlt_audio_format ExtFrame::get_audio_format() const
{
	return mlt_audio_none;
}
//return (mlt_audio_format)d->f.get_int( "audio_format" );

double ExtFrame::get_audio_level(int index)
{
	return 0;
}
//const char* key[2] = { "meta.media.audio_level.0", "meta.media.audio_level.1"};
//frame->get_double(key[channel])

int ExtFrame::get_image_width() const
{
	return 0;
}
//return d->f.get_int( "width" );

int ExtFrame::get_image_height() const
{
	return 0;
}
//return d->f.get_int( "height" );

int ExtFrame::get_audio_channels() const
{
	return 0;
}
//return d->f.get_int( "audio_channels" );

int ExtFrame::get_audio_frequency() const
{
	return 0;
}
//return d->f.get_int( "audio_frequency" );

int ExtFrame::get_audio_samples() const
{
	return 0;
}
//return d->f.get_int( "audio_samples" );


//virtual mlt_frame get_frame( );
//mlt_properties get_properties( );

//mlt_properties get_unique_properties( Service &service );
//int set_image( uint8_t *image, int size, mlt_destructor destroy );
//int set_alpha( uint8_t *alpha, int size, mlt_destructor destroy );
