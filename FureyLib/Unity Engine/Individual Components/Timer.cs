
// Simple Timer Script
// by Kyle Furey

using UnityEngine;
using UnityEngine.Events;

// Creates a simple timer.
public class Timer : MonoBehaviour
{
    [Header("Creates a simple timer.")]

    [Header("Whether the timer has started:")]
    public bool start = true;

    [Header("The current time:")]
    public float timer = 0;

    [Header("Where to start and end the time:")]
    public float startTime = 0;
    public float endTime = 10;

    [Header("Whether the timer will increment up or down:")]
    public TimerIncrement increment = TimerIncrement.Default;

    [Header("Whether the timer will stop, loop, or continue when it ends:")]
    public TimerLoop loop = TimerLoop.Stop;

    [Header("The scale applied to the timer:")]
    public float timeScale = 1;

    [Header("Timer events:")]
    public UnityEvent startEvents = null;
    public UnityEvent tickEvents = null;
    public UnityEvent stopEvents = null;
    public UnityEvent endEvents = null;
    public bool callEndEventsOnTick = false;
    private bool calledEndEvents = false;

    [Header("Debugging:")]
    public bool debugLogs = true;
    [SerializeField] private bool testTimer = false;

    // Timer incrementing enum
    public enum TimerIncrement { Default, Up, Down };

    // Timer looping enum
    public enum TimerLoop { Stop, Loop, Continue };


    // UNITY FUNCTIONS

    private void Start()
    {
        if (start)
        {
            StartTimer();
        }
    }

    private void Update()
    {
        Tick();
    }

    private void OnValidate()
    {
        if (testTimer)
        {
            testTimer = false;

            if (!start)
            {
                StartTimer();
            }
            else
            {
                StopTimer();
            }
        }
    }


    // TIMER CONTROL

    // Starts the timer
    public void StartTimer()
    {
        switch (increment)
        {
            case TimerIncrement.Default:

                if (startTime < endTime)
                {
                    if (timer >= endTime)
                    {
                        RestartTimer();
                    }
                    else
                    {
                        ResumeTimer();
                    }
                }
                else if (startTime > endTime)
                {
                    if (timer <= endTime)
                    {
                        RestartTimer();
                    }
                    else
                    {
                        ResumeTimer();
                    }
                }
                else
                {
                    ResumeTimer();
                }

                break;

            case TimerIncrement.Up:

                if (timer >= endTime)
                {
                    RestartTimer();
                }
                else
                {
                    ResumeTimer();
                }

                break;

            case TimerIncrement.Down:

                if (timer <= endTime)
                {
                    RestartTimer();
                }
                else
                {
                    ResumeTimer();
                }

                break;
        }
    }

    // Restarts the timer
    public void RestartTimer()
    {
        if (debugLogs) { print("Timer on object " + gameObject.name + " started!"); }

        start = true;

        timer = startTime;

        calledEndEvents = false;

        startEvents.Invoke();
    }

    // Resumes the timer from where it left off
    public void ResumeTimer()
    {
        if (debugLogs) { print("Timer on object " + gameObject.name + " resumed!"); }

        start = true;

        startEvents.Invoke();
    }

    // Stops the timer and returns the current time
    public float StopTimer()
    {
        if (debugLogs) { print("Timer on object " + gameObject.name + " stopped!"); }

        start = false;

        stopEvents.Invoke();

        return timer;
    }


    // DURING TIMER

    // The timer's tick
    private void Tick()
    {
        if (start)
        {
            if (debugLogs) { print("Timer on object " + gameObject.name + " is now " + ConvertTimerToString(':') + "."); }

            tickEvents.Invoke();

            switch (increment)
            {
                case TimerIncrement.Default:

                    if (startTime < endTime)
                    {
                        timer += Time.deltaTime * timeScale;

                        if (timer >= endTime)
                        {
                            End();
                        }
                    }
                    else if (startTime > endTime)
                    {
                        timer -= Time.deltaTime * timeScale;

                        if (timer <= endTime)
                        {
                            End();
                        }
                    }
                    else
                    {
                        End();
                    }

                    break;

                case TimerIncrement.Up:

                    timer += Time.deltaTime * timeScale;

                    if (timer >= endTime)
                    {
                        End();
                    }

                    break;

                case TimerIncrement.Down:

                    timer -= Time.deltaTime * timeScale;

                    if (timer <= endTime)
                    {
                        End();
                    }

                    break;
            }
        }
    }

    // The timer when reaching the end
    private void End()
    {
        switch (loop)
        {
            case TimerLoop.Stop:

                if (debugLogs) { print("Timer on object " + gameObject.name + " reached its end!"); }

                endEvents.Invoke();

                StopTimer();

                break;

            case TimerLoop.Loop:

                if (debugLogs) { print("Timer on object " + gameObject.name + " reached its end!"); }

                endEvents.Invoke();

                RestartTimer();

                break;

            case TimerLoop.Continue:

                if (!calledEndEvents || callEndEventsOnTick)
                {
                    if (debugLogs) { print("Timer on object " + gameObject.name + " reached its end!"); }

                    calledEndEvents = true;

                    endEvents.Invoke();
                }

                break;
        }
    }


    // TIMER TO STRING FUNCTIONS

    // Converts a given time into a readable string (like 00.00.00)
    public static string ConvertTimeToString(float time)
    {
        // Change timer float to a readable time value
        float seconds = time;

        string milliseconds = (seconds - ((int)seconds)).ToString();

        if (milliseconds.Length > 2)
        {
            milliseconds = milliseconds.Remove(0, 2);
        }

        while (milliseconds.Length > 2)
        {
            milliseconds = milliseconds.Remove(milliseconds.Length - 1, 1);
        }

        if (milliseconds.Length == 1)
        {
            milliseconds += "0";
        }

        int minutes = 0;

        while (seconds > 60)
        {
            minutes += 1;

            seconds -= 60;
        }

        if (seconds < 10 && minutes < 10)
        {
            return "0" + minutes.ToString() + ".0" + ((int)seconds).ToString() + "." + milliseconds;
        }
        else if (seconds < 10)
        {
            return minutes.ToString() + ".0" + ((int)seconds).ToString() + "." + milliseconds;
        }
        else if (minutes < 10)
        {
            return "0" + minutes.ToString() + "." + ((int)seconds).ToString() + "." + milliseconds;
        }
        else
        {
            return minutes.ToString() + "." + ((int)seconds).ToString() + "." + milliseconds;
        }
    }

    // Converts a given time into a readable string (like 00.00.00)
    public static string ConvertTimeToString(float time, char separator)
    {
        // Change timer float to a readable time value
        float seconds = time;

        string milliseconds = (seconds - ((int)seconds)).ToString();

        if (milliseconds.Length > 2)
        {
            milliseconds = milliseconds.Remove(0, 2);
        }

        while (milliseconds.Length > 2)
        {
            milliseconds = milliseconds.Remove(milliseconds.Length - 1, 1);
        }

        if (milliseconds.Length == 1)
        {
            milliseconds += "0";
        }

        int minutes = 0;

        while (seconds > 60)
        {
            minutes += 1;

            seconds -= 60;
        }

        if (seconds < 10 && minutes < 10)
        {
            return "0" + minutes.ToString() + separator + "0" + ((int)seconds).ToString() + separator + milliseconds;
        }
        else if (seconds < 10)
        {
            return minutes.ToString() + separator + "0" + ((int)seconds).ToString() + separator + milliseconds;
        }
        else if (minutes < 10)
        {
            return "0" + minutes.ToString() + separator + ((int)seconds).ToString() + separator + milliseconds;
        }
        else
        {
            return minutes.ToString() + separator + ((int)seconds).ToString() + separator + milliseconds;
        }
    }

    // Converts this timer's value into a readable string (like 00.00.00)
    public string ConvertTimerToString()
    {
        return ConvertTimeToString(timer);
    }

    // Converts this timer's value into a readable string (like 00.00.00)
    public string ConvertTimerToString(char separator)
    {
        return ConvertTimeToString(timer, separator);
    }


    // EXTRA FUNCTIONS

    // Destroy this script
    public void Destroy()
    {
        Destroy(this);
    }

    // Destroy this object
    public void DestroyObject()
    {
        Destroy(gameObject);
    }

    // Flip the increment of the timer
    public void Flip()
    {
        switch (increment)
        {
            case TimerIncrement.Default:

                float temporary = startTime;

                startTime = endTime;

                endTime = temporary;

                break;

            case TimerIncrement.Up:

                increment = TimerIncrement.Up;

                break;

            case TimerIncrement.Down:

                increment = TimerIncrement.Up;

                break;
        }
    }
}
