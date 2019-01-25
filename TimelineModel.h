#ifndef __TIMELINE_MODEL_H__
#define __TIMELINE_MODEL_H__

typedef enum 
{
    AnyTrackType = -1,
    PlaylistTrackType = 0,
    BlackTrackType,
    SilentTrackType,
    AudioTrackType, 
    VideoTrackType, 
    FilterTrackType, 
    TextTrackType,   
    VoiceTrackType,
    SoundFxTrackType,
    OverlayTrackType
} TRACKTYPE;

typedef enum 
{
    ImageClipType = 0,
    TextClipType,
    EmptyClipType,
    AudioOnlyClipType, 
    VideoOnlyClipType, 
    VideoAndAudioClipType,
    ProjectClipType,
    TransitionClipType 
} CLIP_TYPE;

#define CLIP_CONTEXT    Mlt::Producer*
#define FILTER_CONTEXT  Mlt::Filter*
class TimelineModel 
{
public:    
    TimelineModel();
    virtual ~TimelineModel();
    
    int undo();
    int redo();

    int get_track_count(TRACKTYPE track_type);
    TRACKTYPE   get_tack_type(int track_index);
    int insert_track(int track_index, TRACKTYPE track_type);
    int remove_track(int track_index);

    void set_track_name(int track_index, const std::string &track_name);
    void set_track_mute(int track_index, bool mute);
    void set_track_hidden(int track_index, bool hidden);
   // void set_track_composite(int row, Qt::CheckState composite);
    void set_track_Lock(int track_index, bool lock);

    int get_track_duration(int track_index);
    int get_clips_count(int track_index);
    
    CLIP_CONTEXT get_clip(int track_index, int clip_index);
    int get_clip_index( CLIP_CONTEXT clip_context, int &track_index, int &clip_index);
    CLIP_TYPE get_clip_type(CLIP_CONTEXT clip_context);
    int get_clip_position(CLIP_CONTEXT clip_context);

    int insert_clip(int track_index, CLIP_CONTEXT clip_context, int position);
    int move_clip(int from_track, int to_track, int clip_index, int position);

    int split_clip(int track_index, int clip_index, int position);

    int trim_clip_in(int track_index, int clip_index, int delta, bool ripple);
    int trim_clip_out(int track_index, int clip_index, int delta, bool ripple);

    int add_Transition(int trackIndex, int clipIndex, int position);
    int add_transition_byTrimIn(int track_index, int clip_index, int delta);
    int add_transition_byTrimOut(int track_index, int clip_index, int delta);

    int remove_transition(int track_index, int clip_index);

    int trim_transition_in(int track_index, int clip_index, int delta);
    int trim_transition_out(int track_index, int clip_index, int delta);

    int get_filters_count(CLIP_CONTEXT clip_context);
    int insert_filter(CLIP_CONTEXT clip_context, int filter_index, FILTER_CONTEXT filter_context);
    int move_filter(CLIP_CONTEXT clip_context, int filter_index_from, int filter_index_to);
    int remove_filter(CLIP_CONTEXT clip_context, int filter_index);
}
#endif

