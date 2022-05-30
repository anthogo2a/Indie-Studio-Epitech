/*
** EPITECH PROJECT, 2021
** ManetteInput
** File description:
** ManetteInput
*/

#include <map>
#include <iostream>
#include "ManetteInput.hpp"
#include "raylib.h"

ManetteInput::ManetteInput(int manette_id)
{
    _player_id = -1;
    _action = NULL_ACTION;
    _manette_id = manette_id;
}

void ManetteInput::linkPlayer(int player_id)
{
    _player_id = player_id;
}

Event ManetteInput::press()
{
    _action = NULL_ACTION;

    float offset_triggered = 0.3;

    int axis_x = GetGamepadAxisMovement(_manette_id, GAMEPAD_AXIS_LEFT_X); // gauche droite
    int axis_y = GetGamepadAxisMovement(_manette_id, GAMEPAD_AXIS_LEFT_Y); // haut bas
    int left = (axis_x >= 0) ? 0 : -axis_x, right = (axis_x < 0) ? 0 : axis_x;
    int up = (axis_y >= 0) ? 0 : -axis_y, down = (axis_y < 0) ? 0 : axis_y;
    int tmp = 0;

    if (right > offset_triggered && right > tmp) {
        _action = RIGHT;
        tmp = right;
    } if (left > offset_triggered && left > tmp) {
        _action = LEFT;
        tmp = left;
    } if (up > offset_triggered && up > tmp) {
        _action = UP;
        tmp = left;
    } if (down > offset_triggered && down > tmp) {
        _action = DOWN;
        tmp = down;
    }
    if (IsGamepadButtonPressed(_manette_id, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) _action = A_BUTTON;
    if (IsGamepadButtonPressed(_manette_id, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) _action = A_BUTTON;
    if (IsGamepadButtonPressed(_manette_id, GAMEPAD_BUTTON_MIDDLE_RIGHT)) _action = PAUSE;
    if (IsGamepadButtonDown(_manette_id, GAMEPAD_BUTTON_LEFT_FACE_UP)) _action = UP;
    if (IsGamepadButtonDown(_manette_id, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) _action = DOWN;
    if (IsGamepadButtonDown(_manette_id, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) _action = RIGHT;
    if (IsGamepadButtonDown(_manette_id, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) _action = LEFT;

    if (_action == PAUSE) return PAUSE_EVENT;
    return (NULL_EVENT);
}

Action ManetteInput::getAction()
{
    return (_action);
}

bool ManetteInput::isFree()
{
    if (_player_id != -1)
        return (false);
    return (true);
}
