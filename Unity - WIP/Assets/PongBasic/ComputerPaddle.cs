using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ComputerPaddle : Paddle
{
    public float bufferZone = 5f;
    public Rigidbody2D ball;
    public float minScaleFactor = 1;
    public float maxScaleFactor = 10;
    public float scaleFactor = 2f;

    private void Start()
    {
        scaleFactor = minScaleFactor;
        GameManager.instance.lastHitPaddle = this;
    }

    private void FixedUpdate()
    {
        HandleMovement();
    }

    private void HandleMovement()
    {
        // If ball is coming towards compPaddle
        Vector2 movementDirection = Vector2.zero;
        float paddleSpeed = defaultPaddleSpeed;
        previousLocation = rb.position;
        if (ball.velocity.y > 0)
        {

            // Determine direction to move
            if (ball.position.x > rb.position.x + (bufferZone / 2) && !hitWall)
            {
                movementDirection = Vector2.right;
            }
            if (ball.position.x < rb.position.x - (bufferZone / 2) && !hitWall)
            {
                movementDirection = Vector2.left;
            }

            // Adjust movement speed based off distance (prevents jittering)
            paddleSpeed = (Mathf.Abs(ball.position.x - rb.position.x) / defaultPaddleSpeed) * scaleFactor;
        }
        // Reset Position
        else
        {
            if (rb.position.x > 0 + (bufferZone / 2))
            {
                movementDirection = Vector2.left;
            }
            if (rb.position.x < 0 - (bufferZone / 2))
            {
                movementDirection = Vector2.right;
            }

            Vector2 centerPosition = new Vector2(0, rb.position.y);
            paddleSpeed = (Vector2.Distance(rb.position, centerPosition) / defaultPaddleSpeed) * scaleFactor;
        }

        movementDirection *= paddleSpeed;
        rb.MovePosition(rb.position + (movementDirection * Time.deltaTime));
    }
}
