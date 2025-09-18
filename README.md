<<<<<<< HEAD
# ESP32 Multi-Display Dashboard

A comprehensive IoT dashboard system for ESP32 that displays real-time data from multiple MQTT topics on a TFT display. Perfect for monitoring renewable energy systems, smart home metrics, and environmental data.

## 📋 Features

- **Real-time MQTT Data Display**: Monitors multiple MQTT topics simultaneously
- **TFT Color Display**: Shows data with color-coded trend indicators
- **Anti-Burn-In Protection**: Automatically shifts display content to prevent screen burn-in
- **Traffic Light Indicators**: Visual status indicators for critical values
- **System Monitoring**: Displays CPU usage and light sensor readings
- **Modular Configuration**: Easy to configure WiFi and MQTT settings

## 📊 Monitored Data

The dashboard displays the following metrics:

1. **Renewable Energy Share** (`OE_Strom%`) - Percentage of renewable energy in the grid
2. **Electricity Price** (`Strompreis`) - Current electricity pricing
3. **Wallbox Power** (`Wallbox`) - Electric vehicle charging station power consumption
4. **Charging Level** (`Charge Lev`) - Battery/vehicle charging level
5. **Water Temperature** (`Temp H2O`) - Heating system water temperature
6. **Stock Price** (`Stock`) - Real-time stock market data
7. **Calendar Events** - Next upcoming calendar event

## 🔧 Hardware Requirements

### Required Components
- **ESP32 Development Board** (ESP32-DevKit or similar)
- **TFT Display** compatible with TFT_eSPI library
- **Light Dependent Resistor (LDR)** connected to GPIO 34
- **Breadboard and jumper wires**

### Wiring Diagram
```
ESP32          TFT Display
-----          -----------
3.3V     -->   VCC
GND      -->   GND
GPIO XX  -->   CS  (Configure in TFT_eSPI)
GPIO XX  -->   DC  (Configure in TFT_eSPI)
GPIO XX  -->   MOSI (Configure in TFT_eSPI)
GPIO XX  -->   SCK  (Configure in TFT_eSPI)

ESP32          LDR
-----          ---
GPIO 34  -->   LDR Signal
3.3V     -->   LDR VCC (through voltage divider)
GND      -->   LDR GND
```

## 📚 Software Dependencies

### Libraries (automatically installed via PlatformIO)
- **TFT_eSPI** - TFT display driver
- **PubSubClient** - MQTT client library
- **ArduinoJson** - JSON parsing for MQTT messages
- **WiFi** - Built-in ESP32 WiFi functionality

### Development Environment
- **PlatformIO** (recommended) or Arduino IDE
- **ESP32 Arduino Core**

## 🚀 Installation & Setup

### 1. Clone the Repository
```bash
git clone <repository-url>
cd Multidisplay_ESP32_Rev1
```

### 2. Configure Hardware Settings
Configure your TFT display pins in the TFT_eSPI library:
- Edit `~/.platformio/lib_deps/TFT_eSPI/User_Setup.h`
- Or create a custom setup file for your specific display

### 3. Configure Network & MQTT Settings
```bash
# Copy the template configuration
cp include/config_template.h include/config_private.h

# Edit config_private.h with your settings
```

Edit `include/config_private.h`:
```cpp
// WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// MQTT broker
const char* mqtt_server = "YOUR_MQTT_SERVER_IP";
const int mqtt_port = 1883;
const char* mqtt_user = "YOUR_MQTT_USER";      // Leave empty if no auth
const char* mqtt_pass = "YOUR_MQTT_PASSWORD";  // Leave empty if no auth
```

### 4. Customize MQTT Topics
Edit the MQTT topics in `src/main.cpp` to match your system:
```cpp
const char* topic1 = "home/PV/Share_renewable";
const char* topic2 = "home/PV/EnergyPrice";
const char* topic3 = "home/PV/WallboxPower";
// ... add your topics
```

### 5. Build and Upload
```bash
# Using PlatformIO
pio run --target upload

# Or using PlatformIO IDE
# Click the upload button in VS Code
```

## 📖 Usage

### Display Layout
The dashboard shows data in a structured layout:
- **Top Section**: Renewable energy percentage with traffic light indicator
- **Middle Sections**: Numerical values with trend colors (green=increasing, red=decreasing)
- **Bottom Section**: System information (CPU usage, light sensor reading)
- **Event Display**: Current calendar event

### Color Coding
- **Green**: Increasing values (positive trend)
- **Red**: Decreasing values (negative trend)
- **Yellow**: Warning states
- **White**: Neutral/unchanged values

### Traffic Light Indicator
The renewable energy percentage shows a traffic light:
- 🔴 **Red**: < 30% renewable energy
- 🟡 **Yellow**: 30-70% renewable energy
- 🟢 **Green**: > 70% renewable energy

## ⚙️ Configuration Options

### Anti-Burn-In Settings
```cpp
const unsigned long shiftInterval = 60000; // Shift every 60 seconds
```

### Display Refresh Rate
```cpp
const unsigned long refreshInterval = 1000; // Check for updates every second
```

### LDR Settings
```cpp
analogReadResolution(12);     // 12-bit resolution: 0–4095
analogSetAttenuation(ADC_11db); // Full input voltage 0–3.3V
```

## 🔧 Customization

### Adding New Data Sources
1. Define new MQTT topic:
```cpp
const char* topic_new = "your/mqtt/topic";
```

2. Add variable for the data:
```cpp
float newValue = 0, newValue_old = 0;
```

3. Add to MQTT callback function
4. Add to display update function

### Modifying Display Layout
Edit the `drawValue()` function calls in the main loop to adjust positioning and formatting.

## 🐛 Troubleshooting

### Common Issues

**WiFi Connection Problems**
- Verify SSID and password in `config_private.h`
- Check WiFi signal strength
- Ensure 2.4GHz network (ESP32 doesn't support 5GHz)

**MQTT Connection Issues**
- Verify broker IP address and port
- Check firewall settings
- Test MQTT broker with another client

**Display Issues**
- Verify TFT_eSPI configuration
- Check wiring connections
- Ensure adequate power supply

**Compilation Errors**
- Ensure `config_private.h` exists
- Verify all library dependencies are installed
- Check ESP32 board definitions

### Debug Information
The system outputs debug information via Serial at 115200 baud rate.

## 📁 Project Structure

```
Multidisplay_ESP32_Rev1/
├── src/
│   └── main.cpp              # Main application code
├── include/
│   ├── config_private.h      # Your private configuration (not in git)
│   └── config_template.h     # Configuration template
├── lib/                      # Custom libraries (if any)
├── test/                     # Test files
├── platformio.ini           # PlatformIO configuration
├── .gitignore              # Git ignore file
└── README.md               # This file
```

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📄 License

This project is open source. Please check the license file for details.

## 🙏 Acknowledgments

- **TFT_eSPI Library** by Bodmer
- **PubSubClient Library** by Nick O'Leary
- **ArduinoJson Library** by Benoît Blanchon
- ESP32 Arduino Core team

## 📞 Support

For issues and questions:
1. Check the troubleshooting section above
2. Search existing GitHub issues
3. Create a new issue with detailed information about your setup and problem

---

**Happy Monitoring!** 📊✨
=======
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
>>>>>>> 011f78416efeeefa5e377afb9236c3f507a7ba41
