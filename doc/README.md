e4Coin Core 0.14.0
=====================

This is the official reference wallet for e4Coin digital currency and comprises the backbone of the e4Coin peer-to-peer network. You can [download e4Coin Core](https://www.e4coin.org/downloads/) or [build it yourself](#building) using the guides below.

Running
---------------------
The following are some helpful notes on how to run e4Coin on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/e4coin-qt` (GUI) or
- `bin/e4coind` (headless)

### Windows

Unpack the files into a directory, and then run e4coin-qt.exe.

### OS X

Drag e4Coin-Qt to your applications folder, and then run e4Coin-Qt.

### Need Help?

* See the [e4Coin documentation](https://docs.e4coin.org)
for help and more information.
* See the [e4Coin Developer Documentation](https://e4coin-docs.github.io/) 
for technical specifications and implementation details.
* Ask for help on [e4Coin Nation Discord](http://e4coinchat.org)
* Ask for help on the [e4Coin Forum](https://e4coin.org/forum)

Building
---------------------
The following are developer notes on how to build e4Coin Core on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OS X Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The e4Coin Core repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- Source Code Documentation ***TODO***
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Travis CI](travis-ci.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* Discuss on the [e4Coin Forum](https://e4coin.org/forum), in the Development & Technical Discussion board.
* Discuss on [e4Coin Nation Discord](http://e4coinchat.org)

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [ZMQ](zmq.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
