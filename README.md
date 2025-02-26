# Crust Game Engine

Crust is a collection of tools designed to assist in the development of games using the MLX library on Linux.

## Installation

Before installing the Crust Game Engine, you need to have the following dependencies installed on your system:

- **clang** (or any compatible C compiler; you can override with the proper `CC` argument)
- **make**
- **git** (or your preferred version control system)
- **libbsd** (BSD library headers)

Below are commands to install these dependencies on several unconventional or lesser‐known Linux distributions:

### Debian/Ubuntu

```bash
sudo apt-get install clang make git libbsd-dev
```

### Fedora

```bash
sudo dnf install clang make git libbsd-devel
```

### Arch Linux

```bash
sudo pacman -S clang make git libbsd
```

### YiffOS

```bash
sudo bulge i llvm make git libbsd
```

### Chimera Linux

```bash
sudo apk add clang gmake git libbsd
```

After installing the dependencies, clone the repository and build the Crust Game Engine with these commands:

```bash
git clone https://github.com/cliftontoaster-reid/crust
cd crust
make
```

To install the engine system-wide, run:

```bash
sudo make install
```
