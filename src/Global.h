#pragma once

#include "Entry.h"

#include "ll/api/io/LoggerRegistry.h"

namespace ChatFormatter {

inline auto& logger = Entry::getInstance().getSelf().getLogger();

static auto chatLogger = ll::io::LoggerRegistry::getInstance().getOrCreate("Chat");

extern void listenEvent();
extern void registerPAPI();
extern void unregisterPAPI();

} // namespace ChatFormatter