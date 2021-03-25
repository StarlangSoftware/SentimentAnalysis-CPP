//
// Created by Oğuz Kerem Yıldız on 25.03.2021.
//

#ifndef SENTIMENTANALYSIS_SENTENCEAUTOSENTIMENT_H
#define SENTIMENTANALYSIS_SENTENCEAUTOSENTIMENT_H
#include <utility>
#include "Sentence.h"
#include "SentiNet.h"
#include "AnnotatedSentence.h"

using namespace std;

class SentenceAutoSentiment {
private:
    static PolarityType findPolarityType(double sum) {
        if (sum > 0.0) {
            return PolarityType::POSITIVE;
        } else if (sum < 0.0) {
            return PolarityType::NEGATIVE;
        }
        return PolarityType::NEUTRAL;
    }
protected:
    SentiNet* sentiNet{};
virtual PolarityType getPolarity(PolarityType polarityType, AnnotatedSentence* sentence, int index) = 0;
public:
    SentenceAutoSentiment() = default;
    explicit SentenceAutoSentiment(SentiNet *_sentiNet) {
        this->sentiNet = _sentiNet;
    }
    PolarityType autoSentiment(AnnotatedSentence* sentence) {
        double polarityValue = 0.0;
        for (int i = 0; i < sentence->wordCount(); i++) {
            auto* word = dynamic_cast<AnnotatedWord*>(sentence->getWord(i));
            SentiSynSet* sentiSynSet = sentiNet->getSentiSynSet(word->getSemantic());
            if (sentiSynSet != nullptr) {
                double value = max(sentiSynSet->getNegativeScore(), sentiSynSet->getPositiveScore());
                switch (getPolarity(sentiSynSet->getPolarity(), sentence, i)) {
                    case PolarityType::POSITIVE:
                        polarityValue += value;
                        break;
                    case PolarityType::NEGATIVE:
                        polarityValue -= value;
                        break;
                    default:
                        break;
                }
            }
        }
        return findPolarityType(polarityValue);
    }
};

#endif //SENTIMENTANALYSIS_SENTENCEAUTOSENTIMENT_H
