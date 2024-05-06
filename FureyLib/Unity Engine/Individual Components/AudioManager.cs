
// Audio Manager Script
// by Kyle Furey

using System.Collections.Generic;
using System.Threading.Tasks;
using UnityEngine;

/// <summary>
/// A component that allows easy access to play sounds.
/// </summary>
public class AudioManager : MonoBehaviour
{
    [Header("A component that allows easy access to play sounds.")]

    [Header("Each category for this audio manager's sounds:")]
    [SerializeField] private List<AudioCategory> audioCategories = new List<AudioCategory>();

    /// <summary>
    /// The compiled list of all sound instances
    /// </summary>
    private Dictionary<string, AudioInstance> audio = new Dictionary<string, AudioInstance>();

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
                audio[audioInstance.name.ToLower()] = audioInstance;
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
        return audio[sound.ToLower()].source;
    }


    // PLAYING SOUND

    /// <summary>
    /// Start playing a sound
    /// </summary>
    /// <param name="sound"></param>
    public void Play(string sound)
    {
        audio[sound.ToLower()].source.Stop();
        audio[sound.ToLower()].source.time = 0;
        audio[sound.ToLower()].source.Play();
    }

    /// <summary>
    /// Start playing a sound at the given start time
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="startTime"></param>
    public void Play(string sound, float startTime)
    {
        audio[sound.ToLower()].source.Stop();
        audio[sound.ToLower()].source.time = startTime;
        audio[sound.ToLower()].source.Play();
    }

    /// <summary>
    /// Start playing a sound at the given start time and volume
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="startTime"></param>
    /// <param name="volume"></param>
    public void Play(string sound, float startTime, float volume)
    {
        audio[sound.ToLower()].source.Stop();
        audio[sound.ToLower()].source.volume = volume;
        audio[sound.ToLower()].source.time = startTime;
        audio[sound.ToLower()].source.Play();
    }


    // STOPPING SOUND

    /// <summary>
    /// Stop playing a designated sound
    /// </summary>
    /// <param name="sound"></param>
    public void Stop(string sound)
    {
        if (audio[sound.ToLower()].source.isPlaying)
        {
            audio[sound.ToLower()].source.Stop();
            audio[sound.ToLower()].source.time = 0;
        }
    }


    // PLAYING SOUND ONCE

    /// <summary>
    /// Play a sound once
    /// </summary>
    /// <param name="sound"></param>
    public void PlayOnce(string sound)
    {
        audio[sound.ToLower()].source.PlayOneShot(audio[sound.ToLower()].source.clip);
    }

    /// <summary>
    /// Play a sound once at the given volume
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="volume"></param>
    public void PlayOnce(string sound, float volume)
    {
        audio[sound.ToLower()].source.PlayOneShot(audio[sound.ToLower()].source.clip, volume);
    }


    // PLAYING MUSIC

    /// <summary>
    /// Play a sound after another sound ends (for music)
    /// </summary>
    /// <param name="opening"></param>
    /// <param name="track"></param>
    public void PlayMusic(string opening, string track)
    {
        audio[opening.ToLower()].source.Stop();
        audio[opening.ToLower()].source.time = 0;
        audio[opening.ToLower()].source.Play();

        audio[track.ToLower()].source.Stop();
        audio[track.ToLower()].source.time = 0;
        audio[track.ToLower()].source.PlayDelayed(audio[opening.ToLower()].source.clip.length);
    }

    /// <summary>
    /// Play a sound at the given start time after another sound ends (for music)
    /// </summary>
    /// <param name="opening"></param>
    /// <param name="openingStartTime"></param>
    /// <param name="track"></param>
    public void PlayMusic(string opening, float openingStartTime, string track)
    {
        audio[opening.ToLower()].source.Stop();
        audio[opening.ToLower()].source.time = openingStartTime;
        audio[opening.ToLower()].source.Play();

        audio[track.ToLower()].source.Stop();
        audio[track.ToLower()].source.time = 0;
        audio[track.ToLower()].source.PlayDelayed(audio[opening.ToLower()].source.clip.length - openingStartTime);
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
        audio[opening.ToLower()].source.Stop();
        audio[opening.ToLower()].source.volume = openingVolume;
        audio[opening.ToLower()].source.time = openingStartTime;
        audio[opening.ToLower()].source.Play();

        audio[track.ToLower()].source.Stop();
        audio[track.ToLower()].source.time = 0;
        audio[track.ToLower()].source.PlayDelayed(audio[opening.ToLower()].source.clip.length - openingStartTime);
    }

    /// <summary>
    /// Play a sound after another sound ends starting at the given start time (for music)
    /// </summary>
    /// <param name="opening"></param>
    /// <param name="track"></param>
    /// <param name="trackStartTime"></param>
    public void PlayMusic(string opening, string track, float trackStartTime)
    {
        audio[opening.ToLower()].source.Stop();
        audio[opening.ToLower()].source.time = 0;
        audio[opening.ToLower()].source.Play();

        audio[track.ToLower()].source.Stop();
        audio[track.ToLower()].source.time = trackStartTime;
        audio[track.ToLower()].source.PlayDelayed(audio[opening.ToLower()].source.clip.length);
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
        audio[opening.ToLower()].source.Stop();
        audio[opening.ToLower()].source.time = 0;
        audio[opening.ToLower()].source.Play();

        audio[track.ToLower()].source.Stop();
        audio[track.ToLower()].source.volume = trackVolume;
        audio[track.ToLower()].source.time = trackStartTime;
        audio[track.ToLower()].source.PlayDelayed(audio[opening.ToLower()].source.clip.length);
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
        audio[opening.ToLower()].source.Stop();
        audio[opening.ToLower()].source.time = openingStartTime;
        audio[opening.ToLower()].source.Play();

        audio[track.ToLower()].source.Stop();
        audio[track.ToLower()].source.time = trackStartTime;
        audio[track.ToLower()].source.PlayDelayed(audio[opening.ToLower()].source.clip.length - openingStartTime);
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
        audio[opening.ToLower()].source.Stop();
        audio[opening.ToLower()].source.volume = openingVolume;
        audio[opening.ToLower()].source.time = openingStartTime;
        audio[opening.ToLower()].source.Play();

        audio[track.ToLower()].source.Stop();
        audio[track.ToLower()].source.volume = trackVolume;
        audio[track.ToLower()].source.time = trackStartTime;
        audio[track.ToLower()].source.PlayDelayed(audio[opening.ToLower()].source.clip.length - openingStartTime);
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
        audio[opening.ToLower()].source.Stop();
        audio[opening.ToLower()].source.volume = volume;
        audio[opening.ToLower()].source.time = openingStartTime;
        audio[opening.ToLower()].source.Play();

        audio[track.ToLower()].source.Stop();
        audio[track.ToLower()].source.volume = volume;
        audio[track.ToLower()].source.time = trackStartTime;
        audio[track.ToLower()].source.PlayDelayed(audio[opening.ToLower()].source.clip.length - openingStartTime);
    }


    // PLAYING SOUND AT LOCATION

    /// <summary>
    /// Play a sound at a specific location
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="position"></param>
    public void PlayAt(string sound, Vector3 position)
    {
        AudioSource.PlayClipAtPoint(audio[sound.ToLower()].source.clip, position);
    }

    /// <summary>
    /// Play a sound at a specific location and volume
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="position"></param>
    /// <param name="volume"></param>
    public void PlayAt(string sound, Vector3 position, float volume)
    {
        audio[sound.ToLower()].source.volume = volume;
        AudioSource.PlayClipAtPoint(audio[sound.ToLower()].source.clip, position);
    }

    /// <summary>
    /// Play the sound at the audio manager component's location
    /// </summary>
    /// <param name="sound"></param>
    public void PlayHere(string sound)
    {
        AudioSource.PlayClipAtPoint(audio[sound.ToLower()].source.clip, transform.position);
    }

    /// <summary>
    /// Play the sound at the audio manager component's location at the given volume
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="volume"></param>
    public void PlayHere(string sound, float volume)
    {
        audio[sound.ToLower()].source.volume = volume;
        AudioSource.PlayClipAtPoint(audio[sound.ToLower()].source.clip, transform.position);
    }


    // PLAYING SOUND FOR DURATION

    /// <summary>
    /// Start playing a sound for a specific time
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="duration"></param>
    public void PlayFor(string sound, float duration)
    {
        audio[sound.ToLower()].source.Stop();
        audio[sound.ToLower()].source.Play();
        StopPlay(audio[sound.ToLower()].source, duration);
    }

    /// <summary>
    /// Start playing a sound for a specific time starting at the start time
    /// </summary>
    /// <param name="sound"></param>
    /// <param name="duration"></param>
    /// <param name="startTime"></param>
    public void PlayFor(string sound, float duration, float startTime)
    {
        audio[sound.ToLower()].source.Stop();
        audio[sound.ToLower()].source.time = startTime;
        audio[sound.ToLower()].source.Play();
        StopPlay(audio[sound.ToLower()].source, duration);
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
        audio[sound.ToLower()].source.Stop();
        audio[sound.ToLower()].source.time = startTime;
        audio[sound.ToLower()].source.volume = volume;
        audio[sound.ToLower()].source.Play();
        StopPlay(audio[sound.ToLower()].source, duration);
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
}

/// <summary>
/// Audio Category Class
/// </summary>
[System.Serializable]
public class AudioCategory
{
    [Header("The name of this audio category:")]
    public string name = "New Audio Category";

    [Header("The sounds owned by this audio category:")]
    public List<AudioInstance> audio = new List<AudioInstance>();
}
