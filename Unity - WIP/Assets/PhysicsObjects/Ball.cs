using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ball : MonoBehaviour
{
    bool directionToStart = false;
    public float startSpeed = 10f;
    public float maxSpeed = 100f;
    public Vector2 mapRange = new Vector2(-5, 5);
    Rigidbody2D rb;

    private void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        float direction = UnityEngine.Random.Range(0f, 1f);
        if (direction >= .5f) directionToStart = true;
        else directionToStart = false;

        Vector2 startVelocity = new Vector2(UnityEngine.Random.Range(mapRange.x, mapRange.y), startSpeed);
        if(!directionToStart)
        {
            startVelocity = new Vector2(startVelocity.x, startVelocity.y * -1);
        }
        rb.velocity = startVelocity;
        Debug.Log("Start Vel: " + startVelocity);
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
        }
    }

}
