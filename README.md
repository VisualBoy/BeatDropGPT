![Discord Shield](https://discord.com/api/guilds/1041603212798599168/widget.png?style=shield) [Chat with us on Discord!](https://discord.gg/rp5cBDtGuM)

[![Logo](https://upload.wikimedia.org/wikipedia/commons/thumb/6/6f/Logo_of_Twitter.svg/20px-Logo_of_Twitter.svg.png)](https://twitter.com/BeatDropVis) [@BeatDropVis](https://twitter.com/BeatDropVis)

![Logo](https://github.com/OfficialIncubo/The-Improved-and-Modified-Version-of-BeatDrop-Music-Visualizer/raw/master/Logos/BeatDrop%20New%20Logo%20GitGub%20ver.png) (logo design by Incubo_)

# BeatDrop Music Visualizer

One standalone visualization, one improvement.
In this repo will fix the bug, adding new features and more stuff to BeatDrop Music Visualizer.
- This is a continued development because the original developer, Maxim Volskiy (@mvsoft74) has gone silent.

Things fixed:
* The y/n decision bug
* Keyboard function changes (F4: Show Preset Info, F5: Show FPS, F6: Show Rating, F1: Help)
* Help text changes
* Unlimited FPS, nTexSize to Auto, nCanvasStretch to 100 and more...
* ...many and many bugs squashed.

Features added:
* Always On Top Feature (F7 Hotkey)
* Multiple monitor stretch (Thanks to @milkdropper for the code - ALT + S Hotkey) 
* Now it can support up to 16 custom shapes and waves!
* Real-time toggling FPS by pressing F3!
* New waveforms (from 8 to 15)
* Transparency Mode
* Spout Support (thanks @leadedge for helping me)
* Hardcut Modes (F11 Hotkey)

Features to be added:
* Toggle 3D Support
* Getting BeatDrop's Song Title data from Windows Playback
* Blending the visualizer with Webcam (Example: [Webcam > Spout > NestDrop on Reddit](https://www.reddit.com/r/NestDrop/comments/rh6zew/webcam_spout_nestdrop/) - F2 Hotkey
* Double Preset Mode
* Playback Hotkeys that can be controlled on any media players
* Pressing 'C' to add random values of ret /= float3(r, g, b); in the final of the comp shader code (with 30% chance to add ret /= float3(bass, mid, treb));
* New blending transitions

Before compiling the code:
* Anyone who uses Visual Studio 2019 or higher, please change from debug to release and build it.

# BEFORE YOU RUN BEATDROP

Please download and install [DirectX End-User Runtime Web](https://www.microsoft.com/en-us/download/details.aspx?id=35) first.
BeatDrop now has a Spout integration! Download Spout: https://spout.zeal.co

# Featured Websites:

[![Logo](https://upload.wikimedia.org/wikipedia/commons/f/f4/Softpedia_logo.svg)](https://www.softpedia.com/get/Multimedia/Audio/Other-AUDIO-Tools/BeatDrop-Music-Visualizer.shtml)

[![Logo](https://alternativeto.net/static/icons/a2/org-icon.png)](https://alternativeto.net/software/beatdrop/about/)

[The Audio File](https://audio-file.org/2023/10/13/beatdrop-music-visualizer/)

[Spout Open-Source Projects](https://leadedge.github.io/spout-projects.html#OfficialIncubo)

---------------------------------------------------------------------------------------------------------------------------------------------

BeatDrop is a stand-alone implementation of the amazing Milkdrop2 Winamp plug-in.

It lets you experience the stunning visual 2D effects with your music player of choice. No additional configuration steps needed! Just start BeatDrop and play your music.

Use BeatDrop with your favourite

* Music player:
  [foobar2000](https://www.foobar2000.org/),
  [VLC media player](https://www.videolan.org/vlc/index.html),
  [Clementine](https://www.clementine-player.org/),
  [AIMP](https://www.aimp.ru/),
  ...

* Web-based player:
  [SoundCloud](https://soundcloud.com/),
  [YouTube](https://www.youtube.com/),
  [Vimeo](https://vimeo.com/),
  ...

* Internet Radio station:
  [SomaFM](https://somafm.com/),
  [DI.FM](https://www.di.fm/),
  [RauteMusik.FM](https://www.rm.fm/),
  ...

## System Requirements
* Windows 11, Windows 10, Windows 8.1, Windows 8, Windows 7, Windows Vista

* Minimum 2GB of RAM required

* WASAPI-compatible sound card

* DirectX 9 or higher - compatible GPU

* DirectX End-User [Runtimes](https://www.microsoft.com/en-us/download/details.aspx?id=8109) (also included in the installer) contains the required 32-bit helper libraries d3dx9_43.dll and d3dx9_31.dll

## Acknowledgements
Special thanks to:

* Ryan Geiss and Rovastar (John Baker) [official Milkdrop2 source code](https://sourceforge.net/projects/milkdrop2/)

* oO-MrC-Oo [XBMC plugin](https://github.com/oO-MrC-Oo/Milkdrop2-XBMC)

* Casey Langen [milkdrop2-musikcube](https://github.com/clangen/milkdrop2-musikcube)

* Matthew van Eerde [loopback-capture](https://github.com/mvaneerde/blog)

* and all the preset authors!

## License

[license]: #license

This repository is licensed under the 3-Clause BSD License ([LICENSE](LICENSE) or [https://opensource.org/licenses/BSD-3-Clause](https://opensource.org/licenses/BSD-3-Clause)) with the exception of where otherwise noted.

Although the original Matthew van Eerde's [loopback-capture](https://github.com/mvaneerde/blog) project didn't explicitly state the license, the author has been kind enough to provide the [license clarification](
https://blogs.msdn.microsoft.com/matthew_van_eerde/2014/11/05/draining-the-wasapi-capture-buffer-fully/)

> ### Sunny March 29, 2015 at 11:06 pm
> Hi. Just wondering is this open source? I'm looking for something like this for my school project.
>
> ### Maurits [MSFT] March 30, 2015 at 8:35 am
> @Sunny do with the source as you like.

All changes in this repository to the original Matthew's code are published either under the terms of BSD license or the license provided by original author.

## Contributions

Unless you explicitly state otherwise, any contribution intentionally submitted for inclusion in the work by you, shall be licensed as above.
