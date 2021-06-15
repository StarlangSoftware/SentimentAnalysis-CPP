//
// Created by Oğuz Kerem Yıldız on 26.03.2021.
//

#include "TurkishSentenceBasicAutoSentiment.h"

TurkishSentenceBasicAutoSentiment::TurkishSentenceBasicAutoSentiment(SentiNet *sentiNet) : SentenceAutoSentiment(sentiNet) {}

PolarityType TurkishSentenceBasicAutoSentiment::findPolarityType(double sum) {
    if (sum > 0.0) {
        return PolarityType::POSITIVE;
    } else if (sum < 0.0) {
        return PolarityType::NEGATIVE;
    }
    return PolarityType::NEUTRAL;
}

PolarityType TurkishSentenceBasicAutoSentiment::getPolarity(PolarityType polarityType, AnnotatedSentence *sentence, int index) {
    if (((AnnotatedWord*)(sentence->getWord(index)))->getParse()->containsTag(MorphologicalTag::NEGATIVE)) {
        if (polarityType == PolarityType::POSITIVE) {
            polarityType = PolarityType::NEGATIVE;
        } else if (polarityType == PolarityType::NEGATIVE) {
            polarityType = PolarityType::POSITIVE;
        }
    }
    if (index + 1 < sentence->wordCount()) {
        auto* nextWord = (AnnotatedWord*) (sentence->getWord(index + 1));
        string name = nextWord->getParse()->getWord()->getName();
        if (Word::toLowerCase(name) == "değil") {
            if (polarityType == PolarityType::POSITIVE) {
                return PolarityType::NEGATIVE;
            } else if (polarityType == PolarityType::NEGATIVE) {
                return PolarityType::POSITIVE;
            }
        }
    }
    return polarityType;
}

PolarityType TurkishSentenceBasicAutoSentiment::autoSentiment(AnnotatedSentence *sentence) {
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
