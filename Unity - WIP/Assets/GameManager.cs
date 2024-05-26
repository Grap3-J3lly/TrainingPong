using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public static GameManager instance;
    public UIManager uiManager;
    public Paddle lastHitPaddle;

    public int playerScore = 0;
    public int enemyeScore = 0;

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

    public void UpdateScore()
    {
        if (lastHitPaddle == null)
        {
            Debug.LogError("No Paddle was Hit Previously");
            return;
        }

        if(lastHitPaddle.GetType() == typeof(PlayerPaddle))
        {
            ++playerScore;
            uiManager.UpdateScore(true, playerScore);
        }
        else
        {
            ++enemyeScore;
            uiManager.UpdateScore(false, enemyeScore);
        }
    }
}
