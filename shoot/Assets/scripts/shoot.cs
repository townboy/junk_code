using UnityEngine;
using System.Collections;

public class shoot : MonoBehaviour {

	int cnt = 0;
	// Use this for initialization
	void Start () {
		status = true;
	}

	public GameObject bullet;
	public GameObject block;
	bool status;

	// Update is called once per frame
	void Update () {
		float speed = 0.05f;

		if (false == status)
			return;
		transform.position += new Vector3 (0, 0, speed);
	
		distance shared = (distance)GameObject.Find("Main Camera").GetComponent("distance");

		cnt ++;
		if (0 == cnt % 100) {
			float pos = Random.Range (970, 1030);
			float dis = Random.Range (50, 100);
			GameObject ttt = (GameObject)Instantiate (block, (new Vector3(pos, 10, dis + transform.position.z) ), transform.rotation);
		}
		if(0 == cnt % 300)
			shared.updateballs(-1);


		if (Input.GetButtonDown ("Fire1")) {
			shared.updateballs(-1);

			if(shared.m_ball < 0) {
				shared.stop();
				status = false;
			}
	

			Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
		//	print(ray);

			GameObject n = (GameObject)Instantiate (bullet, transform.position, transform.rotation);
			Vector3 fwd = transform.TransformDirection(Vector3.forward);
			float force = bullet.rigidbody.mass * 1500;
			n.rigidbody.AddForce(force * ray.direction);
		}
	}
}