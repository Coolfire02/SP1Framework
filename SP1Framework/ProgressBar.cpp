#include "ProgressBar.h"

ProgressBar::ProgressBar()
{
    weight = 10000;
}

ProgressBar::~ProgressBar()
{
}

std::string ProgressBar::getType() {
    return "ProgressBar";
}