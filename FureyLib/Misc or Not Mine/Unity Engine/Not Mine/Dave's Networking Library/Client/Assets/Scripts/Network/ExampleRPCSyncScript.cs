using UnityEngine;
using System.Collections;
using System.IO;

[RequireComponent(typeof(NetworkSync))]
public class ExampleRPCSyncScript : MonoBehaviour {

    // Callback that happens
    void NetworkInitialized() {
        // Get the NetworkSync component, set up our function calls
        NetworkSync sync = gameObject.GetComponent(typeof(NetworkSync)) as NetworkSync;
        if (sync) {
            sync.getDataFunction = GetSyncData;
            sync.setDataFunction = SetSyncData;

            if (sync.owned) {
                GetComponent<Renderer>().material.color = Color.green;
            } else {
                GetComponent<Renderer>().material.color = Color.grey;
            }
        } else {
            Debug.LogWarning("Unable to get Sync component");
        }
    }

    // Example RPCs
    public void TestRPC(int i, float f, string s) {
        Debug.Log("ExampleRPCSyncScript::TestRPC called with " + i.ToString() + " " + f.ToString() + " " + s);
        StartCoroutine(PulseColor());
    }

    IEnumerator PulseColor() {
        for (int i=0; i<20; i++) {
            GetComponent<Renderer>().material.color = new Color(Random.Range(0.0f, 1.0f), Random.Range(0.0f, 1.0f), Random.Range(0.0f, 1.0f));
            yield return new WaitForSeconds(0.1f);
        }

        NetworkSync sync = gameObject.GetComponent(typeof(NetworkSync)) as NetworkSync;
        if (sync) {
            if (sync.owned) {
                GetComponent<Renderer>().material.color = Color.green;
            } else {
                GetComponent<Renderer>().material.color = Color.grey;
            }
        } else {
            GetComponent<Renderer>().material.color = Color.red;
        }
    }

    // Example Sync functionality
    public void GetSyncData(ref BinaryWriter aBinWriter) {
        aBinWriter.Write(transform.position.x);
        aBinWriter.Write(transform.position.y);
        aBinWriter.Write(transform.position.z);
    }

    public void SetSyncData(ref BinaryReader aBinReader) {
        float newX = aBinReader.ReadSingle();
        float newY = aBinReader.ReadSingle();
        float newZ = aBinReader.ReadSingle();
        transform.position = new Vector3(newX, newY, newZ);
    }

    public void OnGainOwnership() {
        GetComponent<Renderer>().material.color = Color.green;
    }

    public void OnLoseOwnership() {
        GetComponent<Renderer>().material.color = Color.gray;
    }
}
