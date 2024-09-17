using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class TitleScreenLogic : MonoBehaviour {

    public Text server;
    public Text port;
    public ExampleClient client;

    public void Connect()
    {
        client.ConnectToServer(server.text, int.Parse(port.text));
    }
}
