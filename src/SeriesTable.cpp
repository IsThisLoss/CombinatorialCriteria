#include <cstring>

#include "include/SeriesTable.h"

SeriesTable::SeriesTable()
{

    for (unsigned i = 0; i < SERIES_TABLE_SIZE; i++)
        memset(table[i], 0x0, sizeof(table[i]));

    table[0][0] = {2, 8};
    table[0][1] = {3, 9};
    table[0][2] = {3, 10};
    table[0][3] = {3, 10};
    table[0][4] = {4, 10};

    table[1][1] = {3, 11};
    table[1][2] = {4, 12};
    table[1][3] = {5, 12};
    table[1][4] = {5, 13};

    table[2][2] = {5, 13};
    table[2][3] = {6, 14};
    table[2][4] = {6, 15};

    table[3][3] = {6, 16};
    table[3][4] = {7, 17};

    table[4][4] = {8, 18};
}

bool SeriesTable::check(size_t n_1, size_t n_2, int R, int& R_min, int& R_max) const
{
    if (valid(n_1) && valid(n_2))
    {
        auto pair = table[map(n_2)][map(n_1)];
        R_min = pair.R_min;
        R_max = pair.R_max;
        return (R_min <= R && R <= R_max);
    }
    return false;
}
