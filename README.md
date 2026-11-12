# HSD-SDP Repo

## Create doxygen Dokumentation website

```shell
doxygen Doxyfile
```

## DrivingSimulation

`DrivingSimulation` uses TCP instead of Windows named pipes, so the simulator
does not depend on `windows.h`. The repository now contains three executables:
`DrivingSimulation`, `DigitalDisplay`, and `AnalogDisplay`. The displays use
SDL2 for their windows and CMake downloads the pinned Asio and SDL2 versions
automatically during configuration.

The digital display must accept TCP connections on `127.0.0.1:4711` and the
analog display on `127.0.0.1:4712`. Values are sent as newline-terminated
messages:

```text
SET_VALUE 125
```

Build it with:

```shell
cmake -S DrivingSimulation -B DrivingSimulation/build
cmake --build DrivingSimulation/build
```

Start `DigitalDisplay` and `AnalogDisplay` before `DrivingSimulation`. The
simulator waits until both display servers are available.
