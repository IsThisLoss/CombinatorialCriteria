#ifndef SERIESTABLE_H
#define SERIESTABLE_H

#define SERIES_TABLE_SIZE 5

#include <cstdlib> // size_t

/**
 * @class SeriesTable
 * @brief The SeriesTable class stores table with correlations
 * between n_1, n_2 values and R_min, R_max velues
 */
class SeriesTable
{
public:
    /**
     * @brief SeriesTable is a default ctor which initialize table
     * with correlations
     */
    SeriesTable();

    /**
     * @brief check get R_min and R_max by n_1 and n_2 and check whether R_min <= R <= R_max is true
     * @param n_1 is the number of elements greater than mean
     * @param n_2 is the number of elements less than mean
     * @param R is the number of series
     * @param R_min is a R_min value used to check
     * @param R_max is a R_max value used to check
     * @return true if R_min <= R <= R_max, false otherwise
     */
    bool check(size_t n_1, size_t n_2, int R, int& R_min, int& R_max) const;

private:
    /**
     * @struct Pair is a structure to store pair of R_min and R_max
     * @brief The Pair struct
     */
    struct Pair final
    {
        int R_min;
        int R_max;
    };

    /**
     * @brief table is a hardcoded two-dimension array which stores correlations between
     * n_1, n_2 and pairs of R_min, R_max
     */
    Pair table[SERIES_TABLE_SIZE][SERIES_TABLE_SIZE];

    // n_i = 2*i+4;
    // i = (n_i - 4)/2;

    /**
     * @brief map from n_i to array index by i = (n_i - 4)/2
     * @param n is a value on row or on column
     * @return {@link table} index
     */
    inline size_t map(size_t n) const {return (n-4)/2;}

    /**
     * @brief valid check if 4 <= n <= 12
     * @param n is a value on row or on column
     * @return true if 4 <= n <= 12, false otherwise
     */
    inline bool valid(size_t n) const {return (4 <= n && n <= 12);}
};

#endif // SERIESTABLE_H
