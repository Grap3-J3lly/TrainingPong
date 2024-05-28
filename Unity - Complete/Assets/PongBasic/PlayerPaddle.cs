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
        InputManager.instance.PControls.Default.Quit.performed += OnQuit;
    }

    private void OnStartMovement(InputAction.CallbackContext context)
    {
        if(!GameManager.instance || GameManager.instance.gameOver)
        {
            moveValue = 0;
            return;
        }
        moveValue = context.ReadValue<float>();
    }

    private void OnEndMovement(InputAction.CallbackContext context)
    {
        //if (!InputManager.instance.PControls.Default.Movement.IsInProgress())
        //{
        //    rb.velocity = Vector2.zero;
        //}
    }

    private void OnQuit(InputAction.CallbackContext context)
    {
        Application.Quit();
    }
}
