/**
 * @file     :libcrc_sample.c
 * @author   :wangwang105(wang rong wen)
/**
 * @file libcrc_sample.c
 * @brief Example usage of the libcrc library for CRC calculations.
 *
 * This file demonstrates how to use the libcrc library to perform
 * CRC (Cyclic Redundancy Check) calculations in an embedded system
 * using the RT-Thread operating system on an STM32F407VETx microcontroller.
 * @version  :0.1
 * @date     :2025-01-09 10:54:10
 *
 * @copyright:Copyright (c) 2025 wangwang105(wang rong wen).AllRightsReserved.
 */

#include "checksum.h"
#include <rtthread.h>
#include <stdbool.h>
#include <stdio.h>

#if defined(LIBCRC_USING_CRC16) &&          \
    defined(LIBCRC_USING_CRC_CCITT_1D0F) && \
    defined(LIBCRC_USING_CRC_CCITT_FFFF) && \
    defined(LIBCRC_USING_CRC_DNP) &&        \
    defined(LIBCRC_USING_CRC_KERMIT) &&     \
    defined(LIBCRC_USING_CRC_MODBUS) &&     \
    defined(LIBCRC_USING_CRC_SICK) &&       \
    defined(LIBCRC_USING_CRC_XMODEM) &&     \
    defined(LIBCRC_USING_CRC32)

#define MAX_STRING_SIZE 512
int crc(int argc, char *argv[])
{
    char input_string[MAX_STRING_SIZE];
    unsigned char *ptr;
    unsigned char *dest;
    unsigned char hex_val;
    unsigned char prev_byte;
    uint16_t crc_16_val;
    uint16_t crc_16_modbus_val;
    uint16_t crc_ccitt_ffff_val;
    uint16_t crc_ccitt_0000_val;
    uint16_t crc_ccitt_1d0f_val;
    uint16_t crc_dnp_val;
    uint16_t crc_sick_val;
    uint16_t crc_kermit_val;
    uint32_t crc_32_val;
    uint16_t low_byte;
    uint16_t high_byte;
    int a;
    int ch;
    bool do_ascii;
    bool do_hex;
    // FILE *fp;

    do_ascii = false;
    do_hex = false;

    printf("\ncrc: CRC algorithm sample program\nCopyright (c) 2025 wangwang105(Wang rong wen)\n\n");

    if (argc < 2)
    {
        printf("Usage: crc [-a|-x] inputstring \n\n");
        printf("    -a Program asks for ASCII input. Following parameters ignored.\n");
        printf("    -x Program asks for hexadecimal input. Following parameters ignored.\n");
        return -RT_ERROR;
    }

    if (!rt_strcmp(argv[1], "-a") || !rt_strcmp(argv[1], "-A"))
        do_ascii = true;
    if (!rt_strcmp(argv[1], "-x") || !rt_strcmp(argv[1], "-X"))
        do_hex = true;

    if (do_ascii || do_hex)
    {
        rt_strncpy(input_string, argv[2], sizeof(input_string) - 1);
        input_string[sizeof(input_string) - 1] = '\0';
    }

    if (do_ascii)
    {
        ptr = (unsigned char *)input_string;
        while (*ptr && *ptr != '\r' && *ptr != '\n')
            ptr++;
        *ptr = 0;
    }

    if (do_hex)
    {
        ptr = (unsigned char *)input_string;
        dest = (unsigned char *)input_string;

        while (*ptr && *ptr != '\r' && *ptr != '\n')
        {
            if (*ptr >= '0' && *ptr <= '9')
                *dest++ = (unsigned char)((*ptr) - '0');
            if (*ptr >= 'A' && *ptr <= 'F')
                *dest++ = (unsigned char)((*ptr) - 'A' + 10);
            if (*ptr >= 'a' && *ptr <= 'f')
                *dest++ = (unsigned char)((*ptr) - 'a' + 10);

            ptr++;
        }

        *dest = '\x80';
        *(dest + 1) = '\x80';
    }

    crc_16_val = 0x0000;
    crc_16_modbus_val = 0xffff;
    crc_dnp_val = 0x0000;
    crc_sick_val = 0x0000;
    crc_ccitt_0000_val = 0x0000;
    crc_ccitt_ffff_val = 0xffff;
    crc_ccitt_1d0f_val = 0x1d0f;
    crc_kermit_val = 0x0000;
    crc_32_val = 0xffffffffL;

    if (do_ascii)
    {
        prev_byte = 0;
        ptr = (unsigned char *)input_string;

        while (*ptr)
        {
            crc_16_val = update_crc_16(crc_16_val, *ptr);
            crc_16_modbus_val = update_crc_16(crc_16_modbus_val, *ptr);
            crc_dnp_val = update_crc_dnp(crc_dnp_val, *ptr);
            crc_sick_val = update_crc_sick(crc_sick_val, *ptr, prev_byte);
            crc_ccitt_0000_val = update_crc_ccitt(crc_ccitt_0000_val, *ptr);
            crc_ccitt_ffff_val = update_crc_ccitt(crc_ccitt_ffff_val, *ptr);
            crc_ccitt_1d0f_val = update_crc_ccitt(crc_ccitt_1d0f_val, *ptr);
            crc_kermit_val = update_crc_kermit(crc_kermit_val, *ptr);
            crc_32_val = update_crc_32(crc_32_val, *ptr);

            prev_byte = *ptr;
            ptr++;
        }
    }

    else if (do_hex)
    {
        prev_byte = 0;
        ptr = (unsigned char *)input_string;

        while (*ptr != '\x80')
        {
            hex_val = (unsigned char)((*ptr & '\x0f') << 4);
            hex_val |= (unsigned char)((*(ptr + 1) & '\x0f'));

            crc_16_val = update_crc_16(crc_16_val, hex_val);
            crc_16_modbus_val = update_crc_16(crc_16_modbus_val, hex_val);
            crc_dnp_val = update_crc_dnp(crc_dnp_val, hex_val);
            crc_sick_val = update_crc_sick(crc_sick_val, hex_val, prev_byte);
            crc_ccitt_0000_val = update_crc_ccitt(crc_ccitt_0000_val, hex_val);
            crc_ccitt_ffff_val = update_crc_ccitt(crc_ccitt_ffff_val, hex_val);
            crc_ccitt_1d0f_val = update_crc_ccitt(crc_ccitt_1d0f_val, hex_val);
            crc_kermit_val = update_crc_kermit(crc_kermit_val, hex_val);
            crc_32_val = update_crc_32(crc_32_val, hex_val);

            prev_byte = hex_val;
            ptr += 2;
        }

        input_string[0] = 0;
    }

    crc_32_val ^= 0xffffffffL;

    crc_dnp_val = ~crc_dnp_val;
    low_byte = (crc_dnp_val & 0xff00) >> 8;
    high_byte = (crc_dnp_val & 0x00ff) << 8;
    crc_dnp_val = low_byte | high_byte;

    low_byte = (crc_sick_val & 0xff00) >> 8;
    high_byte = (crc_sick_val & 0x00ff) << 8;
    crc_sick_val = low_byte | high_byte;

    low_byte = (crc_kermit_val & 0xff00) >> 8;
    high_byte = (crc_kermit_val & 0x00ff) << 8;
    crc_kermit_val = low_byte | high_byte;

    rt_kprintf("%s :\n", input_string);
    rt_kprintf("CRC16              = 0x%04x \n", crc_16_val);
    rt_kprintf("CRC16 (Modbus)     = 0x%04x \n", crc_16_modbus_val);
    rt_kprintf("CRC16 (Sick)       = 0x%04x \n", crc_sick_val);
    rt_kprintf("CRC-CCITT (0x0000) = 0x%04x \n", crc_ccitt_0000_val);
    rt_kprintf("CRC-CCITT (0xffff) = 0x%04x \n", crc_ccitt_ffff_val);
    rt_kprintf("CRC-CCITT (0x1d0f) = 0x%04x \n", crc_ccitt_1d0f_val);
    rt_kprintf("CRC-CCITT (Kermit) = 0x%04x \n", crc_kermit_val);
    rt_kprintf("CRC-DNP            = 0x%04x \n", crc_dnp_val);
    rt_kprintf("CRC32              = 0x%08x \n", crc_32_val);

    return 0;

} /* (crc.c) */
MSH_CMD_EXPORT(crc, crc_algorithm sample program);

#endif

#if defined(LIBCRC_USING_CRC8)
int crc8(int argc, char *argv[])
{
    char input_string[MAX_STRING_SIZE] = {0};
    if (argc < 2)
    {
        printf("Usage: crc <arg1> \n\n");
        printf(" <arg1>: Program asks for ASCII input.\n");
        return -RT_ERROR;
    }

    rt_strncpy(input_string, argv[1], sizeof(input_string) - 1);
    input_string[sizeof(input_string) - 1] = '\0';

    int crc8 = crc_8((const unsigned char *)input_string, sizeof(input_string) - 1);
    rt_kprintf("%s :\n", input_string);
    rt_kprintf("CRC8               = 0x%02x \n", crc8);
    return RT_EOK;
}
MSH_CMD_EXPORT(crc8, a simple crc_8 algorithm sample program);

#endif
