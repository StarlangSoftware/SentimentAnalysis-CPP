//
// Created by Oğuz Kerem Yıldız on 26.03.2021.
//

#include "SentenceAutoSentiment.h"

SentenceAutoSentiment::SentenceAutoSentiment() = default;

SentenceAutoSentiment::SentenceAutoSentiment(SentiNet *_sentiNet) {
    this->sentiNet = _sentiNet;
}
