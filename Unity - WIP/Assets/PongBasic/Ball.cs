using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ball : MonoBehaviour
{
    public Vector2 startLocation = Vector2.zero;
    bool directionToStart = false;
    public float startSpeed = 5f;
    public float maxSpeed = 50f;
    public Vector2 mapRange = new Vector2(-5, 5);
    Rigidbody2D rb;

    private void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        ResetBall();
    }

    private void ResetBall()
    {
        rb.position = startLocation;

        Vector2 startVelocity = new Vector2(UnityEngine.Random.Range(mapRange.x, mapRange.y), startSpeed);
        if (!directionToStart)
        {
            startVelocity = new Vector2(startVelocity.x, startVelocity.y * -1);
        }
        rb.velocity = startVelocity;
    }

    private void FixedUpdate()
    {
        if (rb.velocity.x > maxSpeed)
        {
            rb.velocity = new Vector2(maxSpeed, rb.velocity.y);
        }
        if(rb.velocity.y > maxSpeed)
        {
            rb.velocity = new Vector2(rb.velocity.x, maxSpeed);
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.tag == "wall")
        {
            Debug.Log("Hit a wall");
            Vector2 velocity = new Vector2(-rb.velocity.x, rb.velocity.y);
            rb.velocity = velocity;
        }

        if(collision.gameObject.tag == "paddle")
        {
            Debug.Log("Hit a paddle");

            float newXVelocity = rb.velocity.x + collision.gameObject.GetComponent<Rigidbody2D>().velocity.x;
            Vector2 velocity = new Vector2(newXVelocity, -rb.velocity.y);
            rb.velocity = velocity;
            GameManager.instance.lastHitPaddle = collision.gameObject.GetComponent<Paddle>();
            
        }

        if(collision.gameObject.tag == "goal")
        {
            GameManager.instance.UpdateScore();
            ResetBall();
        }
    }

}
