#include "crc32.h"

/**
 * @brief Calculate the CRC32 checksum of the given data.
 *
 * This function computes the CRC32 checksum for the input QByteArray data using
 * the standard CRC32 polynomial (0x04C11DB7).
 *
 * @param data The input data for which the CRC32 checksum is to be calculated.
 * @return The calculated CRC32 checksum as a 32-bit unsigned integer.
 */


uint32_t getCRC32(QByteArray dataPart, uint16_t dataLength)
{
    uint32_t Crc = 0xFFFFFFFF;
    for (int i = 0; i < dataLength; i++)
    {
        Crc ^= dataPart[i];
        for (int j = 0; j < 32; ++j)
        {
            if (Crc & 0x80000000)
            {
                Crc = (Crc << 1) ^ 0x04C11DB7;
            }
            else
            {
                Crc <<= 1;
            }
        }
    }
    return Crc ^ 0xFFFFFFFF;
}

