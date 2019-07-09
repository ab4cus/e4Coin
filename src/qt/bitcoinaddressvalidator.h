// Copyright (c) 2011-2014 The dash Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef E4COIN_QT_E4COINADDRESSVALIDATOR_H
#define E4COIN_QT_E4COINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class e4coinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit e4coinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** e4coin address widget validator, checks for a valid bitcoin address.
 */
class e4coinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit e4coinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // E4COIN_QT_E4COINADDRESSVALIDATOR_H
