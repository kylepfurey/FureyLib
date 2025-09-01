// .cs
// Singleton Component Base Class
// by Kyle Furey

using UnityEngine;

/// <summary>
/// Allows a derived MonoBehaviour to have a single global instance via T.Instance.
/// </summary>
public abstract class Singleton<T> : MonoBehaviour where T : Singleton<T>
{
    // VARIABLES

    /// <summary>
    /// The underlying singleton instance of this component.
    /// </summary>
    private static T _instance = null;

    /// <summary>
    /// Whether the game is currently quitting and singletons should not be instantiated.
    /// </summary>
    private static bool _isQuitting = false;


    // PROPERTIES

    /// <summary>
    /// Returns the singleton instance of this component.
    /// </summary>
    public static T Instance
    {
        get
        {
            if (!Application.isPlaying || _isQuitting)
            {
                return null;
            }
            if (_instance == null)
            {
                _instance = FindFirstObjectByType<T>(FindObjectsInactive.Include);
                if (_instance == null)
                {
                    GameObject gameObject = new GameObject('[' + typeof(T).Name + ']');
                    _instance = gameObject.AddComponent<T>();
                    DontDestroyOnLoad(gameObject);
                }
            }
            return _instance;
        }
    }


    // EVENTS

    /// <summary>
    /// Initializes the singleton.
    /// </summary>
    protected virtual void Awake()
    {
        if (!Application.isPlaying || _isQuitting)
        {
            return;
        }
        if (_instance == null)
        {
            _instance = (T)this;
            gameObject.transform.SetParent(null);
            DontDestroyOnLoad(gameObject);
        }
        else
        {
            Destroy(this);
        }
    }

    /// <summary>
    /// Cleans up the singleton.
    /// </summary>
    protected virtual void OnDestroy()
    {
        if (_instance == this)
        {
            _instance = null;
        }
    }

    /// <summary>
    /// Prevents instantiation of the singleton while the game is quitting.
    /// </summary>
    protected virtual void OnApplicationQuit()
    {
        _isQuitting = true;
    }
}
