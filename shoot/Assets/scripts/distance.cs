using UnityEngine;
using System.Collections;

public class distance : MonoBehaviour {
	public GUIStyle style;
	// Use this for initialization
	private Rect score;
	public int m_score;
	private Rect ball;
	Rect gameover;

	bool status;

	public int m_ball;
	
	void Start () {
		m_score = 0;
		status = true;
		score = new Rect(10, 30, 100, 50);
	
		m_ball = 24;
		ball = new Rect(300, 30, 100, 50);

		gameover = new Rect (-100, -100, 100, 50);

		style.fontSize = 50;
		style.normal.textColor = Color.blue;
	}
	
	// Update is called once per frame
	void Update () {
		if (true == status)
			m_score ++;
	}

	public void stop() {
		status = false;
		GameOver ();
	}

	void OnGUI()
	{
		GUI.color = Color.blue;
		GUI.Label(score, "score: " + m_score, style);
		GUI.Label(ball, "balls: " + m_ball, style);
		GUI.Label (gameover, "Game Over", style);
	}

	public void GameOver() {
		gameover.position = new Vector2 (400, 150);
	}

	public void updateballs(int add) {
		m_ball += add;
	}
}