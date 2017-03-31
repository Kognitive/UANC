/* Simplified ANC Model, only targets inversion, but can be extended. University project.
 *  Copyright (C) 2017 Danielle Ceballos, Janne Wulf, Markus Semmler, Roman Rempel, Vladimir Roskin.

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <thread>
#include <Code/UANC/amv/anc/ANCAlgorithmRegister.h>
#include <cstring>
#include <fstream>
#include <Code/UANC/util/SignalFileActor.h>

#include <math.h>
#include "EpsilonTests.h"

using namespace uanc::amv::anc;


EpsilonTests::EpsilonTests() {
    // Constructor
}

void EpsilonTests::run(std::string path) {

    QString _Path = QString::fromStdString(path);

    //your filenames will be stored here
    std::vector<QString> signalsVec;
    QDir dir(_Path);
    dir.setNameFilters(QStringList() << "*.wav");
    auto signalList = dir.entryList();

    if (signalList.size() == 0) {
        std::cout << "There are no *.wav files in " << path << std::endl;
        return;
    }

    // Iterate over all signals and algorithm
    std::shared_ptr<std::vector<uanc::amv::IAlgorithm *>> algorithmList = ANCAlgorithmRegister::getAlgorithms();
    for (QList<QString>::iterator signalString = signalList.begin(); signalString != signalList.end(); ++signalString) {
        uanc::util::SignalFileActor fileActor((_Path.toStdString() + signalString->toStdString()));
        auto signal = fileActor.loadData();
        // name of the file
        std::cout << "File: " << signalString->toStdString() <<  std::endl;
        for (unsigned int algoIt = 0; algoIt < algorithmList->size(); ++algoIt) {
            auto algo = algorithmList->at(algoIt)->clone();

            try {
                algo->process(signal);

                auto castedAlgorithm = (uanc::amv::anc::algorithm::ANCAlgorithm<uanc::amv::anc::model::ANCModel> *) algo;
                auto resultModel = castedAlgorithm->getModel();
                auto out = resultModel;
                auto errorSignal = std::shared_ptr<Aquila::SignalSource>(
                    new Aquila::SignalSource(*out->inverted->left_channel.get() +
                        *signal->left_channel.get()));
                size_t length = errorSignal->length();
                auto sample = errorSignal->Aquila::SignalSource::toArray();

                // get average error
                double errorSum = 0;
                double b = 0;
                double mi = abs(sample[0]);
                double ma = abs(sample[0]);
                for (size_t i = 0; i < length; ++i) {
                    errorSum = errorSum + abs(sample[i]);
                    b = b + (abs(sample[i]) * abs(sample[i]));
                    mi = std::min(mi, abs(sample[i]));
                    ma = std::max(ma, abs(sample[i]));
                }

                double avgMy = errorSum / length;
                double avgError = b / length;
                double deviation = sqrt(avgError - avgMy * avgMy);

                QString algoString = QString::fromStdString(algorithmList->at(algoIt)->getName());
                QString fileString = QString::fromStdString(signalString->toStdString());
                std::cout << "\t Algorithm: " << algoString.toStdString() <<
                          " --> Where estimated gaussian of the error is N(" + std::to_string(avgMy) << "," << std::to_string(deviation) << ")" << std::endl;
            }
            catch (...) {
                QString algoString = QString::fromStdString(algorithmList->at(algoIt)->getName());
                std::cout << "Algorithm: " << algoString.toStdString() << " --> FAILED DURING EXECUTION" << std::endl;
            }
        }
    }
}
