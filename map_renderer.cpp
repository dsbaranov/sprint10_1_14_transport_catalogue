#include "map_renderer.h"

/*
 * В этом файле вы можете разместить код, отвечающий за визуализацию карты
 * маршрутов в формате SVG. Визуализация маршртутов вам понадобится во второй
 * части итогового проекта. Пока можете оставить файл пустым.
 */
bool IsZero(double value)
{
    return std::abs(value) < EPSILON;
}

void MapRenderer::SetProps(const RendererProperties &props)
{
    props_ = props;
}