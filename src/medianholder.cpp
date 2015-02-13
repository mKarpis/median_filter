#include "medianholder.h"

void MedianHolder::insert(const float &t)
{
    if (elements_.empty()) {
        iter_ = elements_.insert(t).first;
        return;
    }

    bool smaller = (t < getMedian()) ? true:false;
    bool odd = (elements_.size() % 2) == 1;

    if (!elements_.insert(t).second)
        return;

    if (odd && smaller) --iter_;
    else if (!odd && !smaller) ++iter_;
}

void MedianHolder::clear()
{
    elements_.clear();
    iter_ = elements_.begin();
}
