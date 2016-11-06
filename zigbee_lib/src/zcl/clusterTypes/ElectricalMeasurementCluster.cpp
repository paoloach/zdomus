//
// Created by Paolo Achdjian on 11/18/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//
#include "../attributeTypes/ZCLuint8Attribute.h"
#include "ElectricalMeasurementCluster.h"

namespace zigbee {
    static std::vector<Cluster::AttributeDef> attributesDef{
            Cluster::AttributeDef(ZCLTypeDataType::ZCLType32bitBitmap, 0, "Measurement Type", true),

            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x100, "DC Voltage", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x101, "DC Voltage Min", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x102, "DC Voltage Max", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x103, "DC Current", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x104, "DC Current Min", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x105, "DC Current Max", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x106, "DC Power", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x107, "DC Power Min", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x108, "DC Power Max", true),

            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x200, "DC Voltage Multiplier", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x201, "DC Voltage Divisor", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x202, "DC Current Multiplier", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x203, "DC Current Divisor", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x204, "DC Power Multiplier", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x205, "DC Power Divisor", true),

            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x300, "AC Frequency", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x301, "AC Frequency Min", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x302, "AC Frequency Max", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x303, "Neutral Curren", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt32, 0x304, "Total Active Power", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt32, 0x305, "Total Reactive Power", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 0x306, "Total Apparent Powew", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x307, "Measured 1st Harmonic Current", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x308, "Measured 3st Harmonic Current", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x309, "Measured 5st Harmonic Current", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x30a, "Measured 7st Harmonic Current", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x30b, "Measured 9st Harmonic Current", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x30c, "Measured 11st Harmonic Current", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x30d, "Measured Phase 1st Harmonic Current", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x30e, "Measured Phase 3st Harmonic Current", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x30f, "Measured Phase 5st Harmonic Current", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x310, "Measured Phase 7st Harmonic Current", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x311, "Measured Phase 9st Harmonic Current", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x312, "Measured Phase 11st Harmonic Current", true),

            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x400, "AC Frequence Multiplier", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x401, "AC Frequence Divisor", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 0x402, "Power Multiplier", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 0x403, "Power Divisor", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt8, 0x404, "Harmonic Current Multiplier", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt8, 0x405, "Harmonic Current Divisor", true),

            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x501, "Line Current", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x502, "Active Current", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x503, "Reactive Current", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x505, "RMS Voltage", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x506, "RMS Voltage Min", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x507, "RMS Voltage Max", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x508, "RMS Current", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x509, "RMS Current Min", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x50a, "RMS Current Max", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x50b, "Active Power", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x50c, "Active Power Min", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x50d, "Active Power Max", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x50e, "Reactive Power", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x50f, "Apparent Power", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt8, 0x510, "Power Factor", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x511, "Average RMS Voltage Measurement Period", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x512, "Average RMS Over Voltage Counter", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x513, "Average RMS Under Voltage Counter", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x514, "RMS Extreme Over Voltage Period", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x515, "RMS Extreme Under Voltage Period", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x516, "RMS Voltage Sag Period", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x517, "RMS Voltage Swell Period", true),

            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x600, "AC Voltage Multiplier", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x601, "AC Voltage Divisor", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x602, "AC Current Multiplier", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x603, "AC Current Divisor", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x604, "AC Power Multiplier", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x605, "AC Power Divisor", true),

            Cluster::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x700, "DC Overload Alarms Mask", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x701, "DC Voltage Overload", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x702, "DC Current Overload", true),

            Cluster::AttributeDef(ZCLTypeDataType::ZCLType16bitBitmap, 0x800, "AC Alarms Mask", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x801, "AC Voltage Overload", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x802, "AC Current Overloa", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x803, "AC Active Power Overload", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x804, "AC Reactive Poweer Overload", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x805, "Average RMS Over Voltage", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x806, "Average RMS Under Voltage", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x807, "RMS Extreme Over Voltage", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x808, "RMS Extreme Under Voltage", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x809, "RMS Voltage Sag", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x80A, "RMS Voltage Swell", true),

            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x901, "Line Current PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x902, "Active Current PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x903, "Reactive Current PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x905, "RMS Voltage PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x906, "RMS Voltage Min PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x907, "RMS Voltage Max PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x908, "RMS Current PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x909, "RMS Current Min PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x90a, "RMS Current Max PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x90b, "Active Power PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x90c, "Active Power Min PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x90d, "Active Power Max PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x90e, "Reactive Power PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x90f, "Apparent Power PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt8, 0x910, "Power Factor PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x911, "Average RMS Voltage Measurement Period PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x912, "Average RMS Over Voltage Counter PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x913, "Average RMS Under Voltage Counter PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x914, "RMS Extreme Over Voltage Period PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x915, "RMS Extreme Under Voltage Period PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x916, "RMS Voltage Sag Period PhB", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x917, "RMS Voltage Swell Period PhB", true),

            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0xa01, "Line Current PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0xa02, "Active Current PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0xa03, "Reactive Current PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0xa05, "RMS Voltage PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0xa06, "RMS Voltage Min PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0xa07, "RMS Voltage Max PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0xa08, "RMS Current PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0xa09, "RMS Current Min PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0xa0a, "RMS Current Max PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0xa0b, "Active Power PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0xa0c, "Active Power Min PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0xa0d, "Active Power Max PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0xa0e, "Reactive Power PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0xa0f, "Apparent Power PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt8, 0xa10, "Power Factor PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0xa11, "Average RMS Voltage Measurement Period PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0xa12, "Average RMS Over Voltage Counter PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0xa13, "Average RMS Under Voltage Counter PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0xa14, "RMS Extreme Over Voltage Period PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0xa15, "RMS Extreme Under Voltage Period PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0xa16, "RMS Voltage Sag Period PhC", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0xa17, "RMS Voltage Swell Period PhC", true)

    };

    ElectricalMeasurementCluster::ElectricalMeasurementCluster(ZigbeeDevice * zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
            Cluster(zigbeeDevice, endpoint, networkAddress) {
        createAttributes(attributesDef);

        _commandsDef.emplace_back([=](std::vector<uint8_t> &&) { zigbeeDevice->sendCmd(networkAddress, endpoint, ElectricalMeasurament, 0); }, 0,
                                  "Get Profile Info Command");
        _commandsDef.emplace_back(
                [=](std::vector<uint8_t> &&) { zigbeeDevice->sendCmd(networkAddress, endpoint, ElectricalMeasurament, 1); },
                1,
                "Get Measurement Profile Command",
                std::make_shared<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("Attribute ID"),
                std::make_shared<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUTCTime>>("Start Time"),
                std::make_shared<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt8>>("Number Of Intervals")
        );
    }

    ClusterID ElectricalMeasurementCluster::getId() const {
        return ElectricalMeasurament;
    }

    std::string ElectricalMeasurementCluster::getClusterName() const {
        return "Electrical Measurement";
    }

}
