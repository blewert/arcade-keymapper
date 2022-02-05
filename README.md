# Arcade Keymapper
A keymapper built in C++, using Windows low-level keyboard hooks to do several things:

- Reset & boot initial kiosk client for the arcade UI
- Fix enumeration issues by prompting user-based enumeration of joypads, for virtual keymapping
- Auto refreshing arcade kiosk host processes after X amount of idle time
- Provide retro-themed GUI prompts for users of the arcade kiosks

## More detail
This is the keymapper that runs on the arcade kiosks, that takes joypad button inputs and maps them to virtual key presses. It does this by tricking the host OS (Windows) into thinking that a key was pressed when it was not. Why do we map to keys in the first place? Well, tracking joypads and their enumeration dynamically is a big hassle. It is instead easier to map the joypad inputs to keys, and that way, there is cross-platform support for inputs. WebGL doesn't play so great with joypad inputs either.

Virtual axes (e.g. left/right/up/down) are also mapped to keys, again, to make the process for input checking easier. Using this approach, we can also check when the last key was pressed without native `windows.h` calls from anywhere, which is useful when following development guidelines for the arcades.
