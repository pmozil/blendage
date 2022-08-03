# This is a fork of dwl with some added functions

Right now there's:
- inverse dynamic tiling
- dynamic config with lua in development

# blendage - Wayland compositor

Join us on our [Discord server](https://discord.gg/jJxZnrGPWN)!

Blendage is a compact, hackable compositor for Wayland based on [wlroots](https://gitlab.freedesktop.org/wlroots/wlroots/). It is intended to fill the same space in the Wayland world that dwm does in X11, primarily in terms of philosophy, and secondarily in terms of functionality. Like dwm, blendage is:

- Easy to understand, hack on, and extend with patches
- One C source file (or a very small number) configurable via `config.h`
- Limited to 2000 SLOC to promote hackability
- Tied to as few external dependencies as possible

- Any features provided by dwm/Xlib: simple window borders, tags, keybindings, client rules, mouse move/resize.
- Configurable multi-monitor layout support, including position and rotation
- Configurable HiDPI/multi-DPI support
- Idle-inhibit protocol which lets applications such as mpv disable idle monitoring
- Provide information to external status bars via stdout/stdin
- Urgency hints via xdg-activate protocol
- Support screen lockers via input-inhibitor protocol
- Various Wayland protocols
- XWayland support as provided by wlroots (can be enabled in `config.mk`)
- Zero flickering - Wayland users naturally expect that "every frame is perfect"
- Layer shell popups (used by Waybar)
- Damage tracking provided by scenegraph API

Features under consideration (possibly as patches) are:

- Protocols made trivial by wlroots
- Client-side decoration
- Animations and visual effects
- keyboard, keybinding and monitor config in lua
- implement a socket server so as to support sway workspaces and keyboard layout


## Building blendage

Blendage has three dependencies: lua, wlroots and wayland-protocols. Simply install these (and their `-devel` versions if your distro has separate development packages) and run `make`.

To disable XWayland, you should also install xorg-xwayland and comment its flag in `config.mk`.

## Configuration

Some configuration is done by editing `config.h` and recompiling, in the same manner as dwm. There is no way to separately restart the window manager in Wayland without restarting the entire display server, so any changes will take effect the next time blendage is executed.

You can also edit `~/.config/blend/rc.lua` and set variable with the same names as in `config.h` with the function `set_var`

## Running blendage

Belndage can be run on any of the backends supported by wlroots. This means you can run it as a separate window inside either an X11 or Wayland session, as well as directly from a VT console. Depending on your distro's setup, you may need to add your user to the `video` and `input` groups before you can run blendage on a VT.

When `blend` is run with no arguments, it will launch the server and begin handling any shortcuts configured in `config.h` and `~/.config/blend/rc.lua`. There is no status bar or other decoration initially; these are instead clients that can be run within the Wayland session.

If you would like to run a script or command automatically at startup, you can specify the command using the `-s` option. This command will be executed as a shell command using `/bin/sh -c`.  It serves a similar function to `.xinitrc`, but differs in that the display server will not shut down when this process terminates. Instead, blend will send this process a SIGTERM at shutdown and wait for it to terminate (if it hasn't already). This makes it ideal for execing into a user service manager like [s6](https://skarnet.org/software/s6/), [anopa](https://jjacky.com/anopa/), [runit](http://smarden.org/runit/faq.html#userservices), or [`systemd --user`](https://wiki.archlinux.org/title/Systemd/User).

Note: The `-s` command is run as a *child process* of blend, which means that it does not have the ability to affect the environment of blend or of any processes that it spawns. If you need to set environment variables that affect the entire blendage session, these must be set prior to running blendage.  For example, Wayland requires a valid `XDG_RUNTIME_DIR`, which is usually set up by a session manager such as `elogind` or `systemd-logind`.  If your system doesn't do this automatically, you will need to configure it prior to launching `blend`, e.g.:

    export XDG_RUNTIME_DIR=/tmp/xdg-runtime-$(id -u)
    mkdir -p $XDG_RUNTIME_DIR
    blend

### Status information

Information about selected layouts, current window title, and selected/occupied/urgent tags is written to the stdin of the `-s` command (see the `printstatus()` function for details).  This information can be used to populate an external status bar with a script that parses the information.  Failing to read this information will cause blendage to block, so if you do want to run a startup command that does not consume the status information, you can close standard input with the `<&-` shell redirection, for example:

    blend -s 'foot --server <&-'

If your startup command is a shell script, you can achieve the same inside the script with the line

    exec <&-

Existing dwl-specific status bars and dwl-specific scripts for other status bars include:
- [somebar](https://sr.ht/~raphi/somebar/) status bar designed for dwl
- [dtaobarv2.sh](https://cdn.discordapp.com/attachments/792078050024095745/862428883423723560/dtaobarv2.sh) for use with [dtao](https://github.com/djpohly/dtao) (See "Pinned Messages" on the "customizations" channel of the [dwl Discord server](https://discord.gg/jJxZnrGPWN) for details.)
- [dwlbar.sh](https://cdn.discordapp.com/attachments/792078050024095745/810926218529472592/dwlbar.sh) for use with [waybar](https://github.com/Alexays/Waybar) (See "Pinned Messages" on the "customizations" channel of the  [dwl Discord server](https://discord.gg/jJxZnrGPWN) for details.)
- [waybar-dwl](https://codeberg.org/fauxmight/waybar-dwl.git) for use with [waybar](https://github.com/Alexays/Waybar)
- [dwl-tags.sh](https://codeberg.org/novakane/yambar/src/branch/master/examples/scripts/dwl-tags.sh) for use with [yambar](https://codeberg.org/dnkl/yambar)
- [waybar-dwl.sh](https://gitee.com/guyuming76/personal/tree/dwl/gentoo/waybar-dwl) for use with [waybar](https://github.com/Alexays/Waybar) (ACCESS TO THIS SCRIPT REQUIRES gitee.com LOGIN!)

## Replacements for X applications

You can find a [list of Wayland applications on the sway wiki](https://github.com/swaywm/sway/wiki/i3-Migration-Guide).
