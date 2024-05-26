using TMPro;
using UnityEngine;

public class UIManager : MonoBehaviour
{
    private GameManager gameManager;
    public TextMeshProUGUI playerScore;
    public TextMeshProUGUI enemyScore;

    public void Setup()
    {
        gameManager = GameManager.instance;
        playerScore.text = gameManager.playerScore.ToString();
        enemyScore.text = gameManager.enemyeScore.ToString();
    }

    public void UpdateScore(bool updatePlayer, int newScore)
    {
        if (updatePlayer)
        {
            playerScore.text = newScore.ToString();
        }
        else
        {
            enemyScore.text = newScore.ToString();
        }
    }

}
