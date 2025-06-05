# p4t

## Dependencies

### p4api

You can download p4api from the [official website](https://www.perforce.com/downloads/helix-core-c/c-api) or the [archive]( https://filehost.perforce.com/perforce/r25.1/bin.mingw64x64/p4api-openssl3_gcc8_win32_seh.zip)

```sh
curl -Lo p4api.zip https://filehost.perforce.com/perforce/r25.1/bin.mingw64x64/p4api-openssl3_gcc8_win32_seh.zip
```

### mingw64 packages

First open mingw64 shell: `C:/msys64/msys2_shell.cmd -defterm -here -no-start -mingw64`

```sh
pacman -S mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-openssl
```

Add `C:/msys64/mingw64/bin` to your PATH environment variable

## Build

```sh
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```
