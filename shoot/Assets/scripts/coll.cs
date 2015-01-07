using UnityEngine;
using System.Collections;

public class coll : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {

	}
	void OnCollisionEnter(Collision collision) {
		if (collision.gameObject.tag == "bullet") {
			distance shared = (distance)GameObject.Find("Main Camera").GetComponent("distance");
			shared.updateballs(2);
			//print ("bang");
			Destroy (gameObject, 0.0f);
		}
	}
}