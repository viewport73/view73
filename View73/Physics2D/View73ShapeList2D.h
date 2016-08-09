#ifndef __View73ShapeList2D_h__
#define __View73ShapeList2D_h__

#include <loki/Typelist.h>
#include "View73BoxShape2D.h"
#include "View73CircleShape2D.h"

typedef Loki::TL::MakeTypelist<BoxShape2D,CircleShape2D>::Result TShapeTypes;

#endif