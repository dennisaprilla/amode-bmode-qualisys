#include "qcustomplotintervalwindow.h"
#include <QDebug>

QCustomPlotIntervalWindow::QCustomPlotIntervalWindow(QWidget *parent) : QCustomPlot(parent), shadeRect(nullptr), elementsVisible(false)
{
    // Set up the plot (example)
    addGraph();
    xAxis->setRange(-1, 1);
    yAxis->setRange(0, 1);

    // Connect the mouse press event to our custom slot
    connect(this, &QCustomPlot::mousePress, this, &QCustomPlotIntervalWindow::onMousePress);

    // Create the vertical lines
    for (int i = 0; i < 3; ++i) {
        verticalLines[i] = new QCPItemLine(this);
        verticalLines[i]->setPen(QPen(i == 1 ? Qt::red : Qt::blue, 2, Qt::DashLine));
        verticalLines[i]->start->setCoords(0, yAxis->range().lower);
        verticalLines[i]->end->setCoords(0, yAxis->range().upper);
        verticalLines[i]->setVisible(false);
    }

    // Create the shaded rectangle
    shadeRect = new QCPItemRect(this);
    shadeRect->setPen(Qt::NoPen);
    shadeRect->setBrush(QBrush(QColor(0, 0, 255, 50)));
    shadeRect->setVisible(false);
}

void QCustomPlotIntervalWindow::setShadeColor(const QColor& color)
{
    shadeRect->setBrush(QBrush(color));
}

void QCustomPlotIntervalWindow::setInitialSpacing(double spacing)
{
    lineSpacing = spacing;
}

void QCustomPlotIntervalWindow::onMousePress(QMouseEvent *event)
{
    double x = event->pos().x();
    double xValue = xAxis->pixelToCoord(x);

    if (event->button() == Qt::LeftButton) {
        centerX = xValue;
        updateLines(centerX);
        elementsVisible = true;
    } else if (event->button() == Qt::RightButton && elementsVisible) {
        lineSpacing = std::abs(xValue - centerX);
        updateLines(centerX);
    } else if (event->button() == Qt::MiddleButton) {
        clearAllElements();
        elementsVisible = false;
    }

    if (elementsVisible) {
        updateShading();
        updateLabels();
    }
    replot();
}

void QCustomPlotIntervalWindow::updateLines(double centerX)
{
    verticalLines[1]->start->setCoords(centerX, yAxis->range().lower);
    verticalLines[1]->end->setCoords(centerX, yAxis->range().upper);

    verticalLines[0]->start->setCoords(centerX - lineSpacing, yAxis->range().lower);
    verticalLines[0]->end->setCoords(centerX - lineSpacing, yAxis->range().upper);

    verticalLines[2]->start->setCoords(centerX + lineSpacing, yAxis->range().lower);
    verticalLines[2]->end->setCoords(centerX + lineSpacing, yAxis->range().upper);

    for (auto& line : verticalLines) {
        line->setVisible(true);
    }
}

void QCustomPlotIntervalWindow::updateShading()
{
    shadeRect->topLeft->setCoords(centerX - lineSpacing, yAxis->range().upper);
    shadeRect->bottomRight->setCoords(centerX + lineSpacing, yAxis->range().lower);
    shadeRect->setVisible(true);
}

void QCustomPlotIntervalWindow::updateLabels()
{
    for (auto& label : xValueLabels) {
        if (!label.isNull()) {
            removeItem(label);
        }
    }

    for (int i = 0; i < 3; ++i) {
        double x = centerX + (i - 1) * lineSpacing;
        xValueLabels[i] = new QCPItemText(this);
        xValueLabels[i]->position->setType(QCPItemPosition::ptAxisRectRatio);
        xValueLabels[i]->position->setCoords(0.95, 0.05 + 0.05 * i);
        xValueLabels[i]->setText(QString("x%1 = %2").arg(i).arg(QString::number(x, 'f', 2)));
        xValueLabels[i]->setFont(QFont(font().family(), 10));
        // xValueLabels[i]->setPadding(QMargins(1, 0, 1, 0));
    }
}

void QCustomPlotIntervalWindow::clearAllElements()
{
    for (auto& line : verticalLines) {
        line->setVisible(false);
    }
    shadeRect->setVisible(false);
    for (auto& label : xValueLabels) {
        if (!label.isNull()) {
            removeItem(label);
        }
    }
}

std::array<std::optional<double>, 3> QCustomPlotIntervalWindow::getLinePositions() const
{
    std::array<std::optional<double>, 3> positions;

    if (!elementsVisible) {
        qDebug() << "Warning: Lines are not visible. Returning current stored positions.";
    }

    double xMin = xAxis->range().lower;
    double xMax = xAxis->range().upper;

    std::array<double, 3> rawPositions = {centerX - lineSpacing, centerX, centerX + lineSpacing};

    for (size_t i = 0; i < 3; ++i) {
        if (rawPositions[i] >= xMin && rawPositions[i] <= xMax) {
            positions[i] = rawPositions[i];
        } else {
            positions[i] = std::nullopt;
            qDebug() << "Warning: Line" << i << "is outside the plot range.";
        }
    }

    return positions;
}
