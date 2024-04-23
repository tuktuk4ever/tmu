#pragma once

// 3rdparty lib includes
#include <configconstraints_base.h>
#include <configconstraints_espchrono.h>
#include <configmanager.h>
#include <configwrapper.h>
#include <espchrono.h>
#include <makearray.h>

constexpr const auto INPUT_MAPPING_NONE = std::numeric_limits<uint8_t>::max();

using namespace espconfig;

class ConfigContainer;

extern ConfigManager<ConfigContainer> configs;

class ConfigContainer
{
public:
    // display
    struct : ConfigWrapper<bool>
    {
        bool allowReset() const override final { return true; }
        const char *nvsName() const override final { return "displayRot"; }
        bool defaultValue() const override final { return false; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } displayRotated;

    // dpad mapping
    struct : ConfigWrapper<uint8_t>
    {
        bool allowReset() const override final { return true; }
        const char *nvsName() const override final { return "dpadLeft"; }
        uint8_t defaultValue() const override final { return INPUT_MAPPING_NONE; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } dpadLeft;
    struct : ConfigWrapper<uint8_t>
    {
        bool allowReset() const override final { return true; }
        const char *nvsName() const override final { return "dpadRight"; }
        uint8_t defaultValue() const override final { return INPUT_MAPPING_NONE; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } dpadRight;
    struct : ConfigWrapper<uint8_t>
    {
        bool allowReset() const override final { return true; }
        const char *nvsName() const override final { return "dpadUp"; }
        uint8_t defaultValue() const override final { return INPUT_MAPPING_NONE; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } dpadUp;
    struct : ConfigWrapper<uint8_t>
    {
        bool allowReset() const override final { return true; }
        const char *nvsName() const override final { return "dpadDown"; }
        uint8_t defaultValue() const override final { return INPUT_MAPPING_NONE; }
        ConfigConstraintReturnType checkValue(value_t value) const override final { return {}; }
    } dpadDown;

    template<typename T>
    void callForEveryConfig(T &&callable)
    {
#define REGISTER_CONFIG(name) \
        if (callable(name)) return;

        // display
        REGISTER_CONFIG(displayRotated);

        // dpad mapping
        REGISTER_CONFIG(dpadLeft);
        REGISTER_CONFIG(dpadRight);
        REGISTER_CONFIG(dpadUp);
        REGISTER_CONFIG(dpadDown);
    }
};
