# CPCReady Toolchain Configuration Tool

[![Build](https://img.shields.io/github/actions/workflow/status/CPCReady/toolchain/build.yml?branch=main&label=build&logo=github)](https://github.com/CPCReady/toolchain/actions/workflows/build.yml)
[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)](https://github.com/CPCReady/toolchain)
[![License](https://img.shields.io/badge/license-Destroyer%202025-green.svg)](https://github.com/CPCReady/toolchain)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20Raspberry%20Pi-lightgrey.svg)](https://github.com/CPCReady/toolchain)

> **CPCReady Toolchain: INI configuration file management utility.**

A powerful and flexible command-line tool for managing key-value pairs in INI format configuration files. This software is part of the CPCReady SDK and provides seamless section-based configuration management.

## 🚀 Features

- ✅ **Set configuration values**: Create or update key-value pairs in specific sections
- ✅ **Get configuration values**: Retrieve values from INI configuration files
- ✅ **Auto-file creation**: Creates INI files automatically if they don't exist
- ✅ **Auto-section creation**: Creates new sections automatically when needed
- ✅ **Silent operation**: No output on success, detailed errors on failure
- ✅ **Section management**: Full support for INI file sections and organization
- ✅ **Error handling**: Proper exit codes for scripting integration
- ✅ **Multi-platform**: Linux (x86_64, ARM64, ARMhf), macOS (Intel, Apple Silicon)
- ✅ **Lightweight**: Single binary, no dependencies

## 📦 Installation

### Download Precompiled Binaries (Recommended)

Download the latest precompiled binaries from the [Releases page](https://github.com/CPCReady/toolchain/releases):

**Linux:**
- `cpc-conf-linux-amd64.tar.gz` - Linux x86_64 (Intel/AMD 64-bit)
- `cpc-conf-linux-arm64.tar.gz` - Linux ARM64 (Raspberry Pi 4, AWS Graviton)
- `cpc-conf-linux-armhf.tar.gz` - Linux ARM Hard Float (Raspberry Pi 2/3)

**macOS:**
- `cpc-conf-darwin-amd64.tar.gz` - macOS Intel (x86_64)
- `cpc-conf-darwin-arm64.tar.gz` - macOS Apple Silicon (M1/M2/M3)

```bash
# Download and install (replace <platform>-<arch> with your target)
curl -L -o cpc-conf.tar.gz "https://github.com/CPCReady/cpc-conf/releases/latest/download/cpc-conf-<platform>-<arch>.tar.gz"
tar -xzf cpc-conf.tar.gz
chmod +x cpc-conf-<platform>-<arch>
sudo mv cpc-conf-<platform>-<arch> /usr/local/bin/cpc-conf

# Verify installation
cpc-conf --version
```

### Compile from Source

### Prerequisites
- GCC compiler (or Clang on macOS)
- Standard C library

### Compilation

```bash
gcc cpc-conf.c -o cpc-conf
```

### Installation (Optional)
```bash
# Copy to system path (requires sudo on Linux/macOS)
sudo cp cpc-conf /usr/local/bin/
```

## 📖 Usage

### Basic Syntax

```bash
# Set a configuration value
./cpc-conf set <filename> <section> <key> <value>

# Get a configuration value
./cpc-conf get <filename> <section> <key>

# Show help
./cpc-conf --help

# Show version
./cpc-conf --version
```

### Commands

| Command | Description | Syntax |
|---------|-------------|---------|
| `set` | Set or update a key-value pair in a section | `cpc-conf set <file> <section> <key> <value>` |
| `get` | Retrieve the value of a key from a section | `cpc-conf get <file> <section> <key>` |

### Options

| Option | Description |
|--------|-------------|
| `-h, --help` | Show help message and exit |
| `--version` | Show version information and exit |

## 💡 Examples

### Setting Configuration Values

```bash
# Set database configuration
./cpc-conf set cpcready.conf database host "localhost"
./cpc-conf set cpcready.conf database port 5432
./cpc-conf set cpcready.conf database name "myapp"

# Set application settings
./cpc-conf set cpcready.conf application name "MyApplication"
./cpc-conf set cpcready.conf application version "1.0.0"
./cpc-conf set cpcready.conf application debug true

# Create new sections automatically
./cpc-conf set settings.ini logging level "INFO"
./cpc-conf set settings.ini logging file "/var/log/app.log"
```

### Getting Configuration Values

```bash
# Get database settings
./cpc-conf get cpcready.conf database host
# Output: localhost

./cpc-conf get cpcready.conf database port
# Output: 5432

# Get application information
./cpc-conf get cpcready.conf application name
# Output: MyApplication

# Get logging configuration
./cpc-conf get settings.ini logging level
# Output: INFO
```

### Practical Usage in Scripts

```bash
#!/bin/bash

# Initialize application configuration
./cpc-conf set app.ini database host "localhost"
./cpc-conf set app.ini database port 5432
./cpc-conf set app.ini database user "appuser"

./cpc-conf set app.ini cache enabled true
./cpc-conf set app.ini cache ttl 3600

# Read configuration for application startup
DB_HOST=$(./cpc-conf get app.ini database host)
DB_PORT=$(./cpc-conf get app.ini database port)
DB_USER=$(./cpc-conf get app.ini database user)

CACHE_ENABLED=$(./cpc-conf get app.ini cache enabled)
CACHE_TTL=$(./cpc-conf get app.ini cache ttl)

echo "Starting application with database: $DB_USER@$DB_HOST:$DB_PORT"
echo "Cache: $CACHE_ENABLED (TTL: $CACHE_TTL seconds)"
```

## 📋 INI File Format

The tool works with standard INI configuration files:

```ini
[database]
host=localhost
port=5432
name=myapp
user=dbuser

[application]
name=MyApplication
version=1.0.0
debug=true

[logging]
level=INFO
file=/var/log/app.log
max_size=10MB
```

## 🔧 Behavior Notes

- **File Creation**: If the specified file doesn't exist, it will be created automatically
- **Section Creation**: If a section doesn't exist, it will be created automatically
- **Key Updates**: If a key already exists in a section, its value will be updated
- **Key Addition**: If a key doesn't exist, it will be added to the specified section
- **Silent Success**: No output is produced for successful operations (Unix philosophy)
- **Detailed Errors**: Clear error messages for failures with appropriate exit codes
- **Section Format**: Section names are specified without brackets in command line arguments

## 📊 Exit Codes

| Code | Description |
|------|-------------|
| `0` | Success (silent operation) |
| `1` | Error (file not found, key not found, invalid arguments, etc.) |

## 🛠️ Development

### Building from Source

```bash
# Clone the repository
git clone https://github.com/CPCReady/cpc-conf.git
cd toolchain/tools/cpc-conf

# Compile
gcc cpc-conf.c -o cpc-conf

# Test
./cpc-conf --version
```

### Testing

```bash
# Create test configuration
./cpc-conf set test.ini app name "TestApp"
./cpc-conf set test.ini app version "1.0.0"
./cpc-conf set test.ini database host "localhost"

# Verify values
./cpc-conf get test.ini app name
./cpc-conf get test.ini app version
./cpc-conf get test.ini database host

# Check file content
cat test.ini
```

### Integration Testing

```bash
# Test error handling
./cpc-conf get nonexistent.ini section key  # Should fail gracefully
./cpc-conf get test.ini nosection key        # Should report key not found

# Test silent success
./cpc-conf set test.ini section key value   # Should produce no output
echo "Exit code: $?"                       # Should show: Exit code: 0
```

## 🎯 Use Cases

### Application Configuration
- Database connection settings
- API endpoints and credentials
- Feature flags and toggles
- Logging and monitoring configuration

### System Administration
- Service configuration files
- Environment-specific settings
- Deployment configurations
- Multi-tenant application settings

### Development Environments
- Local development settings
- Testing configurations
- CI/CD pipeline parameters
- Build and deployment options

## 📄 License

Copyright (C) 2025 Destroyer. All rights reserved.

## 🔗 Links

- [CPCReady Toolchain](https://github.com/CPCReady)
- [Documentation](https://cpcready.readthedocs.io/es/latest/)
- [Issues](https://github.com/CPCReady/cpc-conf/issues)
- [Releases](https://github.com/CPCReady/cpc-conf/releases)

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📚 Related Tools

- [`cpc-conf`](../cpc-conf/) - Simple key-value configuration management
- [`cpc-json`](../cpc-json/) - JSON configuration management (coming soon)
- [`cpc-yaml`](../cpc-yaml/) - YAML configuration management (coming soon)

---

**CPCReady Toolchain - cpc-conf** - Making configuration management simple and efficient.