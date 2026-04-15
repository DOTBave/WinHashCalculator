# Hash Calculator

A very simple, light weight, cross-platform CLI tool that simplifies file hashing. Instead of memorizing complex syntax for different operating systems, this program wraps native commands to generate results instantly.

## Features
* **Cross-Platform:** Uses `certutil` on Windows and `openssl` on macOS/Linux.
* **No Dependencies:** Doesn't require external hashing libraries.
* **Drag-and-Drop Support:** Supports file paths passed via terminal arguments or by simply dragging a file onto the executable icon.

## Prerequisites
* **Windows:** No additional setup required.
* **macOS/Linux:** `openssl` is required (it is usually already installed on macOS and Linux)

## Usage
Run the program from the terminal by passing a file path, or drag a file onto the program:

```bash
./HashCalculator [path_to_file]

Once launched, follow the on-screen prompt to select your desired hashing algorithm:

Legacy: MD2, MD4, MD5

Secure: SHA1, SHA256, SHA384, SHA512
