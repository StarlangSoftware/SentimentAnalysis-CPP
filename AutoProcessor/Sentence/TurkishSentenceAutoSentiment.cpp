//
// Created by Oğuz Kerem Yıldız on 26.03.2021.
//

#include "TurkishSentenceAutoSentiment.h"

TurkishSentenceAutoSentiment::TurkishSentenceAutoSentiment(SentiNet *sentiNet) : SentenceAutoSentiment(sentiNet) {}

PolarityType TurkishSentenceAutoSentiment::getPolarity(PolarityType polarityType, AnnotatedSentence *sentence, int index) {
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
