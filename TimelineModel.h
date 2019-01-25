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

#define ClipProducer  Mlt::Producer

class TimelineModel 
{
public:    
    TimelineModel();
    virtual ~TimelineModel();
    
    int undo();
    int redo();

    int getTrackCount(TRACKTYPE track_type);
    TRACKTYPE   getTackType(int track_index);
    int insert_track(int track_index, TRACKTYPE track_type);
    int remove_track(int track_index);

    void set_track_name(int track_index, const std::string &track_name);
    void set_track_mute(int track_index, bool mute);
    void set_track_hidden(int track_index, bool hidden);
   // void set_track_composite(int row, Qt::CheckState composite);
    void set_track_Lock(int track_index, bool lock);

    int get_track_duration(int track_index);
    int get_clips_count(int track_index);
    ClipProducer& get_clip(int track_index, int clip_index);
    int insert_clip(int track_index, ClipProducer& clip, int position);
    int move_clip(int from_track, int to_track, int clip_index, int position);

    void split_clip(int track_index, int clip_index, int position);

    int trim_clip_in(int track_index, int clip_index, int delta, bool ripple);
    int trim_clip_out(int track_index, int clip_index, int delta, bool ripple);

    void add_transition_byTrimIn(int track_index, int clip_index, int delta);
    void add_transition_byTrimOut(int track_index, int clip_index, int delta);
}
#endif

