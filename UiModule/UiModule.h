// For conditions of distribution and use, see copyright notice in license.txt

#ifndef incl_UiModule_UiModule_h
#define incl_UiModule_UiModule_h

#include "Foundation.h"
#include "ModuleInterface.h"
#include "UiModuleApi.h"

// UiModule Service includes
#include "UiSceneManager.h"
#include "UiNotificationManager.h"

#include <QStringList>
#include <QMap>

namespace OgreRenderer
{
    class QOgreUIView;
}

namespace UiServices
{
    class UiProxyWidget;
    class UiWidgetProperties;

    /** UiModule hadles the shown ui scene, creates 
      * core modules ui and provides ui services to modules 
      */

    class UI_MODULE_API UiModule : public Foundation::ModuleInterfaceImpl
    {
    public:
        UiModule();
        ~UiModule();

        /*************** ModuleInterfaceImpl ***************/
        void Load();
        void Unload();
        void Initialize();
        void Uninitialize();
        void Update(f64 frametime);
        bool HandleEvent(event_category_id_t category_id, event_id_t event_id, Foundation::EventDataInterface* data);

        /*************** UiModule Services ***************/

        //! UiSceneManager will give you a QObject derived class that will give you all
        //! the UI related services like adding your own QWidgets into the 2D scene 
        //! \return UiSceneManager The scene manager with scene services
        UiServices::UiSceneManager *GetSceneManager() const { return ui_scene_manager_; }

        UiServices::UiNotificationManager *GetNotificationManager() const { return ui_notification_manager_; }

        /*************** Logging ***************/

        MODULE_LOGGING_FUNCTIONS;
        //! Returns name of this module. Needed for logging.
        static const std::string &NameStatic() { return Foundation::Module::NameFromType(type_static_); }

        //! Returns type of this module. Needed for logging.
        static const Foundation::Module::Type type_static_ = Foundation::Module::MT_UiServices;

    private:

        //! Get all the category id:s of categories in eventQueryCategories
        void SubscribeToEventCategories();

        //! Current query categories
        QStringList event_query_categories_;

        //! Current subscribed category events
        QMap<QString, event_category_id_t> service_category_identifiers_;

        //! Pointer to the QOgre UiView
        QGraphicsView *ui_view_;

        //! UiSceneManager pointer
        UiSceneManager *ui_scene_manager_;

        //! UiNotificationManager pointer
        UiNotificationManager *ui_notification_manager_;

        QString current_avatar_;
        QString current_server_;
    };
}

#endif // incl_UiModule_UiModule_h
