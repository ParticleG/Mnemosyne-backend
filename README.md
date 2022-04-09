# Mnemosyne-drogon
The backend for Mnemosyne system
<p style="text-align:center">
    <img src="https://img.shields.io/github/languages/code-size/ParticleG/Mnemosyne-drogon.svg?style=flat-square" alt="Code size"/>
    <img src="https://img.shields.io/github/repo-size/ParticleG/Mnemosyne-drogon.svg?style=flat-square" alt="GitHub repo size"/>
</p>

## Develop

### Requirements

#### Windows

- CMake 3.20.x and above
- Git
- Visual Studio 2019 and above (With English language pack)
- PostgresSQL server 14 and above
- Redis server 3.2.x and above (Use WSL or remote linux server)

#### linux

- CMake 3.20.x and above
- Git
- GCC 9 or Clang 9 and above (10 if you want to use coroutine)
- PostgresSQL server 14 and above
- Redis server 3.2.x and above

### Steps

1. Clone the repository

```bash
git clone --recursive https://github.com/ParticleG/Mnemosyne-drogon
```

2. Create config.json from the config.json.example in each subdirectory

3. Create build directory and run CMake

```bash
# Linux
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" .. 
cmake --build .. --target all

# Windows
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - NMake Makefiles" .. 
cmake --build .. --target all
```

4. Run server executable
