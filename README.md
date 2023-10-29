# Mesh WiFi Sensor Network Project

## Overview

This project establishes a Mesh WiFi network among the NodeMCUs within the system. The NodeMCUs communicate with each other and transmit data to the server, including real-time temperature, humidity, and gas concentration readings, for display on a web server that we have created.

## Repository Structure

- `ESP-DATA`: This folder contains the code and data related to the NodeMCUs within the Mesh WiFi network. It includes the sensor data collection, transmission, and communication logic.

- `ESP-HEAD`: This folder is dedicated to the ROOT node or main controller of the Mesh WiFi network. It manages the data reception, storage, and web server interaction.

## ESP-DATA

The `ESP-DATA` folder contains the following components:

- **NodeMCU Code**: This is where you can find the code that runs on the individual NodeMCU devices. It includes the logic for sensor data collection, communication with other nodes, and transmission to the ROOT node.

- **Data Storage**: This directory may contain any data related to the operation of the NodeMCUs, such as sensor calibration files or configuration settings.

## ESP-HEAD

The `ESP-HEAD` folder contains the following components:

- **ROOT Node Code**: Here, you will find the code that runs on the ROOT node, which is responsible for receiving data from the other NodeMCUs, storing it, and serving it to the web server.

- **Web Server Files**: This directory includes the files for the web server that displays the real-time sensor data. You can find HTML, CSS, and JavaScript files for the user interface here.

## Usage

- Clone this repository to your local development environment.

- Navigate to the `ESP-DATA` or `ESP-HEAD` folder for the specific component you want to work with.

- Follow the README or documentation within each folder for detailed setup and usage instructions.

## Contributing

Contributions are welcome! If you would like to contribute to this project, please follow our [contribution guidelines](CONTRIBUTING.md).

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
