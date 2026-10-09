> **Note from this fork (coah80/wii-ipl)**
>
> original doesnt like ai commits, so im forking to not disturb them. :)
>
> This is a personal fork for AI-assisted matching work. The 4.3U decompilation
> is complete. No pull requests are opened against upstream, ever.

<!--- Github Actions Badge -->

[Build Status]: https://github.com/coah80/wii-ipl/actions/workflows/readme-progress.yml/badge.svg?branch=main
[actions]: https://github.com/coah80/wii-ipl/actions/workflows/readme-progress.yml

<!--- Discord Badge -->

[Discord Badge]: https://img.shields.io/discord/727908905392275526?color=%237289DA&logo=discord&logoColor=%23FFFFFF
[discord]: https://discord.gg/hKx3FJJgrV

<!-- Progress badges: JSON on the progress-data branch, refreshed by the README progress workflow on every push to main -->

[progress]: https://github.com/coah80/wii-ipl/actions/workflows/readme-progress.yml
[DecompiledBadge]: https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fcoah80%2Fwii-ipl%2Fprogress-data%2Fdecompiled.json
[MatchedBadge]: https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fcoah80%2Fwii-ipl%2Fprogress-data%2Fmatched.json
[LinkedBadge]: https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fcoah80%2Fwii-ipl%2Fprogress-data%2Flinked.json
[DataBadge]: https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fcoah80%2Fwii-ipl%2Fprogress-data%2Fdata.json
[FunctionsBadge]: https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fcoah80%2Fwii-ipl%2Fprogress-data%2Ffunctions.json
[UnitsBadge]: https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fcoah80%2Fwii-ipl%2Fprogress-data%2Funits.json

<!--- Header -->

![](./misc/logo.png)  
Wii Menu  
[![Build Status]][actions] [![Discord Badge]][discord]
========

<!--- Contents -->

A work-in-progress decompilation of the Wii Menu (4.3)

This repository does **not** contain any assets or assembly of the executable whatsoever. An existing WAD of the Wii Menu is required.

Live decomp status
==================

[![Build status]][actions]

Every push to `main` rebuilds 4.3U, checks the DOL hash, and refreshes the progress badges below. Open the latest [README progress run][actions] for the full objdiff summary.

Supported versions:
- `43U` - Version **4.3U** (USA)

Progress
========
[![DecompiledBadge]][progress] [![MatchedBadge]][progress] [![LinkedBadge]][progress] [![DataBadge]][progress]  
[![FunctionsBadge]][progress] [![UnitsBadge]][progress]

decompiled = code with a C/C++ implementation (objdiff fuzzy), matched = byte-exact code, linked = code actually linked into the DOL, data = byte-exact data

Dependencies
============

Windows
--------

On Windows, it's **highly recommended** to use native tooling. WSL or msys2 are **not** required.  
When running under WSL, [objdiff](#diffing) is unable to get filesystem notifications for automatic rebuilds.

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
  - Quick install via pip: `pip install ninja`

macOS
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages):

  ```sh
  brew install ninja
  ```

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Linux
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Building
========

- Clone the repository:

  ```sh
  git clone https://github.com/koopthekoopa/wii-ipl.git
  ```

- Copy your WAD to `orig/[Wii Menu Version]`.

- Configure:

  ```sh
  python configure.py
  ```

  To use a version other than the default one, 4.3U, use the `--version` argument.

- Build:

  ```sh
  ninja
  ```

>  [!NOTE]
> This does **not** produce a WAD file, only the executable file, `main.dol`.

> [!WARNING]
> Due to the SEL file not being generated on build, the code is not 100% shiftable.  
> Most of it works aside from a couple of things, such as Wii Settings and a couple of Channel Banners like the Forecast Channel.

Diffing
=======

Once the initial build succeeds, an `objdiff.json` should exist in the project root.

Download the latest release from [encounter/objdiff](https://github.com/encounter/objdiff). Under project settings, set `Project directory`. The configuration should be loaded automatically.

Select an object from the left sidebar to begin diffing. Changes to the project will rebuild automatically: changes to source files, headers, `configure.py`, `splits.txt` or `symbols.txt`.

![](misc/objdiff.png)
