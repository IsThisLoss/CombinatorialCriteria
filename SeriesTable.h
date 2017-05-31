#ifndef SERIESTABLE_H
#define SERIESTABLE_H

#define SERIES_TABLE_SIZE 5

#include <cstdlib>

class SeriesTable
{
public:
    SeriesTable();
    bool check(size_t n_1, size_t n_2, int R, int& R_min, int& R_max) const;

private:
    struct Pair
    {
        int R_min;
        int R_max;
    };
    Pair table[SERIES_TABLE_SIZE][SERIES_TABLE_SIZE];

    // n_i = 2*i+4;
    // i = (n_i - 4)/2;
    inline size_t map(size_t n) const {return (n-4)/2;}
    inline bool valid(size_t n) const {return (4 <= n && n <= 12);}
};

#endif // SERIESTABLE_H
