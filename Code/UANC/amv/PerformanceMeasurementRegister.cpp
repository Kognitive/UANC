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


