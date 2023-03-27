# libsodium keypair generator

This program generates a libsodium keypair and prints the public and/or secret key to the console or saves them to a file.

## Prerequisites

* libsodium: The program requires the libsodium library to be installed on your system. See the [libsodium installation instructions](https://libsodium.gitbook.io/doc/installation) for details.

## Usage

```shell
Usage: ./sodium-keygen [-f filename]

  -f filename Save the keys to the specified file
```

If the -f option is specified, the program saves the keys to the specified file basename instead of printing them to the console. The public key file will have an added ".pub.key" to the basename, the secret key an added ".priv.key".

## Examples

Generate and print the public and secret keys:

```bash
$ ./sodium-keygen
Public Key: 5bb5c5ed5a5e2609b7cf6b2c6f3b3c4d6e63aa6dce77a33ad4fcf9d9b16775f
Secret Key: 8f890aeedeed06ba556f6d2f439c8e3113c2ba1a7b931a172bbf8cfd735a697c
```

Generate and save the public and secret keys to a file:

```bash
$ ./sodium-keygen -f keys
$ cat keys.pub.key
5bb5c5ed5a5e2609b7cf6b2c6f3b3c4d6e63aa6dce77a33ad4fcf9d9b16775f
$ cat keys.priv.key
8f890aeedeed06ba556f6d2f439c8e3113c2ba1a7b931a172bbf8cfd735a697c
```

## License

This program is licensed under the Apache-2.0 License. See the LICENSE file for details.
