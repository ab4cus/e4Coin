#!/bin/bash
# use testnet settings,  if you need mainnet,  use ~/.e4coincore/e4coind.pid file instead
e4coin_pid=$(<~/.e4coincore/testnet3/e4coind.pid)
sudo gdb -batch -ex "source debug.gdb" e4coind ${e4coin_pid}
