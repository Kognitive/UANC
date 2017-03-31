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

#ifndef UANC_PERFORMANCEMEASURE_H
#define UANC_PERFORMANCEMEASURE_H

#include <list>
#include <string>
#include <chrono>
#include <memory>
#include "PerformanceMeasureNode.h"

namespace uanc {
    namespace util {

/**
 * Class for the performance measure of algorithms.
 *
 * It creates a 2 - dimensional tree, where subsequent measurements are stored in the horizontal and
 * sub-measures are stored in the vertical dimension. A measure main contain multiple sub-measure layers.
 *
 * <pre>
 *  startSubMeasure().----.    start()         .----.
 *     .-------------| M1 |------------------->| M2 |
 *     |             '----'                    '----'
 *     |               ^                       |   ^
 *     |               |                       |   |
 *     |               | stopSubMeasure()      |   |
 *     |               '------------------.    '---'
 *     v                                  |    stop()
 *  .----.       .----.                .----.
 *  | S1 |------>| S2 |--------------->| S3 |
 *  '----'       '----'                '----'
 *        start()          start()
 * </pre>
 */
        template<typename durationType = std::chrono::microseconds>
        class PerformanceMeasure {
        public:

            /**
             * Returns a pointer to the root measurement node.
             * @return The pointer to the root measurement node
             */
            const std::shared_ptr<PerformanceMeasureNode<durationType> > getRootMeasure() const {
                auto tmpMeasure = currentMeasure;
                if (!currentMeasure) {
                    return NULL;
                }

                while (tmpMeasure->measureParent) {
                    while (tmpMeasure->measureParent) {
                        tmpMeasure = tmpMeasure->measureParent;
                    }
                    tmpMeasure = tmpMeasure->measureParent;
                }
                return tmpMeasure;
            }

            /**
             * Starts a new measurement or sub-measurement. A new node is created, w
             */
            void start(std::string title) {
                auto tempNode = std::shared_ptr<PerformanceMeasureNode<durationType>>(
                        new PerformanceMeasureNode<durationType>(title));
                //check, if the node is the root node of the measurement tree
                if (!currentMeasure) {
                    currentMeasure = tempNode;
                }
                    //Add the measurement Node as the subsequent node of the current node
                else {
                    stop();
                    //All subsequent measurements have the same parent, but may have different children
                    currentMeasure->subsequentMeasure = tempNode;
                    tempNode->previousMeasure = currentMeasure;
                    tempNode->measureParent = currentMeasure->measureParent;
                    currentMeasure = tempNode;
                }
                currentMeasure->start();
            }

            /**
             * Restarts the current measurement without creating a new measurement node.
             */
            void restart() {
                if (currentMeasure) {
                    currentMeasure->stop();
                    currentMeasure->start();
                }
            }

            /**
             * Stops the current measurement and saves its time
             */
            void stop() {
                currentMeasure->stop();
            }

            /**
             * Starts a new sub-measure layer with a measure with the given title.
             * The sub-measure is started immediately.
             * @param subMeasureTitle The title of the sub-measurement.
             */
            void startSubMeasure(std::string subMeasureTitle = "") {
                //If no measure has beeen started yet, the start of a submeasure is not allowed
                if (!currentMeasure) {
                    return;
                }
                auto tempNode = std::shared_ptr<PerformanceMeasureNode<durationType>>(
                        new PerformanceMeasureNode<durationType>(subMeasureTitle));
                tempNode->measureParent = currentMeasure;
                currentMeasure->measureSubMeasureChild.push_back(tempNode);
                currentMeasure = tempNode;
                currentMeasure->start();
            }

            /**
             * Stops the current measurement, if running, and returns to its parent.
             * The parents state is not changed
             * If no parent measurement exists, then nothing is done.
             */
            void stopSubMeasure() {
                //If no root parent node or no node at all exists, no sub-measures can be stopped
                if (!currentMeasure) {
                    return;
                }
                if (!currentMeasure->measureParent) {
                    return;
                }
                //If any measurement is running in the current node, it is stopped
                stop();
                //Go one level up
                currentMeasure = currentMeasure->measureParent;

            }

            /**
             * Stops all running measurements and returns to the root measurement.
             */
            void stopAllMeasurements() {
                if (!currentMeasure) {
                    return;
                }
                //If the current measurement is already the root measurement
                while (currentMeasure->measureParent) {
                    stop();
                    currentMeasure = currentMeasure->measureParent;
                }
                stop();
            }

        private:
            std::shared_ptr<PerformanceMeasureNode<durationType>> currentMeasure;
        };

    }
}

#endif //UANC_PERFORMANCEMEASURE_H
