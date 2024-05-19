using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ComputerPaddle : Paddle
{
    public float bufferZone = 5f;
    public Rigidbody2D ball;
    private void FixedUpdate()
    {
        // If ball is coming towards compPaddle
        if(ball.velocity.y > 0)
        {
            if(ball.position.x > transform.position.x + (bufferZone/2))
            {
                Debug.Log("1");
                rb.velocity = Vector2.right * paddleSpeed;
            }
            else if(ball.position.x < transform.position.x - (bufferZone/2))
            {
                Debug.Log("2");
                rb.velocity = Vector2.left * paddleSpeed;
            }
            else
            {
                rb.velocity = Vector2.zero;
            }
        }
        else
        {
            if(transform.position.x > 0 + (bufferZone/2))
            {
                Debug.Log("3");
                rb.velocity = Vector2.left * paddleSpeed;
            }
            else if(transform.position.x < 0 - (bufferZone/2))
            {
                Debug.Log("4");
                rb.velocity = Vector2.right * paddleSpeed;
            }
            else
            {
                rb.velocity = Vector2.zero;
            }
        }
    }
}
