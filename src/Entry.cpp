#include "Entry.h"
#include "Global.h"

ll::Logger logger(PLUGIN_NAME);

namespace ChatFormatter {

std::unique_ptr<Entry>& Entry::getInstance() {
    static std::unique_ptr<Entry> instance;
    return instance;
}

bool Entry::load() { return true; }

bool Entry::enable() {
    mConfig.emplace();
    if (!ll::config::loadConfig(*mConfig, getSelf().getConfigDir() / u8"config.json")) {
        ll::config::saveConfig(*mConfig, getSelf().getConfigDir() / u8"config.json");
    }
    ///////////////////// Update Config ////////////////////////
   for (auto it = mConfig->DimensionNameMap.begin(); it != mConfig->DimensionNameMap.end();) {
       auto oldKey = it->first;
       auto val    = it->second;
       auto newKey = GMLIB::StringUtils::toSnakeCase(oldKey);
       if (oldKey != newKey) {
           it                                = mConfig->DimensionNameMap.erase(it);
           mConfig->DimensionNameMap[newKey] = val;
       } else {
           ++it;
       }
   }
    ll::config::saveConfig(*mConfig, getSelf().getConfigDir() / u8"config.json");
    ////////////////////////////////////////////////////////////
    if (getConfig().ChatLogger.LogToFile) {
        chatLogger.setFile(getConfig().ChatLogger.FilePath);
    }
    registerPAPI();
    listenEvent();
    logger.info("ChatFormatter Loaded!");
    logger.info("Author: GroupMountain");
    logger.info("Repository: https://github.com/GroupMountain/ChatFormatter");
    return true;
}

bool Entry::disable() {
    unregisterPAPI();
    return true;
}

bool Entry::unload() {
    getInstance().reset();
    return true;
}

Config& Entry::getConfig() { return mConfig.value(); }

} // namespace ChatFormatter

LL_REGISTER_PLUGIN(ChatFormatter::Entry, ChatFormatter::Entry::getInstance());
