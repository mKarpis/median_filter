#ifndef MEDIANHOLDER
#define MEDIANHOLDER

#include <set>

class MedianHolder{

public:
    float const& getMedian() const {return *iter_;}
    void insert(const float &t);

    void clear();

private:
    std::set<float> elements_;
    std::set<float>::const_iterator iter_;
};

#endif // MEDIANHOLDER

