# Caesar-Problem-Solver

Caesar-Problem-Solver is a CLI tool to encrypt or/and decrypt English text
encrypted with the Caesar cipher.

If you have a large English text encrypted with the Caesar cipher, but
don't have a key to decrypt the text, the tool helps you. It can perform frequency analysis to find the key and then decrypt the text.

The tool accepts **mode**, **input** file path, **output** file path and
**key** as CLI parameters.

**mode** - encryption or decryption.

**input/output** - a path to a text file.

**key** - a shift (from 1 to 25) to perform encryption or decryption.

## How to build the tool

``chmod +x build.sh && ./build.sh``

## How to run the tool

### Encrypt a *plaintext* with a *key* and save it as a *ciphertext*  

``bin/caesar_problem_solver -e plaintext-path ciphertext-path key``

### Decrypt a *ciphertext* with a *key* and save it as a *plaintext*  

``bin/caesar_problem_solver -d ciphertext-path plaintext-path key``

### Decrypt a *ciphertext* using frequency analysis and save it as a *plaintext*

``bin/caesar_problem_solver -d ciphertext-path plaintext-path``
