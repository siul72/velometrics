//
// Created by jenkins on 8/23/26.
//

#ifndef VELOMETRICS_CANVASITEM_H_H
#define VELOMETRICS_CANVASITEM_H_H
#include <qrect.h>

enum class ElementType;

struct CanvasItem
{
    ElementType type;
    QRect rect;
};

#endif //VELOMETRICS_CANVASITEM_H_H
