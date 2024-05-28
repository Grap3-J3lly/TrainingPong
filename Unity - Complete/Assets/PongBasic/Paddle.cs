using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Paddle : MonoBehaviour
{
    public float defaultPaddleSpeed = 10f;
    protected Rigidbody2D rb;
    protected bool hitWall = false;
    protected Vector2 previousLocation = Vector2.zero;

    public void Awake()
    {
        rb = GetComponent<Rigidbody2D>();
    }

    public void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.tag == "wall")
        {
            Debug.Log("Entered Wall Collision");
            hitWall = true;
            rb.position = previousLocation;
        }
    }

    public void OnCollisionExit2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "wall")
        {
            Debug.Log("Left Wall Collision");
            hitWall = false;
        }
    }
}
