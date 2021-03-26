//
// Created by Oğuz Kerem Yıldız on 25.03.2021.
//

#ifndef SENTIMENTANALYSIS_SENTENCEAUTOSENTIMENT_H
#define SENTIMENTANALYSIS_SENTENCEAUTOSENTIMENT_H
#include "SentiNet.h"
#include "AnnotatedSentence.h"

using namespace std;

class SentenceAutoSentiment {
private:
    static PolarityType findPolarityType(double sum);
protected:
    SentiNet* sentiNet{};
virtual PolarityType getPolarity(PolarityType polarityType, AnnotatedSentence* sentence, int index) = 0;
public:
    SentenceAutoSentiment();
    explicit SentenceAutoSentiment(SentiNet *_sentiNet);
    PolarityType autoSentiment(AnnotatedSentence* sentence);
};

#endif //SENTIMENTANALYSIS_SENTENCEAUTOSENTIMENT_H
