#include "Config.h"
#include "Global.h"

#include "ll/api/io/FileSink.h"
#include "ll/api/io/PatternFormatter.h"

#include <memory>

namespace ChatFormatter {

Entry& Entry::getInstance() {
    static Entry instance;
    return instance;
}

bool Entry::load() { return true; } // NOLINT

bool Entry::enable() {
    mConfig.emplace();
    if (!ll::config::loadConfig(*mConfig, getSelf().getConfigDir() / u8"config.json")) {
        ll::config::saveConfig(*mConfig, getSelf().getConfigDir() / u8"config.json");
    }  
    if (getConfig().ChatLogger.LogToFile) {
        chatLogger->addSink(std::make_shared<ll::io::FileSink>(
            getConfig().ChatLogger.FilePath,
            ll::makePolymorphic<ll::io::PatternFormatter>("{tm:.3%F %T.} [{lvl}] {msg}", false)
        ));
    }
    registerPAPI();
    listenEvent();
    logger.info("ChatFormatter Loaded!");
    logger.info("Author: GroupMountain");
    logger.info("Repository: https://github.com/GroupMountain/ChatFormatter");
    return true;
}

bool Entry::disable() { // NOLINT
    unregisterPAPI();
    return true;
}

bool Entry::unload() { return true; } // NOLINT

Config& Entry::getConfig() { return mConfig.value(); }

} // namespace ChatFormatter

LL_REGISTER_MOD(ChatFormatter::Entry, ChatFormatter::Entry::getInstance());
