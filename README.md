# Data Structures 

An implementations of common data structures in C. 

***

## 🛠️ Build and Development

This project uses **CMake** and **Ninja** for building. We provide two distinct setup methods to ensure accessibility and reproducibility.

### Method 1: Nix Environment ❄️

If you have [Nix installed](https://nixos.org/download) and enabled **Flakes**, this is the fastest way to get a complete development shell with all dependencies (**Clang/GCC, CMake, Ninja**, etc.) configured correctly.

#### Setup Steps

1.  **Enter the Development Shell:** This command automatically reads the `flake.nix` and sets up the required environment without affecting your host system.
    ```bash
    nix develop
    ```

2.  **Build the Project:** Once inside the Nix shell, use the standard CMake commands:
    ```bash
    # 1. Configure the build (out-of-source)
    cmake -S . -B build -G Ninja

    # 2. Compile
    cmake --build build

    # 3. (Optional) Run tests
    ctest --test-dir build
    ```

3.  **Run the Executable:**
    ```bash
    ./build/your_executable_name
    ```

4.  **Exit:** Type `exit` or press `Ctrl+D` to leave the isolated Nix environment.

***

### Method 2: Non-Nix Users ⚙️

If you do not use Nix, you must ensure the following dependencies are installed on your system.

#### Prerequisites

You must have the following installed and available in your system's PATH:

* **C/C++ Compiler:** GCC (v10+) or Clang (v12+)
* **Build System Generator:** CMake (v3.18+)
* **Build Tool:** Ninja (or change the generator in the configuration step below to `"Unix Makefiles"`).

#### Setup Steps

1.  **Configure the Build:** Create the build directory and generate the Ninja build files.
    ```bash
    # Ensure you are in the project root
    cmake -S . -B build -G Ninja
    ```

2.  **Compile the Project:**
    ```bash
    cmake --build build
    ```

3.  **Run the Executable:**
    ```bash
    ./build/your_executable_name
    ```
***

## 🗑️ Cleanup

To remove all build artifacts and return the repository to a clean state:

```bash
rm -rf build
rm -f compile_commands.json
rm -f result  # Removes the Nix build symlink if present
```
