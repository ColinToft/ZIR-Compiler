#ifndef __ANALYSIS_H
#define __ANALYSIS_H

enum AnalysisID { SYMBOL_TABLE = 0 };

class Analysis {
  public:
    virtual ~Analysis() {}
};

#endif // __ANALYSIS_H
