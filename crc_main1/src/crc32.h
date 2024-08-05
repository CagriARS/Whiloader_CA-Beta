#ifndef CRC32_H
#define CRC32_H

#include <QByteArray>
#include <cstdint>

/**
 * @brief Calculate the CRC32 checksum of the given data.
 *
 * This function computes the CRC32 checksum for the input QByteArray data using
 * the standard CRC32 polynomial.
 *
 * @param data The input data for which the CRC32 checksum is to be calculated.
 * @return The calculated CRC32 checksum as a 32-bit unsigned integer.
 */
uint32_t getCRC32(QByteArray dataPart, uint16_t dataLength);

#endif // CRC32_H
