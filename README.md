# Data Structures 

An implementations of common data structures in C. 

## 🛠️ Build and Development

This project uses **CMake** and **Ninja** for building. There are two distinct setup methods to ensure accessibility and reproducibility.

### Nix Environment ❄️

If you have [Nix installed](https://nixos.org/download) and enabled **Flakes**, this is the fastest way to get a complete development shell with all dependencies (**Clang/GCC, CMake, Ninja**, etc.) configured correctly.

#### Setup Steps
Enter the Development Shell:** This command automatically reads the `flake.nix` and sets up the required environment without affecting your host system.

```bash
nix develop
nix build
nix run
```

### Non-Nix Users ⚙️

If you do not use Nix, you must ensure the following dependencies are installed on your system.

#### Prerequisites

You must have the following installed and available in your system's PATH:

* **C/C++ Compiler:** Clang (v21+)
* **Build System Generator:** CMake (v4.1+)
* **Build Tool:** Ninja (or change the generator in the configuration step below to `"Unix Makefiles"`).

#### Setup Steps
Configure the Build:** Create the build directory and generate the Ninja build files.
```bash
cmake -S . -B build -G Ninja
cmake --build <folder>
./build/your_executable_name
```

## 🗑️ Cleanup

To remove all build artifacts and return the repository to a clean state:

```bash
rm -rf <folder> # Build folder chosen
rm -f result  # Removes the Nix build symlink if present
```
