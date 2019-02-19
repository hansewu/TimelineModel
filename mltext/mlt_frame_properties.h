

#ifndef __MLT_FRAME_PROPERTIES_H__
#define __MLT_FRAME_PROPERTIES_H__

frame.get_int("rendered")
 (mlt_image_format)d->f.get_int( "format" );
data = d->f.get_data("alpha", size );
frame.set("movit.convert.use_texture", 1);

int SharedFrame::get_image_width() const
{
    return d->f.get_int( "width" );
}

int SharedFrame::get_image_height() const
{
    return d->f.get_int( "height" );
}

mlt_audio_format SharedFrame::get_audio_format() const
{
    return (mlt_audio_format)d->f.get_int( "audio_format" );
}

int SharedFrame::get_audio_channels() const
{
    return d->f.get_int( "audio_channels" );
}

int SharedFrame::get_audio_frequency() const
{
    return d->f.get_int( "audio_frequency" );
}

int SharedFrame::get_audio_samples() const
{
    return d->f.get_int( "audio_samples" );
}


GLsync sync = (GLsync) frame.get_data("movit.convert.fence");

    cloneFrame.inherit(d->f);
    cloneFrame.set("_producer", d->f.get_data("_producer", size), 0, NULL, NULL);
    cloneFrame.set("movit.convert", d->f.get_data("movit.convert", size), 0, NULL, NULL);
    cloneFrame.get_frame()->convert_image = d->f.get_frame()->convert_image;
    cloneFrame.get_frame()->convert_audio = d->f.get_frame()->convert_audio;

    data = d->f.get_data("audio", size);

#endif // __MLT_FRAME_PROPERTIES_H__
