#include "ProgressBar.h"

ProgressBar::ProgressBar(BAR barType, short width, short height, WORD border, WORD fill, int MaxAmt) : barType(barType), borderColour(border), fillColour(fill), progress(0.0)
{
    if (height < 3) height = 3;
    if (width < 3) width = 3;
    (*this).height = height;
    (*this).width = width;
    weight = 10000;
    max = MaxAmt;
    (*this).updateBar(MaxAmt);
}

ProgressBar::ProgressBar(BAR barType, short width, short height, WORD border, WORD fill) : barType(barType), borderColour(border), fillColour(fill), progress(0.0)
{
    max = 100;
    if (height < 3) height = 3;
    if (width < 3) width = 3;
    (*this).height = height;
    (*this).width = width;
    weight = 10000;
    (*this).updateBar();
}

ProgressBar::ProgressBar(BAR barType, short width, short height, int MaxAmt) : barType(barType), borderColour(0x30), fillColour(0xF0), progress(0.0)
{
    if (height < 3) height = 3;
    if (width < 3) width = 3;
    (*this).height = height;
    (*this).width = width;
    weight = 10000;
    max = MaxAmt;
    (*this).updateBar(MaxAmt);

}

ProgressBar::ProgressBar(BAR barType, short width, short height) : barType(barType), borderColour(0x30), fillColour(0xF0), progress(0.0)
{
    max = 100;
    if (height < 3) height = 3;
    if (width < 3) width = 3;
    (*this).height = height;
    (*this).width = width;
    weight = 10000;
    (*this).updateBar();
}

void ProgressBar::updateBar() {
    art.setArt(barType, width, height, borderColour, fillColour, progress);
}

void ProgressBar::updateBar(int MaxAmt)
{
    art.setArt(barType, width, height, borderColour, fillColour, progress, MaxAmt);

}

void ProgressBar::setProgress(double prog) {
    if (prog < 0) prog = 0;
    else if (prog > 100) prog = 100;
    else progress = prog;
    (*this).updateBar();
}

ProgressBar::~ProgressBar()
{
    // intentionally left blank
}

int ProgressBar::getMax()
{
    return max;
}

std::string ProgressBar::getType() {
    return "ProgressBar";
}