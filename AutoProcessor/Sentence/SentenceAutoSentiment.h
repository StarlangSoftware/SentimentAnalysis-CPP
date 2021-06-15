//
// Created by Oğuz Kerem Yıldız on 25.03.2021.
//

#ifndef SENTIMENTANALYSIS_SENTENCEAUTOSENTIMENT_H
#define SENTIMENTANALYSIS_SENTENCEAUTOSENTIMENT_H
#include "SentiNet.h"
#include "AnnotatedSentence.h"

using namespace std;

class SentenceAutoSentiment {
protected:
    SentiNet* sentiNet{};
public:
    SentenceAutoSentiment();
    explicit SentenceAutoSentiment(SentiNet *_sentiNet);
    virtual PolarityType autoSentiment(AnnotatedSentence* sentence) = 0;
};

#endif //SENTIMENTANALYSIS_SENTENCEAUTOSENTIMENT_H
