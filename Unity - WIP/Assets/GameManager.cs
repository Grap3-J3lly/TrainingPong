using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public static GameManager instance;
    public UIManager uiManager;
    public Paddle lastHitPaddle;

    public PlayerPaddle playerPaddle;
    public ComputerPaddle enemyPaddle;
    public Ball ball;

    public int playerScore = 0;
    public int enemyeScore = 0;
    public int gameOverScore = 10;
    public bool gameOver = false;

    private void Awake()
    {
        if(instance == null)
        {
            instance = this;
        }
        else
        {
            Destroy(this);
        }
        uiManager.Setup();
    }

    private void Update()
    {
        if(playerScore >= 10 || enemyeScore >= 10)
        {
            gameOver = true;
        }
    }

    public void HandleScoring()
    {
        if (lastHitPaddle == null)
        {
            Debug.LogError("No Paddle was Hit Previously");
            return;
        }

        if (lastHitPaddle.GetType() == typeof(PlayerPaddle))
        {
            ++playerScore;
            uiManager.UpdateScore(true, playerScore);
            enemyPaddle.IncreaseScaleFactor();
        }
        else
        {
            ++enemyeScore;
            uiManager.UpdateScore(false, enemyeScore);
        }

        if(!gameOver)
        {
            ball.ResetBall();
            ball.IncreaseBallSpeed();
        }
    }
}
