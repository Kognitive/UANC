/**
 * @file OouraFft.cpp
 *
 * A wrapper for the FFT algorithm found in Ooura mathematical packages.
 *
 * This file is part of the Aquila DSP library.
 * Aquila is free software, licensed under the MIT/X11 License. A copy of
 * the license is provided with the library in the LICENSE file.
 *
 * @package Aquila
 * @version 3.0.0-dev
 * @author Zbigniew Siciarz
 * @date 2007-2014
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 3.0.0
 */

#include "OouraFft.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdlib.h>
#include <cstring>
#include <memory>

namespace Aquila
{
    /**
     * Initializes the transform for a given input length.
     *
     * Prepares the work area for Ooura's algorithm.
     *
     * @param length input signal size (usually a power of 2)
     */
OouraFft::OouraFft(std::size_t length)
    : Fft(length),
      stuffedLength(
                static_cast<std::size_t>(std::pow(2, std::ceil(std::log2(length))))) ,
      // according to the description: "length of ip >= 2+sqrt(n)"
      ip(new int[static_cast<std::size_t>(2 + std::sqrt(stuffedLength))]),
      w(new double[static_cast<std::size_t>(stuffedLength) / 2])
      {
  ip[0] = 0;
}

    /**
     * Destroys the transform object and cleans up working area.
     */
    OouraFft::~OouraFft()
    {
        delete [] w;
        delete [] ip;
    }


    /**
     * Returns the length which was used during the FFT transformation.
     *
     * @return the stuffed length
     */
    std::size_t OouraFft::getStuffedLength(){
      return this->stuffedLength;
    }

    /**
     * Applies the transformation to the signal.
     *
     * @param x input signal
     * @return calculated spectrum
     */
    SpectrumType OouraFft::fft(const SampleType x[])
    {
        static_assert(
            sizeof(ComplexType[2]) == sizeof(double[4]),
            "complex<double> has the same memory layout as two consecutive doubles"
        );

        const SampleType *z( x);

        //Stuff the Samples with zeros, if the stuffed length is greater than the sample's length
        SampleType* stuffedSamples;
        if (stuffedLength > N) {
          stuffedSamples = new SampleType[stuffedLength];
          std::memcpy( stuffedSamples, x, N * sizeof(SampleType) );
          z = stuffedSamples;
          for(int i = N; i < stuffedLength; ++i){
            stuffedSamples[i] = 0;
          }
        }
        // create a temporary storage array and copy input to even elements
        // of the array (real values), leaving imaginary components at 0
        double* a = new double[2 * stuffedLength];
        for (std::size_t i = 0; i < stuffedLength; ++i)
        {
            a[2 * i] = z[i];
            a[2 * i + 1] = 0.0;
        }

        // let's call the C function from Ooura's package
        cdft(2*stuffedLength, -1, a, ip, w);
        // convert the array back to complex values and return as vector
        ComplexType* tmpPtr = reinterpret_cast<ComplexType*>(a);
        //Trim the produced FFT again
        SpectrumType spectrum(tmpPtr, tmpPtr + N);
        delete [] a;
        if (stuffedLength != N) {
          delete [] stuffedSamples;
        }

        return spectrum;
    }

    /**
     * Applies the inverse transform to the spectrum.
     *
     * @param spectrum input spectrum
     * @param x output signal, its size must
     */
    std::shared_ptr<std::vector<double>> OouraFft::ifft(SpectrumType spectrum)
    {

        static_assert(
            sizeof(ComplexType[2]) == sizeof(double[4]),
                "complex<double> has the same memory layout as two consecutive doubles"
        );

        std::shared_ptr<std::vector<double>> x = std::shared_ptr<std::vector<double>>(new std::vector<double>());
        SpectrumType *z( &spectrum);

        //Stuff the input samples with zeros, if necessary
        SpectrumType stuffedSamples;
        if (stuffedLength != N) {
          stuffedSamples = spectrum;
          z = &stuffedSamples;
          for (int i = 0; i < stuffedLength; ++i) {
            stuffedSamples.push_back(0);
          }
        }

        // interpret the vector as consecutive pairs of doubles (re,im)
        // and copy to input/output array
        double* tmpPtr = reinterpret_cast<double*>(&((*z)[0]));
        double* a = new double[2 * stuffedLength];
        std::copy(tmpPtr, tmpPtr + 2 * stuffedLength, a);

        // Ooura's function
        cdft(2*stuffedLength, 1, a, ip, w);

        // copy the data to the double array and scale it
        for (std::size_t i = 0; i < stuffedLength; ++i)
        {
            x->push_back(a[2 * i] / static_cast<double>(stuffedLength));
        }
        delete [] a;
        return x;
    }
}
