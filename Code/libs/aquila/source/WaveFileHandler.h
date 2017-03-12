/**
 * @file WaveFileHandler.h
 *
 * A utility class to handle loading and saving of .wav files.
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

#ifndef WAVEFILEHANDLER_H
#define WAVEFILEHANDLER_H

#include "../global.h"
#include "SignalSource.h"
#include "WaveFile.h"
#include <cstddef>
#include <string>

namespace Aquila
{
    /**
     * Forward declaration to avoid including WaveFile.h header.
     */
    struct WaveHeader;

    /**
     * A utility class to handle loading and saving of .wav files.
     */
    class AQUILA_EXPORT WaveFileHandler
    {
    public:
        WaveFileHandler(const std::string& filename);

        void readHeaderAndChannels(WaveHeader& header,
            WaveFile::ChannelType& leftChannel, WaveFile::ChannelType& rightChannel);

        void save(const SignalSource& source);

        static void decode16bit(WaveFile::ChannelType& channel,
            short* data, std::size_t channelSize);
        static void decode16bitStereo(WaveFile::ChannelType& leftChannel,
            WaveFile::ChannelType& rightChannel, short* data, std::size_t channelSize);

        static void decode8bit(WaveFile::ChannelType& channel,
            short* data, std::size_t channelSize);
        static void decode8bitStereo(WaveFile::ChannelType& leftChannel,
            WaveFile::ChannelType& rightChannel, short* data, std::size_t channelSize);

        static void encode16bit(const SignalSource& source, short* data, std::size_t dataSize);
        static void encode8bit(const SignalSource& source, short* data, std::size_t dataSize);

    private:
        /** \brief finds the beginning of the wav data section relative to the beginning of the file
         * @param id The id, identifying the chunck.
         * @param fs The fstream to the wav file
         * @return The index of the first byte of the specified chunk after the id if found. Else -1.
         */
        int findBeginOfChunck(const char *id, std::fstream *fs );

        /** \brief Computes the length of a chunck.
         * @param fs: A pointer to the filestream.
         * @param offset: The beginning of the chunks length.
         */
        int computeChunkLength(std::fstream* fs, unsigned int offset);

        void createHeader(const SignalSource& source, WaveHeader& header);
        static void splitBytes(short twoBytes, unsigned char& lb, unsigned char& hb);

        /**
         * Destination or source file.
         */
        std::string m_filename;
    };
}

#endif // WAVEFILEHANDLER_H
