#ifndef CAN_CRC_H
#define CAN_CRC_H


uint16_t calc_can_crc(const uint8_t *data, int bit_length) {
    uint16_t crc_rg = 0;

    for (size_t i = 0; i < bit_length; i++) {
        uint8_t nxtbit = (data[i / 8] >> (7 - (i % 8))) & 0x01;

        uint8_t crc_bit14 = (crc_rg >> 14) & 0x01;
        uint8_t crcnxt = nxtbit ^ crc_bit14;

        crc_rg = (crc_rg << 1) & 0x7FFF;

        if (crcnxt) {
            crc_rg ^= 0x4599;
        }
    }

    return crc_rg;
}

#endif // CAN_CRC_H