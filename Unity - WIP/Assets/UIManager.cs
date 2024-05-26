using TMPro;
using UnityEngine;

public class UIManager : MonoBehaviour
{
    private GameManager gameManager;
    public TextMeshProUGUI playerScore;
    public TextMeshProUGUI enemyScore;

    public GameObject mainMenu;
    public GameObject gameOverScreen;
    public TextMeshProUGUI gameOverText;

    public void Setup()
    {
        gameManager = GameManager.instance;
        mainMenu.SetActive(true);
        gameOverScreen.SetActive(false);
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

    public void OnStartPressed()
    {
        mainMenu.SetActive(false);
        gameOverScreen.SetActive(false);
        GameManager.instance.StartGame();
        playerScore.text = gameManager.playerScore.ToString();
        enemyScore.text = gameManager.enemyScore.ToString();
    }

    public void OnQuitPressed()
    {
        Application.Quit();
    }

    public void OnGameOver(bool playerWin)
    {
        gameOverScreen.SetActive(true);
        if (playerWin)
        {
            gameOverText.text = "YOU WIN";
        }
        else
        {
            gameOverText.text = "YOU LOSE";
        }
    }
}
