#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

E4COIND=${E4COIND:-$SRCDIR/e4coind}
E4COINCLI=${E4COINCLI:-$SRCDIR/e4coin-cli}
E4COINTX=${E4COINTX:-$SRCDIR/e4coin-tx}
E4COINQT=${E4COINQT:-$SRCDIR/qt/e4coin-qt}

[ ! -x $E4COIND ] && echo "$E4COIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
E4CVER=($($E4COINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for bitcoind if --version-string is not set,
# but has different outcomes for bitcoin-qt and bitcoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$E4COIND --version | sed -n '1!p' >> footer.h2m

for cmd in $E4COIND $E4COINCLI $E4COINTX $E4COINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${E4CVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${E4CVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
