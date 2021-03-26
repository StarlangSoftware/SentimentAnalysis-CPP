//
// Created by Oğuz Kerem Yıldız on 26.03.2021.
//

#include "TurkishSentenceAutoSentiment.h"

TurkishSentenceAutoSentiment::TurkishSentenceAutoSentiment(SentiNet *sentiNet) : SentenceAutoSentiment(sentiNet) {}

string TurkishSentenceAutoSentiment::transform(const string &name) {
    string str;
    for (char i : name) {
        str += (char) tolower(i);
    }
    return str;
}

PolarityType TurkishSentenceAutoSentiment::getPolarity(PolarityType polarityType, AnnotatedSentence *sentence, int index) {
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
