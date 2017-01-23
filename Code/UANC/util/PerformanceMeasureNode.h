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

namespace uanc {
namespace util {

enum class RunningState {
  running = true,
  stopped = false
};

template<typename durationType = std::chrono::microseconds>
class PerformanceMeasureNode {
 public:

  RunningState getTimerState() const {
    return timerState;
  }

  PerformanceMeasureNode(std::string measurementTitle)
      : measureTitle(measurementTitle),
        timerState(RunningState::stopped) {

  }

  PerformanceMeasureNode()
      : measureTitle(""),
        timerState(RunningState::stopped) {

  }

  void start() {
    //If the state is already running, then do nothing, only parallel subMeasure allowed!
    if (timerState == RunningState::running) {
      return;
    }
    startTime = std::chrono::high_resolution_clock::now();
    timerState = RunningState::running;
  }

  void stop() {
    //Calculate the passed time
    std::chrono::high_resolution_clock::time_point endTime =
        std::chrono::high_resolution_clock::now();
    nodeDuration = std::chrono::duration_cast<durationType>(
        endTime - startTime);
    timerState = RunningState::stopped;

  }

  durationType getNodeDuration() const {
    return nodeDuration;
  }

  std::string measureTitle;
  std::shared_ptr<PerformanceMeasureNode<durationType>> subsequentMeasure;
  std::shared_ptr<PerformanceMeasureNode<durationType>> measureSubMeasureChild;
  std::shared_ptr<PerformanceMeasureNode<durationType>> measureParent;
  std::shared_ptr<PerformanceMeasureNode<durationType>> previousMeasure;

 private:
  durationType nodeDuration;
  RunningState timerState;
  std::chrono::high_resolution_clock::time_point startTime;
};

}
}

#endif /* CODE_UANC_ALGORITHM_PERFORMANCEMEASURENODE_H_ */
