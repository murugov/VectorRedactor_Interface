#include "Core/ApplicationCore.hpp"
#include <dlfcn.h>
#include <string>
#include <vector>

int main()
{
    const std::vector<std::string> packages_to_load = {"./Renderer.dylib", "./UIWi.dylib", "./MainPlugin.dylib"};

    Vectoria::ApplicationCore& app = Vectoria::ApplicationCore::instance();
    Vectoria::ApplicationCore::Error error = Vectoria::ApplicationCore::Error::SUCCESS;

    for (const auto& package : packages_to_load)
    {
        if ((error = app.loadPackage(package)) != Vectoria::ApplicationCore::Error::SUCCESS)
        {
            Vectoria::ApplicationCore::log(Vectoria::ApplicationCore::LogLevel::CRITICAL, "%s", Vectoria::ApplicationCore::strError(error));
            if (error == Vectoria::ApplicationCore::Error::PACKAGE_NOT_FOUND)
            {
                Vectoria::ApplicationCore::log(Vectoria::ApplicationCore::LogLevel::CRITICAL, "dlerror = %s", dlerror());
            }
            return 1;
        }
    }

    if ((error = app.run()) != Vectoria::ApplicationCore::Error::SUCCESS)
    {
        Vectoria::ApplicationCore::log(Vectoria::ApplicationCore::LogLevel::ERROR, "Application exited with error %s",
                             Vectoria::ApplicationCore::strError(error));
        return 1;
    }

    Vectoria::ApplicationCore::log(Vectoria::ApplicationCore::LogLevel::OK, "Application successfully stopped");
    return 0;
}
