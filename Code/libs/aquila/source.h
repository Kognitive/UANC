/**
 * @file source.h
 *
 * Convenience header that includes all signal source-related headers.
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


#ifndef AQUILA_SOURCE_H
#define AQUILA_SOURCE_H

#include "Code/UANC/aquila/source/SignalSource.h"
#include "Code/UANC/aquila/source/Frame.h"
#include "Code/UANC/aquila/source/FramesCollection.h"
#include "Code/UANC/aquila/source/PlainTextFile.h"
#include "Code/UANC/aquila/source/RawPcmFile.h"
#include "Code/UANC/aquila/source/WaveFile.h"
#include "Code/UANC/aquila/source/WaveFileHandler.h"
#include "Code/UANC/aquila/source/generator/Generator.h"
#include "Code/UANC/aquila/source/generator/SineGenerator.h"
#include "Code/UANC/aquila/source/generator/SquareGenerator.h"
#include "Code/UANC/aquila/source/generator/TriangleGenerator.h"
#include "Code/UANC/aquila/source/generator/PinkNoiseGenerator.h"
#include "Code/UANC/aquila/source/generator/WhiteNoiseGenerator.h"
#include "Code/UANC/aquila/source/window/BarlettWindow.h"
#include "Code/UANC/aquila/source/window/BlackmanWindow.h"
#include "Code/UANC/aquila/source/window/FlattopWindow.h"
#include "Code/UANC/aquila/source/window/GaussianWindow.h"
#include "Code/UANC/aquila/source/window/HammingWindow.h"
#include "Code/UANC/aquila/source/window/HannWindow.h"
#include "Code/UANC/aquila/source/window/RectangularWindow.h"

#endif // AQUILA_SOURCE_H
