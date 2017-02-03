/*
 * performanceMeasurementRegister.cpp
 *
 *  Created on: 23.01.2017
 *      Author: vladimir
 */

#include <Code/UANC/amv/PerformanceMeasurementRegister.h>

namespace uanc {
namespace amv {
namespace PMRegister {


void PerformanceMeasurementRegister::startOverallExecutionMeasurement() {
  if(!overallMeasurement){
    overallMeasurement = std::shared_ptr<util::PerformanceMeasure<>>(
        new util::PerformanceMeasure <> ());
    overallMeasurement->start("Overall Execution Measurement");
  }
  return;
}

void PerformanceMeasurementRegister::stopOverallExecutionMeasurement() {
  if(overallMeasurement){
    overallMeasurement->stop();
  }
}

void PerformanceMeasurementRegister::registerCustomMeasurement(
    std::shared_ptr<util::PerformanceMeasure<> > measurement) {
  customMeasurements.push_back(measurement);
}

}
}
} /* namespace uanc */


