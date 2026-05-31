# wxCommander

A dual-pane (orthodox) file manager in the style of Norton Commander / Total Commander,
written in C++ with the [wxWindows](https://www.wxwidgets.org/) cross-platform GUI toolkit.

> Vintage project (circa 2000–2001). Targets the wxWindows 2.x API and depends on the
> in-house ConfigIt libraries, so it is primarily of historical/reference interest today.

## Overview

wxCommander presents two side-by-side file panes, each with its own directory listing,
drive/mount selector, and status bar. Files are shown in a multi-column list (name,
extension, size, date, attributes) with type-specific icons, sorting, and keyboard-driven
navigation. A command panel along the bottom exposes the classic function-key style
operations (View, Edit, Copy, Move/Rename, MkDir, Delete, Exit).

## Features

- **Dual-pane layout** with a draggable splitter between the two file views
- **File listing** with sortable columns: name, extension, size, date, attributes
- **File type detection** and icons for files, directories, links, executables, and archives
- **Drive / mount toolbar** for switching volumes per pane
- **Keyboard navigation** — Tab, arrows, Space, Enter, Esc, and a function-key command row
- **File operations** — view, edit, copy, move/rename, make directory, delete
- **Menus** for Files, Commands, Show, Configuration, Mark, Start, and Help
- **Cross-platform** — builds for Linux/X11 (GTK) and Windows (Win32)

## Architecture

The UI is composed of focused components, coordinated by a central manager:

| Component | Responsibility |
|-----------|----------------|
| `Main` (`main.cpp`) | wxApp entry point; bootstraps the `AppManager` |
| `AppManager` (`appmanager.cpp`) | Owns the frame and wires together the panes, panels, and key/command actions |
| `MainFrame` (`mainframe.cpp`) | Top-level window: menu bar, toolbar, status bar |
| `FileView` (`fileview.cpp`) | A single pane: directory bar, mount selector, and its file list |
| `FileList` (`filelist.cpp`) | The list control that loads, displays, sorts, and operates on files |
| `DriveButtonPanel` (`drivebuttonpanel.cpp`) | Drive / mount-point buttons |
| `LowerPanel` (`lowerpanel.cpp`) | Command combo box plus the View/Edit/Copy/Move/MkDir/Delete/Exit buttons |
| `functions.cpp` | File helpers: attributes, size, type checks, date/size formatting |
| `global.h` | Shared constants, macros, fonts, and colours |

Icons live in `bitmaps/` (both `.xpm` for GTK and `.ico` for Windows).

## Building

### Linux / GTK

Requires wxWindows 2.x and the ConfigIt libraries (`configit_base`, `configit_gui`).

```sh
make
```

The `Makefile` uses `g++` and `wx-config` for compiler and linker flags. Adjust the
`CONFIGIT_ROOT` and wxWindows include/library paths for your environment.

### Windows

Open `wxCommander.dsw` / `wxCommander.dsp` in Visual C++ (6.0-era project files);
resources are defined in `wxCommander.rc`.

## Dependencies

- **wxWindows / wxWidgets 2.x** — GUI toolkit
- **ConfigIt** (`configit_base`, `configit_gui`) — in-house support libraries
- A C++ compiler (g++ on Linux, MSVC on Windows) and, on Linux, GTK + X11
