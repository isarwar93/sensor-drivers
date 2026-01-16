# ESP32 DHT11 Humidity and Temperature Sensor Project

## Overview

This project implements a humidity and temperature monitoring system using an ESP32 Lolin microcontroller board with a DHT11 sensor. The system reads sensor data and transmits measurements via UART serial communication at regular intervals.

## Hardware Requirements

- **Microcontroller**: ESP32 Lolin (WEMOS LOLIN32)
- **Sensor**: DHT11 Digital Humidity and Temperature Sensor
- **Connection Pin**: GPIO 26 (data line)
- **Additional Components**:
  - USB cable for programming and serial communication
  - 10kΩ pull-up resistor (recommended for DHT11 data line)
  - Power supply (5V via USB or external)

## Hardware Connection

Connect the DHT11 sensor to the ESP32 Lolin as follows:

| DHT11 Pin | ESP32 Pin | Notes |
|-----------|-----------|-------|
| VCC | 5V or 3.3V | Power supply |
| GND | GND | Ground |
| DATA | GPIO 26 | Signal line (with optional 10kΩ pull-up) |

## Software Setup

### Prerequisites

- Python 3.7 or higher
- pip (Python package manager)
- USB drivers for ESP32 (usually auto-installed on Linux)

### Installation Steps

#### First-Time Setup

1. **Navigate to the project directory**:
   ```bash
   cd /home/ismail-sarwar/esp32-humidity-sensor
   ```

2. **Create a Python virtual environment** (one time only):
   ```bash
   python -m venv .venv
   ```

3. **Activate the virtual environment**:
   ```bash
   source .venv/bin/activate  # On Linux/macOS
   # or
   .venv\Scripts\activate  # On Windows
   ```

4. **Install PlatformIO**:
   ```bash
   pip install platformio
   ```

5. **Verify installation**:
   ```bash
   pio --version
   ```

#### Every Subsequent Work Session

Simply activate the existing virtual environment:

```bash
source .venv/bin/activate  # On Linux/macOS
# or
.venv\Scripts\activate  # On Windows
```

You only need to create the virtual environment once. After that, just activate it each time you start working. When done, deactivate with:

```bash
deactivate
```

## Building and Flashing

### Build the Project

Compile the code for the ESP32 Lolin board:

```bash
pio run -e lolin32
```

This command:
- Compiles the source code (`src/main.cpp`)
- Resolves and downloads dependencies (DHT sensor library, Adafruit Unified Sensor)
- Generates the firmware binary file
- Displays memory usage statistics

### Upload Firmware to Device

Connect the ESP32 Lolin via USB and upload the firmware:

```bash
pio run -e lolin32 -t upload
```

This command:
- Detects the USB port automatically (usually `/dev/ttyUSB0` on Linux)
- Erases the relevant flash memory sectors
- Uploads the compiled firmware
- Verifies the uploaded data with checksums
- Performs a hard reset to start the application

### Monitor Serial Output

Open the serial monitor to view sensor readings in real-time:

```bash
pio device monitor -e lolin32
```

Default settings:
- Baud rate: 115200 bps
- Data bits: 8
- Stop bits: 1
- Parity: None

To exit the monitor, press `Ctrl+C`.

## Project Files

### platformio.ini

Configuration file for PlatformIO:

```ini
[env:lolin32]
platform = espressif32
board = lolin32
framework = arduino
monitor_speed = 115200
lib_deps = 
    DHT sensor library@^1.4.4
    Adafruit Unified Sensor@^1.1.11
```

- `platform`: Espressif 32-bit ESP32 development platform
- `board`: WEMOS LOLIN32 board variant
- `framework`: Arduino framework for ease of development
- `monitor_speed`: Serial communication speed
- `lib_deps`: Required external libraries with version specifications

### src/main.cpp

Main application code implementing the sensor reading logic:

```cpp
#define DHTPIN 26
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
```

The application:
1. Initializes the serial port at 115200 baud
2. Configures GPIO 26 as the DHT11 data line
3. Reads humidity and temperature every 2 seconds
4. Validates sensor responses
5. Outputs formatted data to serial monitor

## Temperature and Humidity Calculation

### DHT11 Sensor Specifications

The DHT11 is a single-wire digital sensor that provides:
- **Humidity Range**: 20% to 80% RH (Relative Humidity)
- **Humidity Accuracy**: ±5% RH
- **Humidity Resolution**: 1% RH
- **Temperature Range**: 0°C to 50°C
- **Temperature Accuracy**: ±2°C
- **Temperature Resolution**: 1°C
- **Sampling Period**: Minimum 1 second between readings

### DHT11 Accuracy and Limitations

The DHT11 sensor has significant accuracy limitations that must be understood for proper interpretation of readings:

#### Temperature Measurements

- **Specified Accuracy**: ±2°C
- **Real-World Performance**: Measurements can deviate by 2-3°C from actual ambient temperature
- **Resolution**: 1°C discrete steps (decimal readings are interpolated)
- **Suitable Range**: 0°C to 50°C (outside this range, readings become unreliable)
- **Response Time**: Slow response to rapid temperature changes (not suitable for dynamic environments)
- **Thermal Effects**: Sensor self-heating occurs if powered continuously, causing higher readings

#### Humidity Measurements

- **Specified Accuracy**: ±5% RH (Relative Humidity)
- **Real-World Performance**: Readings can easily deviate by 5-10% from actual ambient humidity
- **Resolution**: 1% RH discrete steps
- **Usable Range**: 20% to 80% RH (readings outside this range are unreliable)
- **Drift**: Sensor calibration drifts over time, particularly in high humidity or high temperature environments
- **Response Time**: Slow response to rapid humidity changes
- **Environmental Sensitivity**: Accuracy degrades near windows, cold walls, heating sources, or direct sun exposure

#### Common Real-World Issues

- **Stuck Readings**: Humidity often stabilizes around 60-65% due to sensor resolution and calibration drift
- **Resolution Limitations**: Changes smaller than 1% RH are not detected; readings appear constant for extended periods
- **Warm-up Effect**: Fluctuations appear immediately after power-on or reset as sensor reaches thermal equilibrium
- **Weather Discrepancies**: Readings differ significantly from weather applications (which typically report outdoor conditions)
- **Factory Calibration Variance**: Individual sensors vary in accuracy; factory calibration is approximate only

#### Appropriate Use Cases

DHT11 is suitable for:
- Educational projects and demonstrations
- Hobbyist applications requiring rough environmental feedback
- Learning about sensor integration and microcontroller programming
- Simple "dry or humid" binary-style indicators (not precise measurements)

#### Unsuitable Use Cases

DHT11 is NOT suitable for:
- Mold prevention monitoring (requires high accuracy)
- Indoor air quality control systems
- Energy-efficient climate control (heating/cooling optimization)
- Health-related applications or data-dependent decisions
- Systems requiring calibrated, traceable measurements
- Industrial monitoring or compliance applications

#### Alternative Sensors

For applications requiring higher accuracy, consider:
- **BME680**: Measures temperature, humidity, pressure, and air quality (±3% RH)
- **SHT31 or SHT35**: Precision sensors with ±1.5% RH accuracy and better stability
- **AM2320**: Improved DHT alternative with better accuracy (±3% RH)
- **DHT22**: Higher accuracy variant (±2% RH) with extended range, but slower and more expensive

### Data Format and Calculation

The DHT11 transmits data as a 40-bit packet over a single GPIO line:

1. **Humidity Integer**: Bits 0-7
2. **Humidity Decimal**: Bits 8-15
3. **Temperature Integer**: Bits 16-23
4. **Temperature Decimal**: Bits 24-31
5. **Checksum**: Bits 32-39

The DHT sensor library (used in this project) handles the low-level protocol:
- Sends a start signal (pull-down for 18ms, then pull-up for 40µs)
- Waits for the sensor to respond
- Reads the 40-bit data stream using GPIO timing
- Validates the checksum

### Example Calculations

The sensor returns raw binary data that is decoded as follows:

```
Received data: [Humidity_H][Humidity_L][Temp_H][Temp_L][Checksum]
Checksum = (Humidity_H + Humidity_L + Temp_H + Temp_L) & 0xFF

Humidity % = Humidity_H + (Humidity_L / 10)
Temperature °C = Temp_H + (Temp_L / 10)
```

### Library Handling

The DHT sensor library abstracts this complexity:

```cpp
float humidity = dht.readHumidity();       // Returns 0.0 to 100.0
float temperature = dht.readTemperature(); // Returns -40.0 to 50.0
```

Both functions return `NaN` on read failure, which is validated in the code.

## PlatformIO CLI Reference

### Core Commands

#### `pio run`
Builds the project for the specified environment.

```bash
pio run -e lolin32              # Build for lolin32
pio run -e lolin32 -v           # Build with verbose output
pio run                         # Build all environments
```

#### `pio run -t upload`
Builds and uploads firmware to the device.

```bash
pio run -e lolin32 -t upload    # Build and upload for lolin32
```

#### `pio device monitor`
Opens an interactive serial monitor.

```bash
pio device monitor -e lolin32               # Connect to serial port
pio device monitor -e lolin32 -b 115200     # Specify baud rate
pio device monitor -e lolin32 --echo        # Echo input characters
```

### Device Management

#### `pio device list`
Lists available serial ports and connected devices.

```bash
pio device list
```

#### `pio boards`
Displays information about supported boards.

```bash
pio boards esp32                # List ESP32 boards
pio boards lolin32              # Show lolin32 specs
```

### Project Commands

#### `pio project init`
Creates a new PlatformIO project.

```bash
pio project init --board lolin32 --framework arduino
```

#### `pio lib list`
Lists installed libraries.

```bash
pio lib list
```

#### `pio lib install`
Installs a library.

```bash
pio lib install "DHT sensor library"
```

#### `pio lib search`
Searches for available libraries.

```bash
pio lib search dht11
```

### System Management

#### `pio system info`
Displays system and environment information.

```bash
pio system info
```

#### `pio system prune`
Removes unused PlatformIO system data.

```bash
pio system prune --dry-run      # Preview what will be removed
pio system prune                # Remove unnecessary files
```

## Serial Output Format

The application outputs data in the following format:

```
ESP32 DHT11 Humidity & Temperature Sensor
==========================================
DHT11 sensor initialized on GPIO 26
Starting measurements...

Humidity: 55.30% | Temperature: 24.50°C
Humidity: 55.40% | Temperature: 24.55°C
Humidity: 55.35% | Temperature: 24.52°C
```

Each measurement includes:
- Real-time humidity reading (percentage)
- Real-time temperature reading (Celsius)
- Timestamp (implicit via serial output)

## Troubleshooting

### Failed to read from DHT11 sensor

**Cause**: Sensor communication error or loose connections.

**Solution**:
- Verify GPIO 26 connection is secure
- Check DHT11 power supply (3.3V or 5V)
- Ensure pull-up resistor is connected (if needed)
- Increase delay between reads to 2+ seconds

### Serial port not detected

**Cause**: USB drivers not installed or device not recognized.

**Solution**:
- Check USB cable connection
- List available ports: `pio device list`
- On Linux, verify user has USB permissions
- Install CH340 drivers if needed (for certain ESP32 boards)

### Upload fails with timeout

**Cause**: Communication error during upload process.

**Solution**:
- Hold BOOT button while uploading (if required)
- Try a different USB cable
- Reduce upload speed in platformio.ini:
  ```ini
  upload_speed = 115200
  ```

## Project Structure

```
esp32-humidity-sensor/
├── .gitignore              # Git ignore patterns
├── .venv/                  # Python virtual environment
├── README.md               # This file
├── platformio.ini          # PlatformIO configuration
├── src/
│   └── main.cpp            # Main application code
├── include/                # Header files (empty)
└── .pio/                   # PlatformIO build directory
```

## Dependencies

- **DHT sensor library** (v1.4.4+): Provides DHT11/DHT22 sensor interface
- **Adafruit Unified Sensor** (v1.1.11+): Base sensor library framework
- **Arduino Framework**: Core ESP32 Arduino API

## License

This project is provided as-is for educational and development purposes.

## Additional Resources

- [PlatformIO Documentation](https://docs.platformio.org/)
- [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)
- [DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library)
- [DHT11 Datasheet](https://www.mouser.com/datasheet/2/758/DHT11-928424.pdf)
