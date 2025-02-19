#pragma once

#include "Config.h"

#include <ll/api/mod/NativeMod.h>
#include <ll/api/mod/RegisterHelper.h>

namespace ChatFormatter {

class Entry {

public:
    static Entry& getInstance();

    Entry() : mSelf(*ll::mod::NativeMod::current()) {}

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    /// @return True if the plugin is loaded successfully.
    bool load();

    /// @return True if the plugin is enabled successfully.
    bool enable();

    /// @return True if the plugin is disabled successfully.
    bool disable();

    // /// @return True if the plugin is unloaded successfully.
    bool unload();

    Config& getConfig();

private:
    ll::mod::NativeMod&   mSelf;
    std::optional<Config> mConfig;
};

} // namespace ChatFormatter
