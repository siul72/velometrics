# Velometrics

Velometrics is a Qt/C++ application for designing and rendering cycling telemetry overlays. It combines activity data (such as TCX and GPX tracks) with a visual editor so users can compose dashboards, charts, maps, and labels for video output.

## What it does

- Lets you build a telemetry layout on a canvas with draggable UI elements
- Imports cycling activity files such as TCX and GPX data
- Displays metrics like speed, heart rate, cadence, distance, and elapsed time
- Supports templates, themed visual styles, and project persistence
- Renders the final composition for video or export workflows using FFmpeg-backed rendering services

## Project goals

The project is structured around a designer/editor workflow and a reusable core library:

- `src/velometrics-designer` contains the Qt editor, menus, docks, toolbars, canvas, and template management
- `src/velometrics-core` handles telemetry parsing, rendering, metrics, and template/theme logic
- `resources` contains configuration and template assets
- `tests` contains sample activity files used during development and validation

## Features in progress

- Canvas-based composition editor
- Activity loading and playback controls
- Telemetry widget element definitions
- Template and theme management
- Video rendering pipeline based on FFmpeg

## Requirements

Velometrics is built with CMake and Qt 6.

Required system packages on Debian/Ubuntu-based systems:

```bash
sudo apt-get update
sudo apt-get install -y \
  build-essential \
  cmake \
  pkg-config \
  qt6-base-dev \
  qt6-tools-dev \
  qt6-svg-dev \
  libyaml-cpp-dev \
  libavcodec-dev \
  libavformat-dev \
  libavutil-dev \
  libswscale-dev
```

## Build

From the repository root:

```bash
cmake -S . -B build
cmake --build build
```

This generates the application target `velometrics` in the build directory.

## Run

```bash
./build/velometrics
```

## Repository layout

```text
.
├── CMakeLists.txt
├── README.md
├── resources/
│   ├── velometrics-config.yaml
│   └── templates/
├── src/
│   ├── velometrics-core/
│   └── velometrics-designer/
├── tests/
│   ├── exercise_tcx_file.tcx
│   └── GX010225_ALTA-15809081757057240.gpx
└── debian/
```

## Notes

This project is still under active development. The design/editor application is the primary entry point, while the core library is being expanded to support more data sources, layouts, and output modes.

## License

See the project sources and Qt licensing notes in `CMakeLists.txt` for the current dependency and licensing context.
