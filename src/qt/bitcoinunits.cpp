// Copyright (c) 2011-2015 The dash Core developers
// Copyright (c) 2014-2017 The e4Coin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "bitcoinunits.h"
#include "chainparams.h"
#include "primitives/transaction.h"

#include <QSettings>
#include <QStringList>

e4coinUnits::e4coinUnits(QObject *parent):
        QAbstractListModel(parent),
        unitlist(availableUnits())
{
}

QList<e4coinUnits::Unit> e4coinUnits::availableUnits()
{
    QList<e4coinUnits::Unit> unitlist;
    unitlist.append(E4C);
    unitlist.append(mE4C);
    unitlist.append(uE4C);
    unitlist.append(puya);
    return unitlist;
}

bool e4coinUnits::valid(int unit)
{
    switch(unit)
    {
    case E4C:
    case mE4C:
    case uE4C:
    case puya:
        return true;
    default:
        return false;
    }
}

QString e4coinUnits::name(int unit)
{
    if(Params().NetworkIDString() == CBaseChainParams::MAIN)
    {
        switch(unit)
        {
            case E4C: return QString("E4C");
            case mE4C: return QString("Real");
            case uE4C: return QString::fromUtf8("Locha");
            case puyas: return QString("Puyas");
            default: return QString("???");
        }
    }
    else
    {
        switch(unit)
        {
            case E4C: return QString("tE4C");
            case mE4C: return QString("mtReal");
            case uE4C: return QString::fromUtf8("μtLocha");
            case puyas: return QString("tPuyas");
            default: return QString("???");
        }
    }
}

QString e4coinUnits::description(int unit)
{
    if(Params().NetworkIDString() == CBaseChainParams::MAIN)
    {
        switch(unit)
        {
            case E4C: return QString("e4Coin");
            case mE4C: return QString("Milli-e4Coin (1 / 1" THIN_SP_UTF8 "000)");
            case uE4C: return QString("Micro-e4Coin (1 / 1" THIN_SP_UTF8 "000" THIN_SP_UTF8 "000)");
            case puyas: return QString("Ten Nano-e4Coin (1 / 100" THIN_SP_UTF8 "000" THIN_SP_UTF8 "000)");
            default: return QString("???");
        }
    }
    else
    {
        switch(unit)
        {
            case E4C: return QString("Teste4Coins");
            case mE4C: return QString("Milli-Teste4Coin (1 / 1" THIN_SP_UTF8 "000)");
            case uE4C: return QString("Micro-Teste4Coin (1 / 1" THIN_SP_UTF8 "000" THIN_SP_UTF8 "000)");
            case puyas: return QString("Ten Nano-Teste4Coin (1 / 100" THIN_SP_UTF8 "000" THIN_SP_UTF8 "000)");
            default: return QString("???");
        }
    }
}

qint64 e4coinUnits::factor(int unit)
{
    switch(unit)
    {
    case E4C:  return 100000000;
    case mE4C: return 100000;
    case uE4C: return 100;
    case puyas: return 1;
    default:   return 100000000;
    }
}

int e4coinUnits::decimals(int unit)
{
    switch(unit)
    {
    case E4C: return 8;
    case mE4C: return 5;
    case uE4C: return 2;
    case puyas: return 0;
    default: return 0;
    }
}

QString e4coinUnits::format(int unit, const CAmount& nIn, bool fPlus, SeparatorStyle separators)
{
    // Note: not using straight sprintf here because we do NOT want
    // localized number formatting.
    if(!valid(unit))
        return QString(); // Refuse to format invalid unit
    qint64 n = (qint64)nIn;
    qint64 coin = factor(unit);
    int num_decimals = decimals(unit);
    qint64 n_abs = (n > 0 ? n : -n);
    qint64 quotient = n_abs / coin;
    qint64 remainder = n_abs % coin;
    QString quotient_str = QString::number(quotient);
    QString remainder_str = QString::number(remainder).rightJustified(num_decimals, '0');

    // Use SI-style thin space separators as these are locale independent and can't be
    // confused with the decimal marker.
    QChar thin_sp(THIN_SP_CP);
    int q_size = quotient_str.size();
    if (separators == separatorAlways || (separators == separatorStandard && q_size > 4))
        for (int i = 3; i < q_size; i += 3)
            quotient_str.insert(q_size - i, thin_sp);

    if (n < 0)
        quotient_str.insert(0, '-');
    else if (fPlus && n > 0)
        quotient_str.insert(0, '+');

    if (num_decimals <= 0)
        return quotient_str;

    return quotient_str + QString(".") + remainder_str;
}


// NOTE: Using formatWithUnit in an HTML context risks wrapping
// quantities at the thousands separator. More subtly, it also results
// in a standard space rather than a thin space, due to a bug in Qt's
// XML whitespace canonicalisation
//
// Please take care to use formatHtmlWithUnit instead, when
// appropriate.

QString e4coinUnits::formatWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators)
{
    return format(unit, amount, plussign, separators) + QString(" ") + name(unit);
}

QString e4coinUnits::formatHtmlWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators)
{
    QString str(formatWithUnit(unit, amount, plussign, separators));
    str.replace(QChar(THIN_SP_CP), QString(THIN_SP_HTML));
    return QString("<span style='white-space: nowrap;'>%1</span>").arg(str);
}

QString e4coinUnits::floorWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators)
{
    QSettings settings;
    int digits = settings.value("digits").toInt();

    QString result = format(unit, amount, plussign, separators);
    if(decimals(unit) > digits) result.chop(decimals(unit) - digits);

    return result + QString(" ") + name(unit);
}

QString e4coinUnits::floorHtmlWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators)
{
    QString str(floorWithUnit(unit, amount, plussign, separators));
    str.replace(QChar(THIN_SP_CP), QString(THIN_SP_HTML));
    return QString("<span style='white-space: nowrap;'>%1</span>").arg(str);
}

bool e4coinUnits::parse(int unit, const QString &value, CAmount *val_out)
{
    if(!valid(unit) || value.isEmpty())
        return false; // Refuse to parse invalid unit or empty string
    int num_decimals = decimals(unit);

    // Ignore spaces and thin spaces when parsing
    QStringList parts = removeSpaces(value).split(".");

    if(parts.size() > 2)
    {
        return false; // More than one dot
    }
    QString whole = parts[0];
    QString decimals;

    if(parts.size() > 1)
    {
        decimals = parts[1];
    }
    if(decimals.size() > num_decimals)
    {
        return false; // Exceeds max precision
    }
    bool ok = false;
    QString str = whole + decimals.leftJustified(num_decimals, '0');

    if(str.size() > 18)
    {
        return false; // Longer numbers will exceed 63 bits
    }
    CAmount retvalue(str.toLongLong(&ok));
    if(val_out)
    {
        *val_out = retvalue;
    }
    return ok;
}

QString e4coinUnits::getAmountColumnTitle(int unit)
{
    QString amountTitle = QObject::tr("Amount");
    if (e4coinUnits::valid(unit))
    {
        amountTitle += " ("+e4coinUnits::name(unit) + ")";
    }
    return amountTitle;
}

int e4coinUnits::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return unitlist.size();
}

QVariant e4coinUnits::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row >= 0 && row < unitlist.size())
    {
        Unit unit = unitlist.at(row);
        switch(role)
        {
        case Qt::EditRole:
        case Qt::DisplayRole:
            return QVariant(name(unit));
        case Qt::ToolTipRole:
            return QVariant(description(unit));
        case UnitRole:
            return QVariant(static_cast<int>(unit));
        }
    }
    return QVariant();
}

CAmount e4coinUnits::maxMoney()
{
    return MAX_MONEY;
}
