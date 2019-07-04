#include "ExtensionManager.h"

ColorFloat ExtensionManager::convRGBA8ToFloat(ColorRGBA8 t_color)
{
	ColorFloat color(
		(float)t_color.r / 255, 
		(float)t_color.g / 255,
		(float)t_color.b / 255,
		(float)t_color.a / 255);

	return color;
}
