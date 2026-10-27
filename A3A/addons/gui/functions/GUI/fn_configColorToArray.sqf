/*
Maintainer: DoomMetal
    Converts colors defined in mission config to arrays usable in sqf.
    From this:
      {1,0,0,1}
    To this:
      [1,0,0,1]

    No, this doesn't do the same thing as BIS_fnc_colorConfigToRGBA.

Arguments:
    <CODE|STRING> The color from the config, either the code `{1,0,0,1}` or its string form (QUOTE(A3A_COLOR_xxx)).

Return Value:
    <ARRAY<SCALAR>> The color as an array

Scope: Any, Local Arguments, Local Effect
Environment: Any
Public: Yes
Dependencies:
    None

Example:
    [QUOTE(A3A_COLOR_BLACK)] call A3A_fnc_configColorToArray; // [0,0,0,1]
    [{0,0,0,1}] call A3A_fnc_configColorToArray; // [0,0,0,1]
*/

private _configColor = _this select 0;
private _configColorAsString = if (_configColor isEqualType "") then { _configColor } else { str _configColor };
private _colorArrayString = "[" + (_configColorAsString select [1, (count _configColorAsString) -2]) + "]";
call compile _colorArrayString;
