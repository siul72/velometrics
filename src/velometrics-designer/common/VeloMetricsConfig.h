#pragma once

#include <QColor>

struct VelometricsConfiguration
{
     // Canvas
     int canvasWidth = 3840;
     int canvasHeight = 2160;

     // Grid
     bool showGrid = true;
     bool snapToGrid = true;
     int gridSize = 50;

     // Selection
     QColor selectionColor = Qt::cyan;
     int selectionWidth = 2;

     // Resize handles
     int resizeHandleSize = 20;

     // Defaults
     int defaultWidgetWidth = 600;
     int defaultWidgetHeight = 300;
};

class VelometricsSettings{

    public:
        static VelometricsConfiguration& instance(){
            static VelometricsConfiguration config;
            return config;
         }
      };

static qreal snapToGrid(qreal value)
{
     const auto& cfg = VelometricsSettings::instance();

     return std::round(value / cfg.gridSize)
            * cfg.gridSize;
}


