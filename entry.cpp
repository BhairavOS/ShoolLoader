#include <kapalaframe-logger/logger.h>
#include <kapalaframe-sys/entry.h>
#include <kapalaframe-sys/file.h>

#include "loader.h"

Async::Task<> entryPointAsync(Sys::Context& ctx) {
    logInfo("shoolLoader " stringify$(__ck_version_value));

    logInfo("loading configs...");
    auto file = co_try$(Sys::File::open("file:/boot/loader.json"_url));

    logInfo("parsing configs...");
    auto fileStr = co_try$(Io::readAllUtf8(file));
    auto json = co_try$(Json::parse(fileStr));

    logInfo("validating configs...");
    logInfo("configs: {}", json);

    auto configs = co_try$(ShoolLoader::Configs::fromJson(json));

    if (configs.entries.len() > 1 or configs.entries.len() == 0)
        co_return co_await ShoolLoader::showMenuAsync(ctx, configs);

    co_return ShoolLoader::loadEntry(configs.entries[0]);
}
