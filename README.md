# Caesar-Problem-Solver

## Description

Caesar-Problem-Solver is a CLI tool to encrypt or/and decrypt English text
encrypted with Caesar cipher.

The tool accepts **mode**, **input** file path, **output** filepath and
**key** as CLI arguments.

**mode** - encryption **(-e)** or decryption **(-d)** mode.

**input/output** - a path to a text file.

**key** - a shift (from 1 to 25) to perform encryption or decryption.

## How to build the tool

``chmod +x && ./build.sh``

## How to run the tool

### Encrypt a *plaintext* with a *key* and save it as a *ciphertext*  

``bin/caesar_problem_solver -e plaintext-path ciphertext-path key``

### Decrypt a *ciphertext* with a *key* and save it as a *plaintext*  

``bin/caesar_problem_solver -d ciphertext-path plaintext-path key``

### Decrypt a *ciphertext* without a key and save it as a *plaintext*

``bin/caesar_problem_solver -d ciphertext-path plaintext-path``
