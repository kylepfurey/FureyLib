// .cs
// Singleton Base Class
// by Kyle Furey

/// <summary>
/// Allows a derived class to have a single global instance via T.Instance.
/// </summary>
public abstract class Singleton<T> where T : Singleton<T>, new()
{
    // VARIABLES

    /// <summary>
    /// The underlying singleton instance of this class.
    /// </summary>
    private static T _instance = null;


    // PROPERTIES

    /// <summary>
    /// Returns the singleton instance of this class.
    /// </summary>
    public static T Instance
    {
        get
        {
            if (_instance == null)
            {
                _instance = new T();
            }
            return _instance;
        }
    }
}
