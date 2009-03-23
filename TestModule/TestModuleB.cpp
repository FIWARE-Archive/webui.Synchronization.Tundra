// For conditions of distribution and use, see copyright notice in license.txt

#include "StableHeaders.h"

#include "TestModuleB.h"
#include "TestModule.h"
#include <Poco/ClassLibrary.h>


namespace Test
{
    TestModuleB::TestModuleB() : ModuleInterface_Impl(NameStatic())
    {
    }

    TestModuleB::~TestModuleB()
    {
    }

    // virtual
    void TestModuleB::Load()
    {
        LogInfo("Module " + Name() + " loaded.");
    }

    // virtual
    void TestModuleB::Unload()
    {
        LogInfo("Module " + Name() + " unloaded.");
    }

    // virtual
    void TestModuleB::Initialize(Foundation::Framework *framework)
    {
        assert(framework != NULL);
        framework_ = framework;
        
        LogInfo("Module " + Name() + " initialized.");
    }


    // virtual 
    void TestModuleB::Uninitialize(Foundation::Framework *framework)
    {
        assert(framework_ != NULL);
        framework_ = NULL;

        framework->GetEventManager()->UnregisterEventSubscriber(this);
        
        LogInfo("Module " + Name() + " uninitialized.");
    }

    // virtual
    void TestModuleB::PostInitialize(Foundation::Framework *framework)
    {
        framework->GetEventManager()->RegisterEventSubscriber(this, 0, NULL);
    }

    // virtual
    void TestModuleB::Update()
    {
        Foundation::TestServiceInterface *test_service = NULL;
        try
        {
            test_service = framework_->GetServiceManager()->GetService<Foundation::TestServiceInterface>(Foundation::Service::ST_Test);
        } catch (std::exception)
        {
            return;
        }
        assert (test_service != NULL);
        assert (test_service->Test());
    }

    // virtual
    bool TestModuleB::HandleEvent(Core::event_category_id_t category_id, Core::event_id_t event_id, Foundation::EventDataInterface* data)
    {
        if (framework_->GetEventManager()->QueryEventCategory("Test") == category_id)
        {
            assert (event_id == 0 || event_id == 1 && "Event id mismatch.");

            if (data)
            {
                TestEvent *event_data = dynamic_cast<TestEvent*>(data);
                assert (event_id == 1 || event_data == NULL);
                assert (event_id == 0 || event_data != NULL);
                if (event_id == 1)
                {
                    assert (event_data->test_value_ == 12345);
                }
            }

            return true;
        }
        return false;
    }
}

