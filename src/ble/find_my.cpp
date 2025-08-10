#include "find_my.h"
#include <stdio.h>

// Service and characteristic UUIDs
#define FAST_PAIR_SERVICE_UUID "FE2C"
#define BEACON_ACTIONS_CHAR_UUID "FE2C1238836648148EB001DE32100BEA"
#define ORIENTATION_CHAR_UUID    "FE2C1239836648148EB001DE32100BEA"

FindMy::FindMy(NINA_SPI &nina) : _nina(nina) {}

bool FindMy::init() {
    if (!set_device_name()) {
        printf("Failed to set device name\\n");
        return false;
    }

    if (!add_service()) {
        printf("Failed to add service\\n");
        return false;
    }

    if (!add_beacon_actions_characteristic()) {
        printf("Failed to add beacon actions characteristic\\n");
        return false;
    }

    if (!add_orientation_characteristic()) {
        printf("Failed to add orientation characteristic\\n");
        return false;
    }

    if (!start_advertising()) {
        printf("Failed to start advertising\\n");
        return false;
    }

    return true;
}

void FindMy::process() {
    // Handle incoming BLE commands
}

void FindMy::update_orientation(float pitch, float roll) {
    char command[100];
    // This is a placeholder. The actual implementation will need to format the data
    // correctly and use the appropriate AT command to update the characteristic.
    sprintf(command, "AT+UBTGWV=%s,%f,%f", ORIENTATION_CHAR_UUID, pitch, roll);
    _nina.send_command(command, NULL, 0);
}

bool FindMy::set_device_name() {
    char command[50];
    sprintf(command, "AT+UBTLN=\\"SkiTag\\"");
    return _nina.send_command(command, NULL, 0);
}

bool FindMy::add_service() {
    char command[50];
    sprintf(command, "AT+UBTGSER=%s,1", FAST_PAIR_SERVICE_UUID);
    return _nina.send_command(command, NULL, 0);
}

bool FindMy::add_beacon_actions_characteristic() {
    char command[100];
    // Properties: Read, Write, Notify
    sprintf(command, "AT+UBTGCHA=%s,12", BEACON_ACTIONS_CHAR_UUID);
    return _nina.send_command(command, NULL, 0);
}

bool FindMy::add_orientation_characteristic() {
    char command[100];
    // Properties: Read, Notify
    sprintf(command, "AT+UBTGCHA=%s,10", ORIENTATION_CHAR_UUID);
    return _nina.send_command(command, NULL, 0);
}

bool FindMy::start_advertising() {
    // Start advertising with the service UUID
    char command[50];
    sprintf(command, "AT+UBTAD=1,%s", FAST_PAIR_SERVICE_UUID);
    return _nina.send_command(command, NULL, 0);
}
