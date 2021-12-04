//
// Copyright (C) 2022 The LineageOS Project
//
// SPDX-License-Identifier: Apache-2.0
//

#include <fstream>
#include <tuple>
#include <android-base/logging.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "vendor_init.h"

#define PROC_OPERATOR "/proc/oppoVersion/operatorName"

void property_override(std::string prop, std::string value, bool add = true) {
    auto pi = (prop_info *)__system_property_find(prop.c_str());

    if (pi != nullptr) {
        __system_property_update(pi, value.c_str(), value.size());
    } else if (add) {
        __system_property_add(prop.c_str(), prop.size(), value.c_str(),
                              value.size());
    }
}

void set_ro_build_prop(const std::string &prop, const std::string &value,
                       bool product = true) {
    std::string prop_name;
    std::string prop_types[] = {
        "",
        "bootimage.",
        "odm.",
        "odm_dlkm.",
        "product.",
        "system.",
        "system_ext.",
        "vendor.",
        "vendor_dlkm.",
    };

    for (const std::string &source : prop_types) {
        if (product) {
            prop_name = "ro.product." + source + prop;
        } else {
            prop_name = "ro." + source + "build." + prop;
        }

        property_override(prop_name, value, false);
    }
}

std::tuple<std::string, std::string> get_device() {
    std::string device, model, line;
    std::ifstream operator_file(PROC_OPERATOR);
    operator_file.good();
    getline(operator_file, line);

    int operatorName = stoi(line);

    switch (operatorName) {
        // realme 6
        case 101:
        case 102:
        case 104:
        case 105:
            device = "RMX2001L1";
            model = "RMX2001";
            break;
        case 106:
            device = "RMX2003L1";
            model = "RMX2003";
            break;
        case 113:
            device = "RMX2005L1";
            model = "RMX2005";
            break;
        // realme 6i/6s/Narzo
        case 111:
        case 112:
        case 114:
            device = "RMX2002L1";
            model = "RMX2002";
            break;
        // realme 7
        case 140:
        case 141:
        case 146:
        case 149:
            device = "RMX2151L1";
            model = "RMX2151";
            break;
        case 142:
            device = "RMX2153L1";
            model = "RMX2153";
            break;
        case 94:
        case 148:
            device = "RMX2155L1";
            model = "RMX2155";
            break;
        // realme Narzo 30 4G
        case 90:
        case 92:
            device = "RMX2156L1";
            model = "RMX2156";
            break;
        // realme Narzo 20 Pro
        case 143:
            device = "RMX2161L1";
            model = "RMX2161";
            break;
        case 145:
        case 147:
            device = "RMX2163L1";
            model = "RMX2163";
            break;
        default:
            LOG(ERROR) << "Unable to read operator from " << PROC_OPERATOR;
    }
    return {device, model};
}

void vendor_load_properties() {
#ifndef __ANDROID_RECOVERY__
    auto [device, model] = get_device();

    set_ro_build_prop("device", device);
    set_ro_build_prop("model", model);
    set_ro_build_prop("name", model);
    set_ro_build_prop("product", model, false);
#endif
}
