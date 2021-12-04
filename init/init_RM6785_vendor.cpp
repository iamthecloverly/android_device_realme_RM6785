//
// Copyright (C) 2022 The LineageOS Project
//
// SPDX-License-Identifier: Apache-2.0
//

#include <android-base/logging.h>
#include <android-base/properties.h>
#include <fstream>

#define PROC_NFC "/proc/oppo_nfc/chipset"
#define PROC_OPERATOR "/proc/oppoVersion/operatorName"

void set_property(std::string prop, std::string value) {
    LOG(INFO) << "Setting property: " << prop << " to " << value;
    if (!android::base::SetProperty(prop.c_str(), value.c_str()))
        LOG(ERROR) << "Unable to set: " << prop << " to " << value;
}

void nfc_detect() {
    std::string chipset;
    std::ifstream nfc_file(PROC_NFC);

    getline(nfc_file, chipset);

    LOG(INFO) << "oppo_nfc : chipset " << chipset;

    if (chipset != "NULL")
        set_property("ro.vendor.nfc_device", "1");
}

void power_profile() {
    std::string op;
    std::ifstream operator_file(PROC_OPERATOR);

    getline(operator_file, op);

    int operatorName = stoi(op);

    switch (operatorName) {
        case 94: case 140: case 141: case 142: case 146: case 148: case 149:
            LOG(INFO) << "operatorName: " << operatorName;
            set_property("ro.vendor.power_profile.device", "RMX2151");
            break;
        case 90: case 92: case 143: case 145: case 147:
            LOG(INFO) << "operatorName: " << operatorName;
            set_property("ro.vendor.power_profile.device", "RMX2161");
            break;
        default:
            LOG(INFO) << "operatorName: " << operatorName;
    }
}

int main() {
    nfc_detect();
    power_profile();
}
