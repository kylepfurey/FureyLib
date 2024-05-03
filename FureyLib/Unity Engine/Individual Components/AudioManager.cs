
// Audio Manager Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;

// A component that allows easy access to play sounds.
public class AudioManager : MonoBehaviour
{
    [Header("A component that allows easy access to play sounds.")]

    public List<AudioCategory> audioCategories = new List<AudioCategory>();

    private List<AudioInstance> audio = new List<AudioInstance>();

    private void Awake()
    {
        // Compile all audio categories into one list of audio instances
        foreach (AudioCategory audioCategory in audioCategories)
        {
            foreach (AudioInstance audioInstance in audioCategory.audio)
            {
                audio.Add(audioInstance);
            }
        }
    }

    // Get a sound instance by name
    public AudioSource Get(string sound)
    {
        for (int i = 0; i < audio.Count; i++)
        {
            if (sound.ToLower() == audio[i].name.ToLower() && audio[i] != null)
            {
                return audio[i].source;
            }
        }

        return null;
    }

    // Start playing a sound
    public void Play(string sound)
    {
        for (int i = 0; i < audio.Count; i++)
        {
            if (sound.ToLower() == audio[i].name.ToLower() && audio[i] != null && audio[i].source.clip != null)
            {
                audio[i].source.Stop();
                audio[i].source.time = 0;
                audio[i].source.Play();
                break;
            }
        }
    }

    public void Play(string sound, float startTime)
    {
        for (int i = 0; i < audio.Count; i++)
        {
            if (sound.ToLower() == audio[i].name.ToLower() && audio[i] != null && audio[i].source.clip != null)
            {
                audio[i].source.Stop();
                audio[i].source.time = startTime;
                audio[i].source.Play();
                break;
            }
        }
    }

    // Stop playing a designated sound
    public void Stop(string sound)
    {
        for (int i = 0; i < audio.Count; i++)
        {
            if (sound.ToLower() == audio[i].name.ToLower() && audio[i] != null && audio[i].source.clip != null)
            {
                if (audio[i].source.isPlaying)
                {
                    audio[i].source.Stop();
                    audio[i].source.time = 0;
                }
                break;
            }
        }
    }

    // Play a sound once
    public void PlayOnce(string sound)
    {
        for (int i = 0; i < audio.Count; i++)
        {
            if (sound.ToLower() == audio[i].name.ToLower() && audio[i] != null && audio[i].source.clip != null)
            {
                audio[i].source.PlayOneShot(audio[i].source.clip);
                break;
            }
        }
    }

    public void PlayOnce(string sound, float volume)
    {
        for (int i = 0; i < audio.Count; i++)
        {
            if (sound.ToLower() == audio[i].name.ToLower() && audio[i] != null && audio[i].source.clip != null)
            {
                audio[i].source.PlayOneShot(audio[i].source.clip, volume);
                break;
            }
        }
    }

    // Play a sound after another sound ends
    public void PlayMusic(string opening, string music)
    {
        for (int i = 0; i < audio.Count; i++)
        {
            if (opening.ToLower() == audio[i].name.ToLower() && audio[i] != null && audio[i].source.clip != null)
            {
                audio[i].source.Stop();
                audio[i].source.time = 0;
                audio[i].source.Play();

                for (int j = 0; j < audio.Count; j++)
                {
                    if (music.ToLower() == audio[j].name.ToLower() && audio[j] != null && audio[j].source.clip != null)
                    {
                        audio[j].source.Stop();
                        audio[j].source.time = 0;
                        audio[j].source.PlayDelayed(audio[i].source.clip.length);
                        break;
                    }
                }
                break;
            }
        }
    }

    public void PlayMusic(string opening, float openingStartTime, string music)
    {
        for (int i = 0; i < audio.Count; i++)
        {
            if (opening.ToLower() == audio[i].name.ToLower() && audio[i] != null && audio[i].source.clip != null)
            {
                audio[i].source.Stop();
                audio[i].source.time = openingStartTime;
                audio[i].source.Play();

                for (int j = 0; j < audio.Count; j++)
                {
                    if (music.ToLower() == audio[j].name.ToLower() && audio[j] != null && audio[j].source.clip != null)
                    {
                        audio[j].source.Stop();
                        audio[j].source.time = 0;
                        audio[j].source.PlayDelayed(audio[i].source.clip.length - openingStartTime);
                        break;
                    }
                }
                break;
            }
        }
    }

    public void PlayMusic(string opening, string music, float musicStartTime)
    {
        for (int i = 0; i < audio.Count; i++)
        {
            if (opening.ToLower() == audio[i].name.ToLower() && audio[i] != null && audio[i].source.clip != null)
            {
                audio[i].source.Stop();
                audio[i].source.time = 0;
                audio[i].source.Play();

                for (int j = 0; j < audio.Count; j++)
                {
                    if (music.ToLower() == audio[j].name.ToLower() && audio[j] != null && audio[j].source.clip != null)
                    {
                        audio[j].source.Stop();
                        audio[j].source.time = musicStartTime;
                        audio[j].source.PlayDelayed(audio[i].source.clip.length);
                        break;
                    }
                }
                break;
            }
        }
    }

    public void PlayMusic(string opening, float openingStartTime, string music, float musicStartTime)
    {
        for (int i = 0; i < audio.Count; i++)
        {
            if (opening.ToLower() == audio[i].name.ToLower() && audio[i] != null && audio[i].source.clip != null)
            {
                audio[i].source.Stop();
                audio[i].source.time = openingStartTime;
                audio[i].source.Play();

                for (int j = 0; j < audio.Count; j++)
                {
                    if (music.ToLower() == audio[j].name.ToLower() && audio[j] != null && audio[j].source.clip != null)
                    {
                        audio[j].source.Stop();
                        audio[j].source.time = musicStartTime;
                        audio[j].source.PlayDelayed(audio[i].source.clip.length - openingStartTime);
                        break;
                    }
                }
                break;
            }
        }
    }
}

// Audio Instance Class
[System.Serializable]
public class AudioInstance
{
    public string name = "New Audio Clip";
    public AudioSource source = null;
}

// Audio Category Class
[System.Serializable]
public class AudioCategory
{
    public string name = "New Audio Category";
    public List<AudioInstance> audio = new List<AudioInstance>();
}
