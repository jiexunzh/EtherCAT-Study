#ifndef EEPROMTOOL_H
#define EEPROMTOOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
    uint16_t slave_num;
    uint16_t PDI_control;
    uint16_t PDI_config;
    uint16_t config_alias;
    uint16_t checksum;
    uint16_t calculated;
    uint32_t vendor_id;
    uint32_t product_code;
    uint32_t revision_number;
    uint32_t serial_number;
    uint16_t mailbox_protocol;
    uint16_t size;
    uint16_t version;
} EEPROM_info_t;

void my_eeprom_display(char *ifname, int slave_num, char *fname, EEPROM_info_t *p_info);
void my_eeprom_read(char *ifname, int slave_num, char *fname);
void my_eeprom_write(char *ifname, int slave_num, char *fname);

#endif /* EEPROMTOOL_H */
