# Copyright (c) 2013-2016 The dash Core developers
# Copyright (c) 2014-2018 The e4Coin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS) $(ERROR_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

E4COIN_CONFIG_INCLUDES=-I$(builddir)/config
E4COIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

E4COIN_INCLUDES += -I$(srcdir)/secp256k1/include
E4COIN_INCLUDES += $(UNIVALUE_CFLAGS)

BLS_LIBS=-lchiabls -lgmp

LIBE4COIN_SERVER=libe4coin_server.a
LIBE4COIN_COMMON=libe4coin_common.a
LIBE4COIN_CONSENSUS=libe4coin_consensus.a
LIBE4COIN_CLI=libe4coin_cli.a
LIBE4COIN_UTIL=libe4coin_util.a
LIBE4COIN_CRYPTO=crypto/libe4coin_crypto.a
LIBE4COINQT=qt/libe4coinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBE4COIN_ZMQ=libe4coin_zmq.a
endif
if BUILD_E4COIN_LIBS
LIBE4COINCONSENSUS=libe4coinconsensus.la
endif
if ENABLE_WALLET
LIBE4COIN_WALLET=libe4coin_wallet.a
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBE4COIN_CRYPTO) \
  $(LIBE4COIN_UTIL) \
  $(LIBE4COIN_COMMON) \
  $(LIBE4COIN_CONSENSUS) \
  $(LIBE4COIN_SERVER) \
  $(LIBE4COIN_CLI) \
  $(LIBE4COIN_WALLET) \
  $(LIBE4COIN_ZMQ)

lib_LTLIBRARIES = $(LIBE4COINCONSENSUS)

bin_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_E4COIND
  bin_PROGRAMS += e4coind
endif

if BUILD_E4COIN_UTILS
  bin_PROGRAMS += e4coin-cli e4coin-tx
endif

.PHONY: FORCE check-symbols check-security
# e4coin core #
E4COIN_CORE_H = \
  addrdb.h \
  activemasternode.h \
  addressindex.h \
  spentindex.h \
  addrman.h \
  alert.h \
  base58.h \
  bip39.h \
  bip39_english.h \
  blockencodings.h \
  bloom.h \
  cachemap.h \
  cachemultimap.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  ctpl.h \
  evo/evodb.h \
  evo/specialtx.h \
  evo/providertx.h \
  evo/deterministicmns.h \
  evo/cbtx.h \
  evo/simplifiedmns.h \
  privatesend.h \
  privatesend-client.h \
  privatesend-server.h \
  privatesend-util.h \
  dsnotificationinterface.h \
  governance.h \
  governance-classes.h \
  governance-exceptions.h \
  governance-object.h \
  governance-validators.h \
  governance-vote.h \
  governance-votedb.h \
  flat-database.h \
  hdchain.h \
  httprpc.h \
  httpserver.h \
  indirectmap.h \
  init.h \
  instantx.h \
  key.h \
  keepass.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  llmq/quorums_commitment.h \
  llmq/quorums_blockprocessor.h \
  llmq/quorums_dummydkg.h \
  llmq/quorums_utils.h \
  llmq/quorums_init.h \
  masternode.h \
  masternode-payments.h \
  masternode-sync.h \
  masternodeman.h \
  masternodeconfig.h \
  memusage.h \
  merkleblock.h \
  messagesigner.h \
  miner.h \
  net.h \
  net_processing.h \
  netaddress.h \
  netbase.h \
  netfulfilledman.h \
  netmessagemaker.h \
  noui.h \
  policy/fees.h \
  policy/policy.h \
  pow.h \
  protocol.h \
  random.h \
  reverselock.h \
  rpc/client.h \
  rpc/protocol.h \
  rpc/server.h \
  rpc/register.h \
  scheduler.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/ismine.h \
  spork.h \
  streams.h \
  support/allocators/mt_pooled_secure.h \
  support/allocators/pooled_secure.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadsafety.h \
  threadinterrupt.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utiltime.h \
  validation.h \
  validationinterface.h \
  versionbits.h \
  wallet/coincontrol.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libe4coin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between e4coind and e4coin-qt
libe4coin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(E4COIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libe4coin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libe4coin_server_a_SOURCES = \
  activemasternode.cpp \
  addrman.cpp \
  addrdb.cpp \
  alert.cpp \
  bloom.cpp \
  blockencodings.cpp \
  chain.cpp \
  checkpoints.cpp \
  dsnotificationinterface.cpp \
  evo/evodb.cpp \
  evo/specialtx.cpp \
  evo/providertx.cpp \
  evo/deterministicmns.cpp \
  evo/cbtx.cpp \
  evo/simplifiedmns.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  instantx.cpp \
  dbwrapper.cpp \
  governance.cpp \
  governance-classes.cpp \
  governance-object.cpp \
  governance-validators.cpp \
  governance-vote.cpp \
  governance-votedb.cpp \
  llmq/quorums_commitment.cpp \
  llmq/quorums_blockprocessor.cpp \
  llmq/quorums_dummydkg.cpp \
  llmq/quorums_utils.cpp \
  llmq/quorums_init.cpp \
  masternode.cpp \
  masternode-payments.cpp \
  masternode-sync.cpp \
  masternodeconfig.cpp \
  masternodeman.cpp \
  merkleblock.cpp \
  messagesigner.cpp \
  miner.cpp \
  net.cpp \
  netfulfilledman.cpp \
  net_processing.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  pow.cpp \
  privatesend.cpp \
  privatesend-server.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/masternode.cpp \
  rpc/governance.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/rpcevo.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  script/ismine.cpp \
  sendalert.cpp \
  spork.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(E4COIN_CORE_H)

if ENABLE_ZMQ
libe4coin_zmq_a_CPPFLAGS = $(E4COIN_INCLUDES) $(ZMQ_CFLAGS)
libe4coin_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libe4coin_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif


# wallet: shared between e4coind and e4coin-qt, but only linked
# when wallet enabled
libe4coin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(E4COIN_INCLUDES)
libe4coin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libe4coin_wallet_a_SOURCES = \
  keepass.cpp \
  privatesend-client.cpp \
  privatesend-util.cpp \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  $(E4COIN_CORE_H)

# crypto primitives library
crypto_libe4coin_crypto_a_CPPFLAGS = $(AM_CPPFLAGS) $(E4COIN_CONFIG_INCLUDES) $(PIC_FLAGS)
crypto_libe4coin_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) $(PIC_FLAGS)
crypto_libe4coin_crypto_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/aes_helper.c \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h

# x11
crypto_libe4coin_crypto_a_SOURCES += \
  crypto/blake.c \
  crypto/bmw.c \
  crypto/cubehash.c \
  crypto/echo.c \
  crypto/groestl.c \
  crypto/jh.c \
  crypto/keccak.c \
  crypto/luffa.c \
  crypto/shavite.c \
  crypto/simd.c \
  crypto/skein.c \
  crypto/sph_blake.h \
  crypto/sph_bmw.h \
  crypto/sph_cubehash.h \
  crypto/sph_echo.h \
  crypto/sph_groestl.h \
  crypto/sph_jh.h \
  crypto/sph_keccak.h \
  crypto/sph_luffa.h \
  crypto/sph_shavite.h \
  crypto/sph_simd.h \
  crypto/sph_skein.h \
  crypto/sph_types.h

# consensus: shared between all executables that validate any consensus rules.
libe4coin_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(E4COIN_INCLUDES)
libe4coin_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libe4coin_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  bls/bls.cpp \
  bls/bls.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/e4coinconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  streams.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  utilstrencodings.cpp \
  utilstrencodings.h \
  version.h

# common: shared between e4coind, and e4coin-qt and non-server tools
libe4coin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(E4COIN_INCLUDES)
libe4coin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libe4coin_common_a_SOURCES = \
  amount.cpp \
  base58.cpp \
  bip39.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  hdchain.cpp \
  key.cpp \
  keystore.cpp \
  netaddress.cpp \
  netbase.cpp \
  protocol.cpp \
  scheduler.cpp \
  script/sign.cpp \
  script/standard.cpp \
  warnings.cpp \
  $(E4COIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libe4coin_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(E4COIN_INCLUDES)
libe4coin_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libe4coin_util_a_SOURCES = \
  bls/bls_ies.cpp \
  bls/bls_ies.h \
  bls/bls_worker.cpp \
  bls/bls_worker.h \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpc/protocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(E4COIN_CORE_H)

if GLIBC_BACK_COMPAT
libe4coin_util_a_SOURCES += compat/glibc_compat.cpp
AM_LDFLAGS += -Wl,--wrap=log2f -Wl,--wrap=__divmoddi4
endif

# cli: shared between e4coin-cli and e4coin-qt
libe4coin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(E4COIN_INCLUDES)
libe4coin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libe4coin_cli_a_SOURCES = \
  rpc/client.cpp \
  $(E4COIN_CORE_H)

nodist_libe4coin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# e4coind binary #
e4coind_SOURCES = e4coind.cpp
e4coind_CPPFLAGS = $(AM_CPPFLAGS) $(E4COIN_INCLUDES)
e4coind_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
e4coind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
e4coind_SOURCES += e4coind-res.rc
endif

e4coind_LDADD = \
  $(LIBE4COIN_SERVER) \
  $(LIBE4COIN_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBE4COIN_UTIL) \
  $(LIBE4COIN_WALLET) \
  $(LIBE4COIN_ZMQ) \
  $(LIBE4COIN_CONSENSUS) \
  $(LIBE4COIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

e4coind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS) $(BLS_LIBS)

# e4coin-cli binary #
e4coin_cli_SOURCES = e4coin-cli.cpp
e4coin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(E4COIN_INCLUDES) $(EVENT_CFLAGS)
e4coin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
e4coin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
e4coin_cli_SOURCES += e4coin-cli-res.rc
endif

e4coin_cli_LDADD = \
  $(LIBE4COIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBE4COIN_UTIL) \
  $(LIBE4COIN_CRYPTO)
e4coin_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS) $(BLS_LIBS)
#

# e4coin-tx binary #
e4coin_tx_SOURCES = e4coin-tx.cpp
e4coin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(E4COIN_INCLUDES)
e4coin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
e4coin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
e4coin_tx_SOURCES += e4coin-tx-res.rc
endif

e4coin_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBE4COIN_COMMON) \
  $(LIBE4COIN_UTIL) \
  $(LIBE4COIN_CONSENSUS) \
  $(LIBE4COIN_CRYPTO) \
  $(LIBSECP256K1)

e4coin_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS) $(BLS_LIBS)
#

# e4coinconsensus library #
if BUILD_E4COIN_LIBS
include_HEADERS = script/e4coinconsensus.h
libe4coinconsensus_la_SOURCES = $(crypto_libe4coin_crypto_a_SOURCES) $(libe4coin_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libe4coinconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libe4coinconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libe4coinconsensus_la_LIBADD = $(LIBSECP256K1) $(BLS_LIBS)
libe4coinconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_E4COIN_INTERNAL
libe4coinconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno

IMMER_DIST = immer

DISTCLEANFILES = obj/build.h

EXTRA_DIST = $(CTAES_DIST)
EXTRA_DIST += $(IMMER_DIST)


config/e4coin-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/e4coin-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/e4coin-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/e4coin-config.h.in

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) -c -o $@ $<

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
