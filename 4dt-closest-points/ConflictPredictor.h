#ifndef CONFLICTPREDICTOR_H
#define CONFLICTPREDICTOR_H

struct ConflictPredictor {
    std::vector< std::pair<double, double> > getConflict(size_t index1, size_t index2, double d) = 0;
};

#endif // CONFLICTPREDICTOR_H
