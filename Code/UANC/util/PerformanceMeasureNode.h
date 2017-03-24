/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * PerformanceMeasureNode.h
 *
 *  Created on: 12.12.2016
 *      Author: vladimir
 */

#ifndef CODE_UANC_ALGORITHM_PERFORMANCEMEASURENODE_H_
#define CODE_UANC_ALGORITHM_PERFORMANCEMEASURENODE_H_

#include <list>
#include <string>
#include <chrono>
#include <memory>
#include <vector>

namespace uanc {
    namespace util {

        enum class RunningState {
            running = true,
            stopped = false
        };

        template<typename durationType = std::chrono::microseconds>
        class PerformanceMeasureNode {
        public:
            /** \brief Simply return the time state.
            *
             * return a timer state
            */
            RunningState getTimerState() const {
                return timerState;
            }

            /** \brief Constructor basically saves the passed measurement titel.
            *
            * @param measurementTitle a String with the measurement titel
            */
            PerformanceMeasureNode(std::string measurementTitle)
                    : measureTitle(measurementTitle),
                      timerState(RunningState::stopped) {

            }
            /** \brief The default constructor.
            *
            */
            PerformanceMeasureNode()
                    : measureTitle(""),
                      timerState(RunningState::stopped) {

            }

            /** \brief Start the Measurement.
            *
            */
            void start() {
                //If the state is already running, then do nothing, only parallel subMeasure allowed!
                if (timerState == RunningState::running) {
                    return;
                }
                startTime = std::chrono::high_resolution_clock::now();
                timerState = RunningState::running;
            }

            /** \brief Stop the Measurement.
            *
            */
            void stop() {
                //Calculate the passed time
                std::chrono::high_resolution_clock::time_point endTime =
                        std::chrono::high_resolution_clock::now();
                nodeDuration = std::chrono::duration_cast<durationType>(
                        endTime - startTime);
                timerState = RunningState::stopped;

            }
            /** \brief Simply returns the node duration.
            *
            * @return a node duration
            */
            durationType getNodeDuration() const {
                return nodeDuration;
            }

            // hold title of the measurement
            std::string measureTitle;
            // a subsequenz of the measurement
            std::shared_ptr<PerformanceMeasureNode<durationType>> subsequentMeasure;
            // vector of submeasurement
            std::vector<std::shared_ptr<PerformanceMeasureNode<durationType>>> measureSubMeasureChild;
            // parent of the measurement
            std::shared_ptr<PerformanceMeasureNode<durationType>> measureParent;
            // previous measurement
            std::shared_ptr<PerformanceMeasureNode<durationType>> previousMeasure;

        private:
            durationType nodeDuration;
            RunningState timerState;
            std::chrono::high_resolution_clock::time_point startTime;
        };

    }
}

#endif /* CODE_UANC_ALGORITHM_PERFORMANCEMEASURENODE_H_ */
