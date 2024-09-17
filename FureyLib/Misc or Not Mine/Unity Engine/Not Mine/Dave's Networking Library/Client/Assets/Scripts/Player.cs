using UnityEngine;
using System.Collections;

public class Player : MonoBehaviour {

    float speed = 5;

    // Update is called once per frame
    void Update()
    {
        if (GetComponent<NetworkSync>().owned)
        {
            Vector3 movement = new Vector3(Input.GetAxis("Horizontal") * speed * Time.deltaTime, Input.GetAxis("Vertical") * speed * Time.deltaTime, 0);
            transform.position += movement;
        }
    }
}
