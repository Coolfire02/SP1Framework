#include "ProgressBar.h"

ProgressBar::ProgressBar(BAR barType, short width, short height, WORD border, WORD fill) : barType(barType), borderColour(border), fillColour(fill), progress(0.0)
{
    if (height < 3) height = 3;
    if (width < 3) width = 3;
    weight = 10000;
}

ProgressBar::ProgressBar(BAR barType, short width, short height) : barType(barType), borderColour(0x30), fillColour(0xF0), progress(0.0)
{
    if (height < 3) height = 3;
    if (width < 3) width = 3;
    weight = 10000;
    (*this).updateBar();
}

void ProgressBar::updateBar() {
    art.setArt(barType, width, height, borderColour, fillColour, progress);
}

ProgressBar::~ProgressBar()
{
    // intentionally left blank
}

std::string ProgressBar::getType() {
    return "ProgressBar";
}