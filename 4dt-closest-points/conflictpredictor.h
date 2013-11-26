#pragma once

struct ConflictPredictor
{
    virtual std::vector< std::pair<double, double> > getConflict(size_t index1, size_t index2, double d) = 0;
};

