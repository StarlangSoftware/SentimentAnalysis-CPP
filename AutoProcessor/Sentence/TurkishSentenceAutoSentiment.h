//
// Created by Oğuz Kerem Yıldız on 25.03.2021.
//

#ifndef SENTIMENTANALYSIS_TURKISHSENTENCEAUTOSENTIMENT_H
#define SENTIMENTANALYSIS_TURKISHSENTENCEAUTOSENTIMENT_H
#include "SentenceAutoSentiment.h"

using namespace std;

class TurkishSentenceAutoSentiment : public SentenceAutoSentiment {
private:
    static string transform(const string& name);
protected:
    PolarityType getPolarity(PolarityType polarityType, AnnotatedSentence* sentence, int index) override;
public:
    explicit TurkishSentenceAutoSentiment(SentiNet *sentiNet);
};

#endif //SENTIMENTANALYSIS_TURKISHSENTENCEAUTOSENTIMENT_H
