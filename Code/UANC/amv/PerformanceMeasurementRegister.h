/*
 * performanceMeasurementRegister.h
 *
 *  Created on: 23.01.2017
 *      Author: vladimir
 */

#ifndef CODE_UANC_AMV_ANC_MODEL_PERFORMANCEMEASUREMENTREGISTER_H_
#define CODE_UANC_AMV_ANC_MODEL_PERFORMANCEMEASUREMENTREGISTER_H_

#include "../util/PerformanceMeasure.h"
#include <vector>

namespace uanc {
namespace amv {
namespace PMRegister {

/** \brief This is an ANCModel.
 *
 * This is the class for registering new Performance Measurements for an Algorithm.
 * It also contains the special default measurement which is executed for every class
 * which inherits from ANCAlgorithm.
 */
class PerformanceMeasurementRegister {
 public:

  /**
   *  This starts the execution of the overall Execution Measurement. This may be only executed once.
   */
  void startOverallExecutionMeasurement();

  /**
   *  Stops the overall execution measurement, if it is running
   */
  void stopOverallExecutionMeasurement();

  /**
   *  Registers a custom measurement.
   *  @param measurement: The pointer to new measurement to register.
   */
  void registerCustomMeasurement(
      std::shared_ptr<util::PerformanceMeasure<>> measurement);

  /**
 *  Give back the actual custom measurements
 */
  const std::vector<std::shared_ptr<util::PerformanceMeasure<> > >& getCustomMeasurements() const {
    return customMeasurements;
  }

  /**
 *  Give back the overall measurment
 */
  const std::shared_ptr<util::PerformanceMeasure<> >& getOverallMeasurement() const {
    return overallMeasurement;
  }

 private:
  /**
   * Holds a pointer to the custom measurements
   */
  std::vector<std::shared_ptr<util::PerformanceMeasure<>>> customMeasurements;
  /**
   * Holds a pointer to the overall measurement
   */
  std::shared_ptr<util::PerformanceMeasure<>> overallMeasurement;

};

}
}
} /* namespace uanc */

#endif /* CODE_UANC_AMV_ANC_MODEL_PERFORMANCEMEASUREMENTREGISTER_H_ */
