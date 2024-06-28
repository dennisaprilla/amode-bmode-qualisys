#include "amodedatamanipulator.h"

QVector<int16_t> AmodeDataManipulator::getRow(const QVector<int16_t>& input, int rowNumber, int totalColumns) {
    int startIndex = rowNumber * totalColumns;
    return input.mid(startIndex, totalColumns);
}

QVector<int16_t> AmodeDataManipulator::downsampleVector(const QVector<int16_t>& input, int targetSize) {
    QVector<int16_t> output;
    output.reserve(targetSize);

    // Calculate the step size based on the ratio of the target size to the input size
    int step = input.size() / targetSize;

    // Use std::transform with a stride to downsample without explicit looping
    std::transform(input.begin(), input.end(), std::back_inserter(output),
                   [step, n = 0] (int16_t value) mutable {
                       return n++ % step == 0 ? value : 0;
                   });

    // Remove the '0' elements which are placeholders for non-sampled elements
    output.erase(std::remove(output.begin(), output.end(), 0), output.end());

    return output;
}
