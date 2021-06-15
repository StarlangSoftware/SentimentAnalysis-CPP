//
// Created by Oğuz Kerem Yıldız on 25.03.2021.
//

#ifndef SENTIMENTANALYSIS_TURKISHSENTENCEBASICAUTOSENTIMENT_H
#define SENTIMENTANALYSIS_TURKISHSENTENCEBASICAUTOSENTIMENT_H
#include "SentenceAutoSentiment.h"

using namespace std;

class TurkishSentenceBasicAutoSentiment : public SentenceAutoSentiment {
private:
    static PolarityType findPolarityType(double sum);
    static PolarityType getPolarity(PolarityType polarityType, AnnotatedSentence *sentence, int index);
public:
    explicit TurkishSentenceBasicAutoSentiment(SentiNet *sentiNet);
    PolarityType autoSentiment(AnnotatedSentence* sentence) override;
};

#endif //SENTIMENTANALYSIS_TURKISHSENTENCEBASICAUTOSENTIMENT_H
