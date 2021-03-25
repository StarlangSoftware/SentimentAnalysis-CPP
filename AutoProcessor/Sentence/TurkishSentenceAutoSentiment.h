//
// Created by Oğuz Kerem Yıldız on 25.03.2021.
//

#ifndef SENTIMENTANALYSIS_TURKISHSENTENCEAUTOSENTIMENT_H
#define SENTIMENTANALYSIS_TURKISHSENTENCEAUTOSENTIMENT_H
#include "SentenceAutoSentiment.h"
#include <utility>
#include <algorithm>
#include <cctype>
#include <string>
#include <MorphologicalTag.h>

using namespace std;

class TurkishSentenceAutoSentiment : public SentenceAutoSentiment {
private:
    static string transform(const string& name) {
        string str;
        for (char i : name) {
            str += (char) tolower(i);
        }
        return str;
    }
protected:
    PolarityType getPolarity(PolarityType polarityType, AnnotatedSentence* sentence, int index) override {
        if (dynamic_cast<AnnotatedWord*>(sentence->getWord(index))->getParse()->containsTag(MorphologicalTag::NEGATIVE)) {
            if (polarityType == PolarityType::POSITIVE) {
                polarityType = PolarityType::NEGATIVE;
            } else if (polarityType == PolarityType::NEGATIVE) {
                polarityType = PolarityType::POSITIVE;
            }
        }
        if (index + 1 < sentence->wordCount()) {
            auto* nextWord = dynamic_cast<AnnotatedWord*>(sentence->getWord(index + 1));
            string name = nextWord->getParse()->getWord()->getName();
            if (transform(name) == "değil") {
                if (polarityType == PolarityType::POSITIVE) {
                    return PolarityType::NEGATIVE;
                } else if (polarityType == PolarityType::NEGATIVE) {
                    return PolarityType::POSITIVE;
                }
            }
        }
        return polarityType;
    }
public:
    explicit TurkishSentenceAutoSentiment(SentiNet *sentiNet) : SentenceAutoSentiment(sentiNet) {}
};

#endif //SENTIMENTANALYSIS_TURKISHSENTENCEAUTOSENTIMENT_H
