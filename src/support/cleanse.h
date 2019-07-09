// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The dash Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef E4COIN_SUPPORT_CLEANSE_H
#define E4COIN_SUPPORT_CLEANSE_H

#include <stdlib.h>

// Attempt to overwrite data in the specified memory span.
void memory_cleanse(void *ptr, size_t len);

#endif // E4COIN_SUPPORT_CLEANSE_H
