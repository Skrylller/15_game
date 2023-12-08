#include "kkk.h"

Kkk::Kkk()
{
    int a = 0;
    int b = a + 3;
}

int Kkk::rowCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant Kkk::data(const QModelIndex &index, int role) const
{
    return 1;
}

bool Kkk::move(int index)
{
    return true;
}

#include "kkk.h"
