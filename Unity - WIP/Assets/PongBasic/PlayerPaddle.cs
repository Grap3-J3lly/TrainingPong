using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class PlayerPaddle : Paddle
{
    float moveValue = 0;
    
    private void Awake()
    {
        base.Awake();
        BindToInputSystem();
    }

    // Update is called once per frame
    private void Update()
    {   
        
    }

    private void FixedUpdate()
    {
        if (InputManager.instance.PControls.Default.Movement.IsInProgress())
        {
            if(moveValue == 0) { return; }
            Vector2 movementForce = Vector2.zero;
            previousLocation = rb.position;

            if (moveValue > 0 && !hitWall) { movementForce = Vector2.right; }
            if (moveValue < 0 && !hitWall) { movementForce = Vector2.left; }
            
            movementForce *= defaultPaddleSpeed;

            rb.MovePosition(rb.position + (movementForce * Time.deltaTime));
        }
    }

    private void BindToInputSystem()
    {
        InputManager.instance.PControls.Default.Movement.started += OnStartMovement;
        InputManager.instance.PControls.Default.Movement.canceled += OnEndMovement;
    }

    private void OnStartMovement(InputAction.CallbackContext context)
    {
        moveValue = context.ReadValue<float>();
    }

    private void OnEndMovement(InputAction.CallbackContext context)
    {
        //if (!InputManager.instance.PControls.Default.Movement.IsInProgress())
        //{
        //    rb.velocity = Vector2.zero;
        //}
    }
}
