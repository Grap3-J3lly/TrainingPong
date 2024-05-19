using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class PlayerPaddle : Paddle
{
    bool movingRight = true;
    
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
            Vector2 movementForce = Vector2.zero;
            if (movingRight) { movementForce = Vector2.right; }
            else { movementForce = Vector2.left; }
            movementForce *= paddleSpeed;

            rb.velocity = movementForce;
        }
    }

    private void BindToInputSystem()
    {
        InputManager.instance.PControls.Default.Movement.started += OnStartMovement;
        InputManager.instance.PControls.Default.Movement.canceled += OnEndMovement;
    }

    private void OnStartMovement(InputAction.CallbackContext context)
    {
        float result = context.ReadValue<float>();
        if (result < 0) movingRight = false;
        else movingRight = true;
    }

    private void OnEndMovement(InputAction.CallbackContext context)
    {
        if (!InputManager.instance.PControls.Default.Movement.IsInProgress())
        {
            rb.velocity = Vector2.zero;
        }
    }
}
