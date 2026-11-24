# GTA:SA Linux Trainer Example
This is a very barebones cli trainer that hooks into GTA San Andreas running under Wine/Proton; this project is meant to serve as an example on how to read and modify memory of a process (`memory` module), as well as how to patch its code (`process` module) while it's running.

This project was created for educational purposes only.

Check out the [complete version](https://github.com/Rikaisan/gta-sa-linux-trainer-rs) as well! It's made in Rust, so it could also serve as a guide on how to do the same thing using FFI.
# Considerations
1. Make sure GTA:SA is downgraded to version 1.0, you can do it using the [GTA SA Open Downgrader](https://github.com/xxanqw/gtasa-open-downgrader)
2. Make sure the game is NOT modded
3. Make sure to disable ALSR for the game by setting the steam/wine/proton launch options to: `setarch x86_64 -R %command%`