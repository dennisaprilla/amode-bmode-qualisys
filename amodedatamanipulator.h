#ifndef AMODEDATAMANIPULATOR_H
#define AMODEDATAMANIPULATOR_H

#include <QVector>

/**
 * @brief AmodeDataManipulator is just a collection of function that will be used for manipulating A-mode data vector.
 */
class AmodeDataManipulator
{
public:

    /**
     * @brief A function that will return the full one row
     */
    static QVector<int16_t> getRow(const QVector<int16_t>& input, int rowNumber, int totalColumns);

    /**
     * @brief A function for downsampling the amode data vector
     */
    static QVector<int16_t> downsampleVector(const QVector<int16_t>& input, int targetSize);
};

#endif // AMODEDATAMANIPULATOR_H
