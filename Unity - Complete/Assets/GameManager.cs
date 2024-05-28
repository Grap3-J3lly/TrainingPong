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
    public int enemyScore = 0;
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
        gameOver = true;
    }

    private void Update()
    {
        if(playerScore == gameOverScore || enemyScore == gameOverScore)
        {
            gameOver = true;
            uiManager.OnGameOver(playerScore > enemyScore);
        }
    }

    public void StartGame()
    {
        gameOver = false;
        playerScore = 0;
        enemyScore = 0;
        ball.Setup();
        ball.ResetBall();
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
            ball.fireDirection = false;
        }
        else
        {
            ++enemyScore;
            uiManager.UpdateScore(false, enemyScore);
            ball.fireDirection = true;
        }

        if(!gameOver)
        {
            ball.ResetBall();
            ball.IncreaseBallSpeed();
        }
    }

    public void SwapLastHit()
    {
        if (lastHitPaddle == null)
        {
            return;
        }

        if (lastHitPaddle == playerPaddle)
        {
            lastHitPaddle = enemyPaddle;
        }
        else
        {
            lastHitPaddle = playerPaddle;
        }
    }
}
