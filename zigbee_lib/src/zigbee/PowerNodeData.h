//
// Created by paolo on 11/05/17.
//

#ifndef DOMUS_ENGINE_POWERNODEDATA_H_H
#define DOMUS_ENGINE_POWERNODEDATA_H_H

#include <zigbee/NwkAddr.h>

namespace zigbee {

    enum class PowerMode {
        ALWAYS_ON, RECV_AUTO, RECV_STIM, RESERVED
    };

    inline PowerMode powerModefrom(int val) {
        switch (val) {
            case 0:
                return PowerMode::ALWAYS_ON;
            case 1:
                return PowerMode::RECV_AUTO;
            case 2:
                return PowerMode::RECV_STIM;
            default:
                return PowerMode::RESERVED;
        }
    }

    inline std::string toString(PowerMode powerMode){
        switch (powerMode){
            case PowerMode::ALWAYS_ON:
                return "ALWAYS_ON";
            case PowerMode::RECV_AUTO:
                return "RECV_AUTO";
            case PowerMode::RECV_STIM:
                return "RECV_STIM";
            default:
                return "RESERVED";
        }
    }

    class PowerSource {
    public:
        PowerSource() : value(0) {}

        PowerSource(uint8_t value) : value(value) {};

        bool isMainPower() const{ return value && 0x01; }

        bool isRechargeable() const { return value && 0x02; }

        bool isDisposable() const{ return value && 0x04; }

        uint8_t getValue() const {return value;}

    private:
        uint8_t value;
    };

    enum class PowerLevel {
        CRITICAL, LEVEL_33, LEVEL_66, LEVEL_100, RESERVED
    };

    inline PowerLevel powerLevelFrom(int val) {
        switch (val) {
            case 0x00:
                return PowerLevel::CRITICAL;
            case 0x04:
                return PowerLevel::LEVEL_33;
            case 0x08:
                return PowerLevel::LEVEL_66;
            case 0x0C:
                return PowerLevel::LEVEL_100;
            default:
                return PowerLevel::RESERVED;
        }
    }

    inline std::string toString(PowerLevel powerLevel){
        switch (powerLevel){
            case PowerLevel::CRITICAL:
                return "CRITICAL";
            case PowerLevel::LEVEL_33:
                return "LEVEL_33";
            case PowerLevel::LEVEL_66:
                return "LEVEL_66";
            case PowerLevel::LEVEL_100:
                return "LEVEL_100";
            default:
                return "RESERVED";
        }
    }


    struct PowerNodeData {
        PowerNodeData(PowerNodeData &&a) : nwkAddr(a.nwkAddr), powerMode(a.powerMode),
                                           availablePowerSource(a.availablePowerSource),
        currentPowerSource(a.currentPowerSource),
        currentPowerSourceLevel(a.currentPowerSourceLevel){};

        PowerNodeData() {}

        ~PowerNodeData() {}

        NwkAddr nwkAddr;
        PowerMode powerMode;
        PowerSource availablePowerSource;
        PowerSource currentPowerSource;
        PowerLevel currentPowerSourceLevel;
    };

}

#endif //DOMUS_ENGINE_POWERNODEDATA_H_H
