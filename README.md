# Crust Game Engine

Crust is a list of tools for assisting in the development of games using the MLX library for Linux.

## Installation

To install the Crust Game Engine, you must have the necessary dependencies installed on your system, being:

- clang (or any other C compiler adding the proper CC argument to the make command)
- make
- git (or rad)
- libbsd

To install the dependencies, you can use the following commands based on your distribution:

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

### Void Linux

```bash
sudo xbps-install clang make git libbsd-devel
```

### OpenSUSE

```bash
sudo zypper install clang make git libbsd0
```

### Solus

```bash
sudo eopkg install clang make git libbsd
```

### Gentoo

```bash
sudo emerge -av dev-lang/clang sys-devel/make dev-vcs/git dev-libs/libbsd
```

### Alpine Linux

```bash
sudo apk add clang make git libbsd-dev
```

After installing the dependencies, you can clone the repository and install the Crust Game Engine using the following commands:

```bash
git clone https://github.com/cliftontoaster-reid/crust
cd crust
make
```

As well the script is able to install the engine in your system, to do so, you can use the following command:

```bash
sudo make install
```
