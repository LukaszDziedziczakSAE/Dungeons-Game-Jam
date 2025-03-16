using UnityEngine;
using UnityEngine.InputSystem;

public class InputReader : MonoBehaviour, Controls.IPlayerActions
{
    Controls controls;

    [field: SerializeField] public Vector2 Move {  get; private set; }

    private void Awake()
    {
        controls = new Controls();

        controls.Player.Enable();
        controls.Player.SetCallbacks(this);
    }

    public void OnMove(InputAction.CallbackContext context)
    {
        Move = context.ReadValue<Vector2>();
    }
}
