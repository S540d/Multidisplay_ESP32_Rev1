# Multidisplay_ESP32_Rev1

A private repository by [S540d](https://github.com/S540d) for ESP32-based multi-display projects using C++ and [PlatformIO](https://github.com/platformio/platformio-core).  
This project is structured for modular development on the ESP32 platform, supporting multiple display interfaces and features.

> **Board Compatibility:**  
> The code is designed for use with the **JC2432W328 Board** (ESP32-based).

## Project Structure

- `src/main.cpp` – Main application code.
- `include/` – Header files for project-specific definitions.
- `lib/` – Custom and third-party libraries.
- `.gitignore` – Git tracking rules.
- `platformio.ini` – PlatformIO project configuration.

## Getting Started

1. **Requirements**  
   - [PlatformIO](https://platformio.org/) (recommended IDE integration: VS Code)
   - ESP32 development board (specifically the JC2432W328 Board)

2. **Setup**  
   - Clone this repository:  
     ```sh
     git clone https://github.com/S540d/Multidisplay_ESP32_Rev1.git
     ```
   - Open the project in PlatformIO/VS Code.
   - Connect your ESP32 board and build/upload the project.

3. **Configuration**  
   - Adjust settings in `platformio.ini` for board type, libraries, and build options.
   - Add custom code in `src/main.cpp` and your headers in `include/`.

## Features

- Modular codebase for multi-display applications.
- Extensible via PlatformIO library management.
- Organized for clean separation between source, headers, and external libraries.

## Directory Overview

| Folder/File     | Purpose                                    |
|-----------------|--------------------------------------------|
| `src/`          | Main source code                           |
| `include/`      | Header files                               |
| `lib/`          | Project/local libraries                    |
| `.gitignore`    | Files to ignore in version control         |
| `platformio.ini`| PlatformIO config (board, libraries, etc.) |

## License

_No license specified yet._

## Author

[S540d](https://github.com/S540d)