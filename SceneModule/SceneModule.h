// For conditions of distribution and use, see copyright notice in license.txt

#ifndef incl_SceneModule_h
#define incl_SceneModule_h

#include "ModuleInterface.h"
#include "SceneManager.h"

namespace Foundation
{
    class Framework;
}

namespace Scene
{
    //! interface for modules
    class SceneModule : public Foundation::ModuleInterface_Impl
    {
    public:
        SceneModule();
        virtual ~SceneModule();

        virtual void Load();
        virtual void Unload();
        virtual void Initialize(Foundation::Framework *framework);
        virtual void Uninitialize(Foundation::Framework *framework);

        virtual void Update();

        MODULE_LOGGING_FUNCTIONS

        //! returns name of this module. Needed for logging.
        static const std::string &NameStatic() { return Foundation::Module::NameFromType(type_static_); }

        static const Foundation::Module::Type type_static_ = Foundation::Module::Type_Scene;

    private:
        Foundation::SceneManagerPtr scene_manager_;
    };
}

#endif
