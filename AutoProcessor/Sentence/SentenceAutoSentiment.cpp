//
// Created by Oğuz Kerem Yıldız on 26.03.2021.
//

#include "SentenceAutoSentiment.h"

SentenceAutoSentiment::SentenceAutoSentiment() = default;

SentenceAutoSentiment::SentenceAutoSentiment(SentiNet *_sentiNet) {
    this->sentiNet = _sentiNet;
}

PolarityType SentenceAutoSentiment::findPolarityType(double sum) {
    if (sum > 0.0) {
        return PolarityType::POSITIVE;
    } else if (sum < 0.0) {
        return PolarityType::NEGATIVE;
    }
    return PolarityType::NEUTRAL;
}

PolarityType SentenceAutoSentiment::autoSentiment(AnnotatedSentence *sentence) {
    double polarityValue = 0.0;
    for (int i = 0; i < sentence->wordCount(); i++) {
        auto* word = (AnnotatedWord*) sentence->getWord(i);
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
