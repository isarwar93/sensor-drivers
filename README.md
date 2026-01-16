# Sensor Drivers

A comprehensive collection of sensor integration projects and drivers for microcontroller platforms. This repository contains well-documented implementations of various environmental and hardware sensors with complete setup guides, build instructions, and usage examples.

## Projects

### DHT11 Temperature and Humidity Sensor

ESP32 Lolin-based project for reading temperature and humidity measurements using the DHT11 sensor via PlatformIO and Arduino framework.

**Directory**: [dht11_sensor](dht11_sensor/)

**Features**:
- Real-time humidity and temperature monitoring
- Serial output at 115200 baud
- Comprehensive accuracy documentation
- Complete build and flash instructions

**Hardware Requirements**:
- ESP32 Lolin (WEMOS LOLIN32)
- DHT11 Digital Humidity and Temperature Sensor
- USB cable for programming

**Quick Start**:
```bash
cd dht11_sensor
pio run -e lolin32                  # Build
pio run -e lolin32 -t upload        # Flash to device
pio device monitor -e lolin32       # View serial output
```

For detailed information, see [dht11_sensor/README.md](dht11_sensor/README.md).

## Repository Structure

```
sensor-drivers/
├── README.md                 # This file
├── dht11_sensor/             # DHT11 sensor project
│   ├── README.md             # Project documentation
│   ├── platformio.ini        # PlatformIO configuration
│   ├── src/
│   │   └── main.cpp          # Main application code
│   ├── include/              # Header files
│   └── .gitignore            # Git ignore patterns
└── ...                        # Additional projects (planned)
```

## Requirements

### General
- Git for cloning repositories
- Python 3.7 or higher

### Per Project
Each project directory contains its own `README.md` with specific requirements and setup instructions.

## Getting Started

1. Clone this repository:
   ```bash
   git clone https://github.com/isarwar93/sensor-drivers.git
   cd sensor-drivers
   ```

2. Navigate to the desired project:
   ```bash
   cd dht11_sensor
   ```

3. Follow the project-specific setup instructions in the project's README.

## Contributing

Contributions are welcome. When adding new sensor projects:
- Follow the existing directory structure
- Include comprehensive README with hardware connections
- Document sensor specifications and accuracy limitations
- Provide working code with error handling
- Include build and deployment instructions
- Add appropriate .gitignore patterns

## License

Each project in this repository is provided for educational and development purposes.

## Additional Resources

- [PlatformIO Documentation](https://docs.platformio.org/)
- [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)
- [Arduino Language Reference](https://www.arduino.cc/reference/en/)
