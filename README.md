# DES Algorithm

C++ Implementation of DES algorithm.

## Installation

Clone the repository and inside the folder run the following commands:

```sh
mkdir build
cd build
cmake ..
make
```

It will build the project and create a binary file named "des" inside the build/bin folder.

Now, run the file using

```sh
./bin/des
```

## Usage

The implementation is in [ECB mode](<https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Electronic_codebook_(ECB)>) and uses [PKCS#7](<https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS%235_and_PKCS%237>) for padding.

The script allows encryption and decryption using a 8-byte key for both text (in hex) and binary files.

1. For Text based

    - Enter text to be encrypted/decrypted (in hex) and key (in hex).

2. For File based (a binary file)
    - Enter input file location, output file location and key (in hex).
    - The script will encrypt the input file in binary file and decrypt it in original form.
