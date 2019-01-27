

#ifndef __MLT_CONSUMER_PROPERTIES_H__
#define __MLT_CONSUMER_PROPERTIES_H__

#define kConsumer_ColorTrc_Property           "color_trc"
#define kConsumer_ImageFormat_Property        "mlt_image_format"
#define kConsumer_RealTime_Property           "real_time"
#define kConsumer_TerminateOnPause_Property           "terminate_on_pause"

#define kConsumer_AudioOff_Property           "audio_off"  //jackrack
#define kConsumer_Buffer_Property           "buffer"
#define kConsumer_Deinterlace_method_Property           "deinterlace_method"
#define kConsumer_Keyer_Property           "keyer"

#define kConsumer_One_Property           "1"              // encode set to "avformat"
#define kConsumer_OneTarget_Property           "1.target"  
#define kConsumer_OneStrict_Property           "1.strict"   // "experimental"

#define kConsumer_Prefill_Property           "prefill"
#define kConsumer_Progressive_Property           "progressive" 

#define kConsumer_Refresh_Property           "refresh"  

#define kConsumer_Rescale_Property           "rescale"
#define kConsumer_ScrubAudio_Property           "scrub_audio"  
#define kConsumer_Volume_Property           "volume"  

#define kConsumer_Zero_Property           "0"  //such as "sdl_audio"
#define kConsumer_ZeroAudioBuffer_Property           "0.audio_buffer"
#define kConsumer_ZeroBuffer_Property           "0.buffer"
#define kConsumer_ZeroDeinterlace_method_Property           "0.deinterlace_method"
#define kConsumer_ZeroKeyer_Property           "0.keyer"
#define kConsumer_ZeroPrefill_Property           "0.prefill"
#define kConsumer_ZeroProgressive_Property           "0.progressive" 
#define kConsumer_ZeroRescale_Property           "0.rescale"
#define kConsumer_ZeroVolume_Property           "0.volume"   //("mlt_service") == "multi"




#endif // __MLT_CONSUMER_PROPERTIES_H__
