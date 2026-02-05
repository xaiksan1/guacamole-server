# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository Overview

This is **Apache Guacamole Server v1.5.3**, a clientless remote desktop gateway that enables access to remote systems via VNC, RDP, SSH, Telnet, and Kubernetes APIs through a modern web browser. The project uses GNU Autotools (Autoconf/Automake) for building and is written primarily in C.

Key components:
- **guacd** - Guacamole proxy daemon (translates protocols to Guacamole protocol)
- **libguac** - Core library providing drawing, protocol parsing, and encoding
- **Protocol libraries** - RDP, SSH, VNC, Telnet, Kubernetes client implementations
- **guacenc** - Video encoding utility for session recordings
- **guaclog** - Input logging tool for session recording playback

Also included:
- **guacamole-bare-metal-proxy** - Installation and configuration guide for bare metal deployments (Nginx + Tomcat + MariaDB)

## Building and Installation

### Prerequisites

Install required dependencies on Debian/Ubuntu:

```bash
sudo apt-get install build-essential autoconf automake libtool pkg-config \
    libcairo2-dev libjpeg-turbo8-dev libpng-dev libpthread-stubs0-dev \
    libossp-uuid-dev libssl-dev libpulse-dev libvncserver-dev \
    libssh2-1-dev libtelnet-dev libwebp-dev libwebsockets-dev \
    libpango1.0-dev libfreerdp2-dev libwinpr2-dev libavcodec-dev \
    libavformat-dev libavutil-dev libswscale-dev
```

### Build Commands

```bash
# Generate configure script from configure.ac
./autoreconf -i

# Configure the build (all protocols and optional features enabled)
./configure --with-init-dir=/etc/init.d --with-systemd-dir=/etc/systemd/system \
    --with-freerdp-plugin-dir=/usr/lib/x86_64-linux-gnu/freerdp2

# Compile all components
make

# Run tests (CUnit framework)
make check

# Install (requires root)
sudo make install

# View dependency status
./configure --help  # See all build-time options
```

### Build Options

```bash
# Disable specific protocol support
./configure --disable-rdp --disable-ssh --disable-vnc

# Disable optional features
./configure --disable-guacenc --disable-guaclog --disable-websockets

# Build without init script/systemd support
./configure --without-init-dir --without-systemd-dir

# Install to custom prefix
./configure --prefix=/opt/guacamole
```

After `./configure`, run `make` to see a summary of enabled/disabled components.

### Minimal Dependencies for Testing

For quick testing without all optional features:

```bash
./configure --disable-guacenc --disable-pulse --disable-websockets --disable-kubernetes

# Then build and test as usual
make
make check
```

This is useful when some libraries aren't available but you still want to test the core functionality.

## Project Structure

```
src/
├── libguac/              # Core library (drawing, protocol, encoding)
│   ├── client.c          # Client connection management
│   ├── parser.c          # Guacamole protocol parser
│   ├── encode-*.c        # Image encoding (JPEG, PNG, WebP)
│   ├── audio.c           # Audio support
│   ├── socket.c          # Socket I/O
│   └── tests/            # CUnit test suite
│
├── guacd/                # Proxy daemon (main application)
│   ├── daemon.c          # Main daemon loop, signal handling
│   ├── connection.c      # Client connection handling
│   ├── proc.c            # Protocol handler process management
│   ├── conf-*.c          # Configuration file parsing
│   └── log.c             # Logging utilities
│
├── protocols/
│   ├── rdp/              # RDP client (FreeRDP wrapper)
│   ├── ssh/              # SSH client (libssh2 wrapper)
│   ├── vnc/              # VNC client (libvncclient wrapper)
│   ├── telnet/           # Telnet client (libtelnet wrapper)
│   └── kubernetes/       # Kubernetes API client (libwebsockets)
│
├── common/               # Shared utilities (rectangle math, string ops, clipboard, cursor)
├── common-ssh/           # SSH-specific utilities (SFTP, keys, user handling)
├── terminal/             # Terminal emulator (for SSH/Telnet)
├── pulse/                # PulseAudio integration (audio from remote systems)
├── guacenc/              # Video encoder (creates recordings)
├── guaclog/              # Session input logger/player
│
build-aux/               # Build system helpers (test-driver, etc)
m4/                      # Autoconf macros
bin/                     # Utility scripts (guacctl)
doc/                     # Doxygen configuration (API docs)
util/                    # Build utilities (test runner generator)
```

## Running guacd

### Quick Start

```bash
# Run in foreground with debug logging
guacd -f -L debug

# Run as daemon on custom port
guacd -b 127.0.0.1 -l 4822 -L info
```

### Command-Line Options

```
-b HOST        Bind to specific host/address (default: 0.0.0.0)
-l PORT        Listen on specific port (default: 4822)
-p PIDFILE     Write PID to file
-L LEVEL       Set log level (debug, info, warning, error)
-f             Run in foreground (don't background)
```

### Service Management (after `make install`)

```bash
# Via systemd (if configured with --with-systemd-dir)
sudo systemctl start guacd
sudo systemctl status guacd
sudo systemctl logs guacd -f

# Via init.d script (if configured with --with-init-dir)
sudo /etc/init.d/guacd start
```

## Testing

### Running Tests

```bash
# All tests (requires CUnit library)
make check

# Specific test suite
make -C src/common/tests check
make -C src/libguac/tests check
make -C src/protocols/rdp/tests check

# Verbose test output
make check VERBOSE=1
```

### Test Architecture

Tests use CUnit framework with TAP (Test Anything Protocol) driver. Test source files are:
- Rectangle math tests: `src/common/tests/rect/*.c`
- String utility tests: `src/common/tests/string/*.c`
- Character encoding tests: `src/common/tests/iconv/*.c`
- Protocol-specific tests: `src/protocols/*/tests/*.c`

Test runner is auto-generated by `util/generate-test-runner.pl` during build.

## Code Organization

### Key Design Patterns

**Protocol Abstraction**: Each protocol (RDP, SSH, VNC, etc.) is isolated in `src/protocols/{protocol}/`. Each implements a common interface that guacd uses to:
- Handle client connections
- Process Guacamole protocol messages
- Encode display updates
- Handle input events

**Guacamole Protocol**: Custom text-based protocol (superset of VNC/RDP operations). All protocol handlers convert their native protocol to Guacamole protocol for transmission to web browser.

**Client-Server Model**:
```
Web Browser ← (WebSocket) → Guacamole Web App ← (Guacamole Protocol) → guacd ← (RDP/SSH/VNC/etc) → Remote System
```

**Process Per Connection**: Each client connection runs in a separate child process (`proc.c`). guacd fork()s a new process for each connected client, isolating failures.

### Common Code Patterns

**Configuration File**: `/etc/guacamole/guacd.conf` parsed by `src/guacd/conf-parse.c`. Settings include bind address, port, SSL cert, etc.

**Logging**: All log messages route through `src/guacd/log.c`, which outputs to syslog and stderr (when running in foreground).

**Socket I/O**: `libguac/socket.c` handles all network I/O with automatic message framing and error handling.

## Git Workflow

### Commit Message Format

Per `CONTRIBUTING` file, follow Apache Guacamole conventions:

```
GUACAMOLE-123: Concise description of change

Longer explanation of what changed and why, if needed.
Include references to related issues/JIRA tickets.
```

(For this fork: reference issues descriptively since it's not the main Apache repo)

### Recent Commits

```
ce45028 Improves script portability    (portability/build improvements)
e5354d8 Initial commit of guacamole-server 1.5.3
```

## Important Configuration Files

| Location | Purpose |
|----------|---------|
| `configure.ac` | Autoconf build configuration (dependency checks, feature flags) |
| `Makefile.am` | Automake build rules (defines what gets built) |
| `src/guacd/guacd.c` | Main daemon entry point |
| `CONTRIBUTING` | Contribution guidelines for Apache Guacamole |
| `/etc/guacamole/guacd.conf` | Runtime configuration (created at install time) |

## Common Development Tasks

### Building a Single Component

```bash
# Build only libguac
make -C src/libguac

# Build only RDP support
make -C src/protocols/rdp

# Rebuild after editing
cd src/protocols/ssh && make clean && make
```

### Adding Protocol-Specific Code

1. Edit code in `src/protocols/{protocol}/`
2. If adding new files, update the corresponding `Makefile.am`
3. Run `make -C src/protocols/{protocol}` to compile
4. Add tests in `src/protocols/{protocol}/tests/` (CUnit format)
5. Run `make -C src/protocols/{protocol}/tests check`

### Debugging guacd

```bash
# Run under gdb with debug symbols
gdb --args guacd -f -L debug

# Or attach to running process
gdb /usr/local/sbin/guacd $(pgrep guacd)

# Enable sanitizers at build time (for memory issues)
./configure CFLAGS="-g -fsanitize=address"
make
```

### Modifying Build Dependencies

Edit `configure.ac` to:
- Add new library checks: `AC_CHECK_LIB([lib], [function])`
- Add feature flags: `AC_ARG_WITH([feature])`
- Update conditional builds: `AM_CONDITIONAL`

Then regenerate configure:
```bash
./autoreconf -i
```

## Architectural Notes

### Protocol Handlers

Each protocol handler (RDP/SSH/VNC/Telnet) works by:
1. Receiving user input (keyboard, mouse) via `libguac`
2. Translating to native protocol format (RDP packets, SSH commands, etc.)
3. Receiving updates from remote system (screen, audio, clipboard)
4. Converting to Guacamole protocol (draw instructions, clips, cursors)
5. Sending to client via `libguac/socket.c`

### File Transfer (SFTP)

SFTP support (for RDP and SSH) is implemented in `src/common-ssh/sftp.c` and integrated into protocol handlers.

### Audio Support

Audio from remote systems is captured via PulseAudio (`src/pulse/`) and encoded as WAV or Ogg Vorbis before transmission.

### Video Encoding

Session recordings are handled by `guacenc` utility, which reads recorded Guacamole protocol stream and encodes to MP4 via FFmpeg.

## Troubleshooting Build Issues

| Issue | Likely Cause | Solution |
|-------|--------------|----------|
| `cairo.h not found` | Cairo library missing | `apt-get install libcairo2-dev` |
| `undefined reference to 'jpeg_start_compress'` | libjpeg not linked | Check `Makefile.am` LDADD flags, reinstall libjpeg-turbo-dev |
| `autoreconf: command not found` | Autotools not installed | `apt-get install autoconf automake libtool` |
| `Protocol disabled after configure` | Optional dependency missing | Install library, re-run `./configure`, check summary |
| `CUnit tests fail to compile` | CUnit not installed | `apt-get install libcunit1-dev` |
| Tests don't run with `make check` | TAP driver issue | Ensure `build-aux/tap-driver.sh` exists and is executable |

## License

Apache Guacamole Server is licensed under the Apache License 2.0. All source files include the ASF license header.

---

**Project**: Apache Guacamole Server v1.5.3
**Build System**: GNU Autotools (Autoconf/Automake)
**Language**: C
**Last Updated**: January 2024
