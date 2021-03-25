//
// Created by Olcay Taner YILDIZ on 2019-08-25.
//

#ifndef SENTINET_SENTINET_H
#define SENTINET_SENTINET_H

#include <map>
#include "SentiSynSet.h"

using namespace std;

class SentiNet {
private:
    map<string, SentiSynSet*> sentiSynSetList;
    void loadSentiNet(string fileName);
public:
    SentiNet();
    ~SentiNet();
    explicit SentiNet(string fileName);
    SentiSynSet* getSentiSynSet(string id);
    vector<string> getPolarity(PolarityType polarityType);
    vector<string> getPositives();
    vector<string> getNegatives();
    vector<string> getNeutrals();
    void removeSynSet(SentiSynSet s);
    void saveAsXml(string fileName);
};


#endif //SENTINET_SENTINET_H
