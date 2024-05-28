using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class InputManager : MonoBehaviour
{
    //------------------------------------------------------
    //                  VARIABLES
    //------------------------------------------------------
    #region

    // - - - - - - - Static Variables - - - - - - -
    public static InputManager instance;

    // Input Info
    Controls _controls;
    public Controls PControls
    {
        get
        {
            if (_controls == null)
            {
                _controls = new Controls();
            }
            return _controls;
        }
    }

    #endregion

    //------------------------------------------------------
    //              STANDARD FUNCTIONS
    //------------------------------------------------------
    #region

    void Awake()
    {
        _controls = new Controls();
        InstanceSetup();
    }

    void OnEnable()
    {
        _controls.Enable();
    }

    void OnDisable()
    {
        _controls.Disable();
    }

    #endregion

    //------------------------------------------------------
    //              SETUP FUNCTIONS
    //------------------------------------------------------
    #region

    /// <summary>
    /// Creates and ensures only one instance of the Manager exists
    /// </summary>
    void InstanceSetup()
    {
        if (instance && instance != this)
        {
            Destroy(gameObject);
        }
        else
        {
            instance = this;
        }
    }

    #endregion
}
