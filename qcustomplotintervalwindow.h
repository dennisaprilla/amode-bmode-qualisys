#ifndef QCUSTOMPLOTINTERVALWINDOW_H
#define QCUSTOMPLOTINTERVALWINDOW_H

#include "qcustomplot.h"
#include <array>

class QCustomPlotIntervalWindow : public QCustomPlot
{
    Q_OBJECT

public:
    explicit QCustomPlotIntervalWindow(QWidget *parent = nullptr);
    // explicit QCustomPlotIntervalWindow(QWidget *parent = nullptr, std::array<std::optional<double>, 3> window = {std::nullopt, std::nullopt, std::nullopt});

    void setShadeColor(const QColor& color);
    void setInitialSpacing(double spacing);
    std::array<std::optional<double>, 3> getLinePositions() const;

private slots:
    void onMousePress(QMouseEvent *event);

private:
    void updateLines(double centerX);
    void updateLabels();
    void updateShading();
    void clearAllElements();

    std::array<QCPItemLine*, 3> verticalLines;
    std::array<QPointer<QCPItemText>, 3> xValueLabels;
    QCPItemRect *shadeRect;
    double lineSpacing = 0.1;
    double centerX = 0;
    bool elementsVisible = false;
};

#endif // QCUSTOMPLOTINTERVALWINDOW_H
