using UnityEngine;
using System.Collections;
using System.IO;

public class NetworkInterpolatedTransform : MonoBehaviour
{
    NetworkSync netSync;

    // We store twenty states with "playback" information
    State[] m_BufferedState = new State[20];

    // Keep track of what slots are used
    int m_TimestampCount;

    bool first = true;
    double interpolationBackTime = 0.2;
    float extrapolationTime = 0.1f;

    float amp; //our current speed or amplitude of direction
        
    // Speed that we are moving at
    public float Speed
    {
        get
        {
            return amp;
        }
        set
        {
            if (netSync.owned)
            {
                amp = value;
            }
        }
    }

    internal struct State
    {
        internal double timestamp;
        internal Vector3 pos;
        internal Quaternion q;
    }


    void Awake()
    {
        netSync = GetComponent(typeof(NetworkSync)) as NetworkSync;

        netSync.getDataFunction = GetSyncData;
        netSync.setDataFunction = SetSyncData;

        interpolationBackTime = netSync.broadcastFrequency * 2;
        extrapolationTime = netSync.broadcastFrequency;
    }

    void Start()
    {
        if (netSync.owned || netSync.GetId() == -1)
        {
            this.enabled = false;
        }
    }

    void OnGainOwnership()
    {
        this.enabled = false;
    }
    void OnLoseOwnership()
    {
        this.enabled = true;
    }

    // Send data to the server about the position of this object
    public void GetSyncData(ref BinaryWriter aBinWriter)
    {
        //Debug.Log ("Getting Sync data " + transform.localPosition.z);

        aBinWriter.Write(amp);

        netSync.position = transform.localPosition;
        netSync.rotation = transform.localRotation;//Quaternion.EulerRotation(0, rot, 0);
    }

    // Get sync data from the server for where this object should be
    public void SetSyncData(ref BinaryReader aBinReader)
    {
        // Receive latest state information
        Vector3 pos = Vector3.zero;

        pos = netSync.position;

        //float syncamp = aBinReader.ReadSingle();
        aBinReader.ReadSingle();

        // Shift buffer contents, oldest data erased, 18 becomes 19, ... , 0 becomes 1
        for (int i = m_BufferedState.Length - 1; i >= 1; i--)
        {
            m_BufferedState[i] = m_BufferedState[i - 1];
        }

        // Save currect received state as 0 in the buffer, safe to overwrite after shifting
        State state = new State();
        state.timestamp = netSync.clientNet.GetTime();

        //Debug.LogWarning ("There's no timestamp info with UCNetwork SetSyncData");
        state.pos = pos;
        state.q = netSync.rotation;

        if (first)
        {
            first = false;
            transform.localPosition = pos;
            transform.localRotation = netSync.rotation; //Quaternion.Euler (0, rot, 0);
        }

        m_BufferedState[0] = state;

        // Increment state count but never exceed buffer size
        m_TimestampCount = Mathf.Min(m_TimestampCount + 1, m_BufferedState.Length);

        // Check integrity, lowest numbered state in the buffer is newest and so on
        for (int i = 0; i < m_TimestampCount - 1; i++)
        {
            if (m_BufferedState[i].timestamp < m_BufferedState[i + 1].timestamp)
                Debug.Log("State inconsistent");
        }

        //Debug.Log("stamp: " + info.timestamp + "my time: " + Network.time + "delta: " + (Network.time - info.timestamp));
    }
    
    // This only runs where the component is enabled, which is only on remote peers
    void Update()
    {
        double currentTime = netSync.clientNet.GetTime();
        double interpolationTime = currentTime - interpolationBackTime;

        // We have a window of interpolationBackTime where we basically play 
        // By having interpolationBackTime the average ping, you will usually use interpolation.
        // And only if no more data arrives we will use extrapolation

        // Use interpolation
        // Check if latest state exceeds interpolation time, if this is the case then
        // it is too old and extrapolation should be used
        if (m_BufferedState[0].timestamp > interpolationTime)
        {
            //Debug.Log("Interpolating");
            for (int i = 0; i < m_TimestampCount; i++)
            {
                // Find the state which matches the interpolation time (time+0.1) or use last state
                if (m_BufferedState[i].timestamp <= interpolationTime || i == m_TimestampCount - 1)
                {
                    // The state one slot newer (<100ms) than the best playback state
                    State rhs = m_BufferedState[Mathf.Max(i - 1, 0)];
                    // The best playback state (closest to 100 ms old (default time))
                    State lhs = m_BufferedState[i];

                    // Use the time between the two slots to determine if interpolation is necessary
                    double length = rhs.timestamp - lhs.timestamp;
                    float t = 0.0F;
                    // As the time difference gets closer to 100 ms t gets closer to 1 in 
                    // which case rhs is only used
                    if (length > 0.0001)
                        t = (float)((interpolationTime - lhs.timestamp) / length);

                    // if t=0 => lhs is used directly
                    transform.localPosition = Vector3.Lerp(lhs.pos, rhs.pos, t);
                    transform.localRotation = Quaternion.Slerp(lhs.q, rhs.q, t);

                    return;
                }
            }
        }
        else
        {
            // Extrapolation logic

            //Debug.Log ("Extrapolating");
            State latest = m_BufferedState[0];
            Vector3 velocity = new Vector3();
            //Quaternion rotationSpeed = new Quaternion();

            if (m_BufferedState.Length > 1 && m_TimestampCount > 1)
            {
                velocity = (latest.pos - m_BufferedState[1].pos) / (float)interpolationTime;
                /*
                rotationSpeed = (latest.q - m_BufferedState[1].q) / extrapolationTime;
                m_BufferedState[1].q
                */
            }
            /*
            transform.localPosition = latest.pos;
            transform.localRotation = latest.q;
            */

            //Debug.Log("Speed = " + velocity.magnitude);
            //float f = (Time.deltaTime * netSync.broadcastFrequency) + 1f;
            float f = extrapolationTime;
            transform.localRotation = Quaternion.Slerp(transform.localRotation, latest.q, f); //tq; //Mathf.LerpAngle (mo.rot, trot, 0.6f);
            transform.localPosition = Vector3.Lerp(transform.localPosition, latest.pos + velocity, f);
        }
    }

    public void SetPosition(Vector3 aPosition)
    {
        transform.localPosition = aPosition;
        m_BufferedState = new State[20];
    }
    public void SetRotation(Quaternion aRotation)
    {
        transform.localRotation = aRotation;
    }
}
