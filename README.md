# Disk Pressure Monitor (DPM)

Disk Pressure Monitor (DPM) is a lightweight tool designed to monitor disk usage and alert you when disk pressure exceeds a specified threshold. This tool is ideal for system administrators and developers who need to ensure their systems have sufficient disk space.

## Features

- Monitor disk usage in real-time
- Set custom thresholds for disk usage alerts
- Configurable check intervals
- Sends emergency alerts to syslog

## Installation

To install Disk Pressure Monitor, run the following commands:

```sh
git clone https://github.com/OmkarPokharkar/disk-pressure-monitor.git
cd disk-pressure-monitor
./install.sh
```

## Usage

Once installed, you can use the `dpm` command to monitor disk usage. Below are some example usages:

```sh
# Check disk usage with default settings
dpm --path / --threshold 80 --interval 60

# Check disk usage for a specific path
dpm --path /var --threshold 90 --interval 30

# Display help message
dpm --help
```

## Command-Line Options

- `--path <path>`: Specify the path to monitor (default: `/`).
- `--threshold <threshold>`: Set the disk usage threshold percentage for alerts (default: `80`).
- `--interval <interval>`: Set the interval in seconds between checks (default: `1`).
- `--help`: Display the help message.

## Example

To monitor the root directory `/` and alert when disk usage exceeds 80%, checking every 60 seconds, use the following command:

```sh
dpm --path / --threshold 80 --interval 60
```

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Author

Developed by [Omkar Pokharkar](https://github.com/OmkarPokharkar).
