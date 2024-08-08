
// Audio Manager Script
// by Kyle Furey

using System.Collections;
using System.Collections.Generic;
using System.Threading.Tasks;
using UnityEngine;

/// <summary>
/// A component that allows easy access to play sounds.
/// </summary>
public class AudioManager : MonoBehaviour, IEnumerable
{
    [Header("A component that allows easy access to play sounds.")]

    [Header("Each category for this audio manager's sounds:")]
    [SerializeField] private List<AudioCategory> audioCategories = new List<AudioCategory>();

    /// <summary>
    /// The compiled list of all sound instances
    /// </summary>
    private Dictionary<string, AudioSource> audio = new Dictionary<string, AudioSource>();

    /// <summary>
    /// Compile the sounds at the start of the component's creation
    /// </summary>
    private void Awake()
    {
        // Compile all audio categories into one list of audio instances
        foreach (AudioCategory audioCategory in audioCategories)
        {
            foreach (AudioInstance audioInstance in audioCategory.audio)
            {
                audio[audioInstance.name.ToLower()] = audioInstance.source;
            }
        }

        audioCategories.Clear();
    }


    // GET SOURCE

    /// <summary>
    /// Get a sound instance by name
    /// </summary>
    /// <param name="sound"></param>
    /// <returns></returns>
    public AudioSource GetSource(string sound)
    {
        return audio[sound.ToLower()];
    }


    // PLAYING SOUND

    /// <summary>
    /// Start playing a sound
    /// </summary>
    /// <param name="sound"></param>
    public void Play(string sound)
    {
        audio[sound.ToLower()].Stop();
        audio[sound.ToLower()].time = 0;
        audio[sound.ToLower()].Play();
    }

    /// <summary>
    /// Start playing a sound at the given start time
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="startTime"></param>
    public void Play(string sound, float startTime)
    {
        audio[sound.ToLower()].Stop();
        audio[sound.ToLower()].time = startTime;
        audio[sound.ToLower()].Play();
    }

    /// <summary>
    /// Start playing a sound at the given start time and volume
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="startTime"></param>
    /// <param name="volume"></param>
    public void Play(string sound, float startTime, float volume)
    {
        audio[sound.ToLower()].Stop();
        audio[sound.ToLower()].volume = volume;
        audio[sound.ToLower()].time = startTime;
        audio[sound.ToLower()].Play();
    }

    /// <summary>
    /// Start playing a sound at the given start time, volume, and pitch
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="startTime"></param>
    /// <param name="volume"></param>
    /// <param name="pitch"></param>
    public void Play(string sound, float startTime, float volume, float pitch)
    {
        audio[sound.ToLower()].Stop();
        audio[sound.ToLower()].volume = volume;
        audio[sound.ToLower()].pitch = pitch;
        audio[sound.ToLower()].time = startTime;
        audio[sound.ToLower()].Play();
    }

    /// <summary>
    /// Unpause a designated sound
    /// </summary>
    /// <param name="sound"></param>
    public void Unpause(string sound)
    {
        audio[sound.ToLower()].UnPause();
    }


    // STOPPING SOUND

    /// <summary>
    /// Stop playing a designated sound
    /// </summary>
    /// <param name="sound"></param>
    public void Stop(string sound)
    {
        if (audio[sound.ToLower()].isPlaying)
        {
            audio[sound.ToLower()].Stop();
            audio[sound.ToLower()].time = 0;
        }
    }

    /// <summary>
    /// Pause a designated sound
    /// </summary>
    /// <param name="sound"></param>
    public void Pause(string sound)
    {
        audio[sound.ToLower()].Pause();
    }

    /// <summary>
    /// Pause or unpause a designated sound
    /// </summary>
    /// <param name="sound"></param>
    public void Repause(string sound)
    {
        if (audio[sound.ToLower()].isPlaying)
        {
            audio[sound.ToLower()].Pause();
        }
        else
        {
            audio[sound.ToLower()].UnPause();
        }
    }


    // PLAYING SOUND ONCE

    /// <summary>
    /// Play a sound once
    /// </summary>
    /// <param name="sound"></param>
    public void PlayOnce(string sound)
    {
        audio[sound.ToLower()].PlayOneShot(audio[sound.ToLower()].clip);
    }

    /// <summary>
    /// Play a sound once at the given volume
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="volume"></param>
    public void PlayOnce(string sound, float volume)
    {
        audio[sound.ToLower()].volume = volume;
        audio[sound.ToLower()].PlayOneShot(audio[sound.ToLower()].clip);
    }

    /// <summary>
    /// Play a sound once at the given volume and pitch
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="volume"></param>
    /// <param name="pitch"></param>
    public void PlayOnce(string sound, float volume, float pitch)
    {
        audio[sound.ToLower()].volume = volume;
        audio[sound.ToLower()].pitch = pitch;
        audio[sound.ToLower()].PlayOneShot(audio[sound.ToLower()].clip);
    }


    // PLAYING MUSIC

    /// <summary>
    /// Play a sound after another sound ends (for music)
    /// </summary>
    /// <param name="opening"></param>
    /// <param name="track"></param>
    public void PlayMusic(string opening, string track)
    {
        audio[opening.ToLower()].Stop();
        audio[opening.ToLower()].time = 0;
        audio[opening.ToLower()].Play();

        audio[track.ToLower()].Stop();
        audio[track.ToLower()].time = 0;
        audio[track.ToLower()].PlayDelayed(audio[opening.ToLower()].clip.length);
    }

    /// <summary>
    /// Play a sound at the given start time after another sound ends (for music)
    /// </summary>
    /// <param name="opening"></param>
    /// <param name="openingStartTime"></param>
    /// <param name="track"></param>
    public void PlayMusic(string opening, float openingStartTime, string track)
    {
        audio[opening.ToLower()].Stop();
        audio[opening.ToLower()].time = openingStartTime;
        audio[opening.ToLower()].Play();

        audio[track.ToLower()].Stop();
        audio[track.ToLower()].time = 0;
        audio[track.ToLower()].PlayDelayed(audio[opening.ToLower()].clip.length - openingStartTime);
    }

    /// <summary>
    /// Play a sound at the given start time and volume after another sound ends (for music)
    /// </summary>
    /// <param name="opening"></param>
    /// <param name="openingStartTime"></param>
    /// <param name="openingVolume"></param>
    /// <param name="track"></param>
    public void PlayMusic(string opening, float openingStartTime, float openingVolume, string track)
    {
        audio[opening.ToLower()].Stop();
        audio[opening.ToLower()].volume = openingVolume;
        audio[opening.ToLower()].time = openingStartTime;
        audio[opening.ToLower()].Play();

        audio[track.ToLower()].Stop();
        audio[track.ToLower()].time = 0;
        audio[track.ToLower()].PlayDelayed(audio[opening.ToLower()].clip.length - openingStartTime);
    }

    /// <summary>
    /// Play a sound at the given start time, volume, and pitch after another sound ends (for music)
    /// </summary>
    /// <param name="opening"></param>
    /// <param name="openingStartTime"></param>
    /// <param name="openingVolume"></param>
    /// <param name="openingPitch"></param>
    /// <param name="track"></param>
    public void PlayMusic(string opening, float openingStartTime, float openingVolume, float openingPitch, string track)
    {
        audio[opening.ToLower()].Stop();
        audio[opening.ToLower()].volume = openingVolume;
        audio[opening.ToLower()].pitch = openingPitch;
        audio[opening.ToLower()].time = openingStartTime;
        audio[opening.ToLower()].Play();

        audio[track.ToLower()].Stop();
        audio[track.ToLower()].time = 0;
        audio[track.ToLower()].PlayDelayed(audio[opening.ToLower()].clip.length - openingStartTime);
    }

    /// <summary>
    /// Play a sound after another sound ends starting at the given start time (for music)
    /// </summary>
    /// <param name="opening"></param>
    /// <param name="track"></param>
    /// <param name="trackStartTime"></param>
    public void PlayMusic(string opening, string track, float trackStartTime)
    {
        audio[opening.ToLower()].Stop();
        audio[opening.ToLower()].time = 0;
        audio[opening.ToLower()].Play();

        audio[track.ToLower()].Stop();
        audio[track.ToLower()].time = trackStartTime;
        audio[track.ToLower()].PlayDelayed(audio[opening.ToLower()].clip.length);
    }

    /// <summary>
    /// Play a sound after another sound ends starting at the given start time and volume (for music)
    /// </summary>
    /// <param name="opening"></param>
    /// <param name="track"></param>
    /// <param name="trackStartTime"></param>
    /// <param name="trackVolume"></param>
    public void PlayMusic(string opening, string track, float trackStartTime, float trackVolume)
    {
        audio[opening.ToLower()].Stop();
        audio[opening.ToLower()].time = 0;
        audio[opening.ToLower()].Play();

        audio[track.ToLower()].Stop();
        audio[track.ToLower()].volume = trackVolume;
        audio[track.ToLower()].time = trackStartTime;
        audio[track.ToLower()].PlayDelayed(audio[opening.ToLower()].clip.length);
    }

    /// <summary>
    /// Play a sound after another sound ends starting at the given start time, volume, and pitch (for music)
    /// </summary>
    /// <param name="opening"></param>
    /// <param name="track"></param>
    /// <param name="trackStartTime"></param>
    /// <param name="trackVolume"></param>
    /// <param name="trackPitch"></param>
    public void PlayMusic(string opening, string track, float trackStartTime, float trackVolume, float trackPitch)
    {
        audio[opening.ToLower()].Stop();
        audio[opening.ToLower()].time = 0;
        audio[opening.ToLower()].Play();

        audio[track.ToLower()].Stop();
        audio[track.ToLower()].volume = trackVolume;
        audio[track.ToLower()].pitch = trackPitch;
        audio[track.ToLower()].time = trackStartTime;
        audio[track.ToLower()].PlayDelayed(audio[opening.ToLower()].clip.length);
    }

    /// <summary>
    /// Play a sound at the given start time after another sound ends starting at the given start time (for music)
    /// </summary>
    /// <param name="opening"></param>
    /// <param name="openingStartTime"></param>
    /// <param name="track"></param>
    /// <param name="trackStartTime"></param>
    public void PlayMusic(string opening, float openingStartTime, string track, float trackStartTime)
    {
        audio[opening.ToLower()].Stop();
        audio[opening.ToLower()].time = openingStartTime;
        audio[opening.ToLower()].Play();

        audio[track.ToLower()].Stop();
        audio[track.ToLower()].time = trackStartTime;
        audio[track.ToLower()].PlayDelayed(audio[opening.ToLower()].clip.length - openingStartTime);
    }

    /// <summary>
    /// Play a sound at the given start time and volume after another sound ends starting at the given start time and volume (for music)
    /// </summary>
    /// <param name="opening"></param>
    /// <param name="openingStartTime"></param>
    /// <param name="openingVolume"></param>
    /// <param name="track"></param>
    /// <param name="trackStartTime"></param>
    /// <param name="trackVolume"></param>
    public void PlayMusic(string opening, float openingStartTime, float openingVolume, string track, float trackStartTime, float trackVolume)
    {
        audio[opening.ToLower()].Stop();
        audio[opening.ToLower()].volume = openingVolume;
        audio[opening.ToLower()].time = openingStartTime;
        audio[opening.ToLower()].Play();

        audio[track.ToLower()].Stop();
        audio[track.ToLower()].volume = trackVolume;
        audio[track.ToLower()].time = trackStartTime;
        audio[track.ToLower()].PlayDelayed(audio[opening.ToLower()].clip.length - openingStartTime);
    }

    /// <summary>
    /// Play a sound at the given start time, volume, and pitch after another sound ends starting at the given start time, volume, and pitch (for music)
    /// </summary>
    /// <param name="opening"></param>
    /// <param name="openingStartTime"></param>
    /// <param name="openingVolume"></param>
    /// <param name="openingPitch"></param>
    /// <param name="track"></param>
    /// <param name="trackStartTime"></param>
    /// <param name="trackVolume"></param>
    /// <param name="trackPitch"></param>
    public void PlayMusic(string opening, float openingStartTime, float openingVolume, float openingPitch, string track, float trackStartTime, float trackVolume, float trackPitch)
    {
        audio[opening.ToLower()].Stop();
        audio[opening.ToLower()].volume = openingVolume;
        audio[opening.ToLower()].pitch = openingPitch;
        audio[opening.ToLower()].time = openingStartTime;
        audio[opening.ToLower()].Play();

        audio[track.ToLower()].Stop();
        audio[track.ToLower()].volume = trackVolume;
        audio[track.ToLower()].pitch = trackPitch;
        audio[track.ToLower()].time = trackStartTime;
        audio[track.ToLower()].PlayDelayed(audio[opening.ToLower()].clip.length - openingStartTime);
    }

    /// <summary>
    /// Play a sound at the given start time after another sound ends starting at the given start time both at the given volume (for music)
    /// </summary>
    /// <param name="opening"></param>
    /// <param name="openingStartTime"></param>
    /// <param name="track"></param>
    /// <param name="trackStartTime"></param>
    /// <param name="volume"></param>
    public void PlayMusic(string opening, float openingStartTime, string track, float trackStartTime, float volume)
    {
        audio[opening.ToLower()].Stop();
        audio[opening.ToLower()].volume = volume;
        audio[opening.ToLower()].time = openingStartTime;
        audio[opening.ToLower()].Play();

        audio[track.ToLower()].Stop();
        audio[track.ToLower()].volume = volume;
        audio[track.ToLower()].time = trackStartTime;
        audio[track.ToLower()].PlayDelayed(audio[opening.ToLower()].clip.length - openingStartTime);
    }

    /// <summary>
    /// Play a sound at the given start time after another sound ends starting at the given start time both at the given volume and pitch (for music)
    /// </summary>
    /// <param name="opening"></param>
    /// <param name="openingStartTime"></param>
    /// <param name="track"></param>
    /// <param name="trackStartTime"></param>
    /// <param name="volume"></param>
    /// <param name="pitch"></param>
    public void PlayMusic(string opening, float openingStartTime, string track, float trackStartTime, float volume, float pitch)
    {
        audio[opening.ToLower()].Stop();
        audio[opening.ToLower()].volume = volume;
        audio[opening.ToLower()].pitch = pitch;
        audio[opening.ToLower()].time = openingStartTime;
        audio[opening.ToLower()].Play();

        audio[track.ToLower()].Stop();
        audio[track.ToLower()].volume = volume;
        audio[track.ToLower()].pitch = pitch;
        audio[track.ToLower()].time = trackStartTime;
        audio[track.ToLower()].PlayDelayed(audio[opening.ToLower()].clip.length - openingStartTime);
    }


    // PLAYING SOUND AT LOCATION

    /// <summary>
    /// Play a sound at a specific location
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="position"></param>
    public void PlayAt(string sound, Vector3 position)
    {
        AudioSource.PlayClipAtPoint(audio[sound.ToLower()].clip, position);
    }

    /// <summary>
    /// Play a sound at a specific location and volume
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="position"></param>
    /// <param name="volume"></param>
    public void PlayAt(string sound, Vector3 position, float volume)
    {
        audio[sound.ToLower()].volume = volume;
        AudioSource.PlayClipAtPoint(audio[sound.ToLower()].clip, position);
    }

    /// <summary>
    /// Play the sound at the audio manager component's location
    /// </summary>
    /// <param name="sound"></param>
    public void PlayHere(string sound)
    {
        AudioSource.PlayClipAtPoint(audio[sound.ToLower()].clip, transform.position);
    }

    /// <summary>
    /// Play the sound at the audio manager component's location at the given volume
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="volume"></param>
    public void PlayHere(string sound, float volume)
    {
        audio[sound.ToLower()].volume = volume;
        AudioSource.PlayClipAtPoint(audio[sound.ToLower()].clip, transform.position);
    }


    // PLAYING SOUND FOR DURATION

    /// <summary>
    /// Start playing a sound for a specific time
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="duration"></param>
    public void PlayFor(string sound, float duration)
    {
        audio[sound.ToLower()].Stop();
        audio[sound.ToLower()].Play();
        StopPlay(audio[sound.ToLower()], duration);
    }

    /// <summary>
    /// Start playing a sound for a specific time starting at the start time
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="duration"></param>
    /// <param name="startTime"></param>
    public void PlayFor(string sound, float duration, float startTime)
    {
        audio[sound.ToLower()].Stop();
        audio[sound.ToLower()].time = startTime;
        audio[sound.ToLower()].Play();
        StopPlay(audio[sound.ToLower()], duration);
    }

    /// <summary>
    /// Start playing a sound for a specific time starting at the start time and volume
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="duration"></param>
    /// <param name="startTime"></param>
    /// <param name="volume"></param>
    public void PlayFor(string sound, float duration, float startTime, float volume)
    {
        audio[sound.ToLower()].Stop();
        audio[sound.ToLower()].time = startTime;
        audio[sound.ToLower()].volume = volume;
        audio[sound.ToLower()].Play();
        StopPlay(audio[sound.ToLower()], duration);
    }

    /// <summary>
    /// Start playing a sound for a specific time starting at the start time, volume, and pitch
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="duration"></param>
    /// <param name="startTime"></param>
    /// <param name="volume"></param>
    /// <param name="pitch"></param>
    public void PlayFor(string sound, float duration, float startTime, float volume, float pitch)
    {
        audio[sound.ToLower()].Stop();
        audio[sound.ToLower()].time = startTime;
        audio[sound.ToLower()].volume = volume;
        audio[sound.ToLower()].pitch = pitch;
        audio[sound.ToLower()].Play();
        StopPlay(audio[sound.ToLower()], duration);
    }

    /// <summary>
    /// Used to stop playing a sound at a duration
    /// </summary>
    /// <param name="source"></param>
    /// <param name="seconds"></param>
    private async void StopPlay(AudioSource source, float seconds)
    {
        await Task.Delay((int)(1000 * seconds));

        source.Stop();
    }


    // MUTING SOUND

    /// <summary>
    /// Mutes the given sound
    /// </summary>
    /// <param name="sound"></param>
    public void Mute(string sound)
    {
        audio[sound.ToLower()].mute = true;
    }

    /// <summary>
    /// Unmutes the given sound
    /// </summary>
    /// <param name="sound"></param>
    public void Unmute(string sound)
    {
        audio[sound.ToLower()].mute = false;
    }

    /// <summary>
    /// Mutes or unmutes the given sound
    /// </summary>
    /// <param name="sound"></param>
    public void Remute(string sound)
    {
        audio[sound.ToLower()].mute = !audio[sound.ToLower()].mute;
    }


    // GETTERS

    /// <summary>
    /// Gets the given sound's duration in seconds
    /// </summary>
    /// <param name="sound"></param>
    public float GetDuration(string sound)
    {
        return audio[sound.ToLower()].clip.length;
    }

    /// <summary>
    /// Gets the given sound's current time in seconds
    /// </summary>
    /// <param name="sound"></param>
    public float GetTime(string sound)
    {
        return audio[sound.ToLower()].time;
    }

    /// <summary>
    /// Gets the given sound's volume
    /// </summary>
    /// <param name="sound"></param>
    public float GetVolume(string sound)
    {
        return audio[sound.ToLower()].volume;
    }

    /// <summary>
    /// Gets the given sound's pitch
    /// </summary>
    /// <param name="sound"></param>
    public float GetPitch(string sound)
    {
        return audio[sound.ToLower()].pitch;
    }

    /// <summary>
    /// Gets the given sound's audio clip
    /// </summary>
    /// <param name="sound"></param>
    public AudioClip GetClip(string sound)
    {
        return audio[sound.ToLower()].clip;
    }

    /// <summary>
    /// Gets whether the given sound is currently playing
    /// </summary>
    /// <param name="sound"></param>
    public bool IsPlaying(string sound)
    {
        return audio[sound.ToLower()].isPlaying;
    }

    /// <summary>
    /// Gets whether the given sound is currently not playing
    /// </summary>
    /// <param name="sound"></param>
    public bool IsPaused(string sound)
    {
        return !audio[sound.ToLower()].isPlaying;
    }


    // SETTERS

    /// <summary>
    /// Sets the given sound's current time in seconds
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="time"></param>
    public void SetTime(string sound, float time)
    {
        audio[sound.ToLower()].time = time;
    }

    /// <summary>
    /// Sets the given sound's volume
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="volume"></param>
    public void SetVolume(string sound, float volume)
    {
        audio[sound.ToLower()].volume = volume;
    }

    /// <summary>
    /// Sets the given sound's pitch
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="pitch"></param>
    public void SetPitch(string sound, float pitch)
    {
        audio[sound.ToLower()].pitch = pitch;
    }

    /// <summary>
    /// Sets the given sound's audio clip
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="clip"></param>
    public void SetClip(string sound, AudioClip clip)
    {
        audio[sound.ToLower()].clip = clip;
    }

    /// <summary>
    /// Sets all the given sound's variables
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="time"></param>
    /// <param name="volume"></param>
    /// <param name="pitch"></param>
    /// <param name="clip"></param>
    public void SetAll(string sound, float time = 0, float volume = 1, float pitch = 1, AudioClip clip = null)
    {
        audio[sound.ToLower()].time = time;
        audio[sound.ToLower()].volume = volume;
        audio[sound.ToLower()].pitch = pitch;

        if (clip != null)
        {
            audio[sound.ToLower()].clip = clip;
        }
    }

    /// <summary>
    /// IEnumerator Implementation
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return audio.GetEnumerator();
    }
}


// AUDIO CLASSES

/// <summary>
/// Audio Instance Class
/// </summary>
[System.Serializable]
public class AudioInstance
{
    [Header("The referenced name of this audio instance:")]
    public string name = "New Audio Clip";

    [Header("The source of this audio instance:")]
    public AudioSource source = null;

    /// <summary>
    /// Audio constructor
    /// </summary>
    /// <param name="name"></param>
    /// <param name="source"></param>
    public AudioInstance(string name, AudioSource source)
    {
        this.name = name;
        this.source = source;
    }
}

/// <summary>
/// Audio Category Class
/// </summary>
[System.Serializable]
public class AudioCategory : IEnumerable
{
    [Header("The name of this audio category:")]
    public string name = "New Audio Category";

    [Header("The sounds owned by this audio category:")]
    public List<AudioInstance> audio = new List<AudioInstance>();

    /// <summary>
    /// IEnumerator Implementation
    /// </summary>
    /// <returns></returns>
    public IEnumerator GetEnumerator()
    {
        return audio.GetEnumerator();
    }
}
