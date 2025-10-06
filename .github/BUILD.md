# GitHub Actions CI/CD

This project uses GitHub Actions to automatically build binaries for multiple platforms and architectures.

## Supported Platforms

### Linux
- **x86_64 (amd64)**: Standard 64-bit Intel/AMD processors
- **ARM64 (aarch64)**: 64-bit ARM processors (Raspberry Pi 4, AWS Graviton, etc.)
- **ARMhf**: 32-bit ARM with hardware floating point (Raspberry Pi 2/3)

### macOS
- **x86_64 (Intel)**: Intel-based Macs
- **ARM64 (Apple Silicon)**: M1/M2/M3 Macs

## Build Process

The build process is triggered on:
- **Push** to main/master/develop branches
- **Pull requests** to main/master
- **Tags** starting with 'v' (for releases)
- **Manual dispatch** from GitHub Actions tab

### Build Matrix

Each platform/architecture combination:
1. Sets up the appropriate build environment
2. Installs cross-compilation tools if needed
3. Compiles the binary with optimizations
4. Tests basic functionality
5. Uploads artifacts

### Cross-Compilation Details

#### Linux ARM builds
- Uses `gcc-aarch64-linux-gnu` for ARM64
- Uses `gcc-arm-linux-gnueabihf` for ARMhf
- Produces statically linked binaries for maximum compatibility

#### macOS builds
- Uses Clang with target-specific flags
- ARM64 targets macOS 11+ (required for Apple Silicon)
- x86_64 targets macOS 10.12+ for broader compatibility

## Release Process

When a tag starting with 'v' is pushed:

1. **Build** all platform binaries
2. **Package** each binary into tar.gz archives
3. **Generate** SHA256 checksums
4. **Create** GitHub release with:
   - All binary archives
   - Checksum file
   - Auto-generated release notes
   - Installation instructions

## File Naming Convention

Binaries follow the pattern: `cpc-conf-<os>-<arch>`

Examples:
- `cpc-conf-linux-amd64`
- `cpc-conf-linux-arm64`
- `cpc-conf-linux-armhf`
- `cpc-conf-darwin-amd64`
- `cpc-conf-darwin-arm64`

## Testing

Each build includes basic smoke tests:
- Version command execution
- Configuration file read/write operations
- Binary functionality verification

## Artifacts

Build artifacts are:
- **Retained for 30 days** for regular builds
- **Permanently available** as release assets for tagged builds
- **Include file information** (architecture, file size, etc.)

## Local Development

To test the build process locally:

```bash
# Install cross-compilation tools (Ubuntu/Debian)
sudo apt-get install gcc-aarch64-linux-gnu gcc-arm-linux-gnueabihf

# Build for different targets
gcc -static -O2 -o cpc-conf-linux-amd64 cpc-conf.c
aarch64-linux-gnu-gcc -static -O2 -o cpc-conf-linux-arm64 cpc-conf.c
arm-linux-gnueabihf-gcc -static -O2 -o cpc-conf-linux-armhf cpc-conf.c

# On macOS
clang -O2 -target x86_64-apple-macos10.12 -o cpc-conf-darwin-amd64 cpc-conf.c
clang -O2 -target arm64-apple-macos11 -o cpc-conf-darwin-arm64 cpc-conf.c
```

## Troubleshooting

### Common Issues

1. **Cross-compilation failures**: Ensure cross-compilation tools are installed
2. **ARM testing limitations**: ARM binaries can't be tested on x86_64 runners
3. **macOS compatibility**: Different minimum OS versions for Intel vs Apple Silicon

### Debug Information

Each build produces `.info` files containing:
- File type and architecture information
- File size and permissions
- Build timestamp and details