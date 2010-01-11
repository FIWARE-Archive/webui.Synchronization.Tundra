/// @file Environment.h
/// @brief Manages environment-related reX-logic, e.g. world time and lightning.
/// For conditions of distribution and use, see copyright notice in license.txt

#ifndef incl_RexLogicModule_Environment_h
#define incl_RexLogicModule_Environment_h

#include <Foundation.h>
#include <RexTypes.h>
#include "EnvironmentModuleApi.h"
#include <QVector>
#include <QObject>

namespace ProtocolUtilities
{
    class NetworkEventInboundData;
}


namespace OgreRenderer
{
    class EC_OgreEnvironment;
}

namespace Environment
{
    class EnvironmentModule;

    class ENVIRONMENT_MODULE_API Environment : public QObject
    {
        Q_OBJECT

    public:
        
        /** 
         * Overloaded constructor.
         * @param owner The owner module.
         **/
        Environment(EnvironmentModule *owner);
        virtual ~Environment();

        /**
         * @return The scene entity that represents the environment in the currently active world.        
         **/
        Scene::EntityWeakPtr GetEnvironmentEntity();

        /**
         * @return Enviroment entity component, or 0 if does not exist
         **/
        OgreRenderer::EC_OgreEnvironment* GetEnvironmentComponent();

        /**
         * Creates the environment EC to current active scene and adjust it using default parameters.
         **/
        void CreateEnvironment();

        /**
         * Handles the "SimulatorViewerTimeMessage" packet.
         * @param data The network event data pointer.
         **/
        bool HandleSimulatorViewerTimeMessage(ProtocolUtilities::NetworkEventInboundData* data);

        /** 
         * Sets a water fog for current active environment.
         * @param fogStart distance in world unit at which linear fog start ot encroach. 
         * @param fogEnd distance in world units at which linear fog becomes completely opaque.
         * @param color the colour of the fog. 
         **/
        void SetWaterFog(float fogStart, float fogEnd, const QVector<float>& color);
 
        /** 
         * Sets a ground fog for current active environment.
         * @param fogStart distance in world unit at which linear fog start ot encroach. 
         * @param fogEnd distance in world units at which linear fog becomes completely opaque.
         * @param color the colour of the fog. 
         **/

        void SetGroundFog(float fogStart, float fogEnd, const QVector<float>& color);

        /**
         * Enables or disables fog color override. 
         * @param enabled boolean defines state of override.
         **/
         
        void SetFogColorOverride(bool enabled);
        
        /**
         * Returns information is fog color controlled by user or caelum.
         * @return true if it is fog color is controlled by user, else false.
         **/
        
        bool GetFogColorOverride();
 
        void SetGroundFogColor(const QVector<float>& color);
        
        void SetWaterFogColor(const QVector<float>& color);

        void SetGroundFogDistance(float fogStart, float fogEnd);

        void SetWaterFogDistance(float fogStart, float fogEnd);

        float GetWaterFogStartDistance();
        float GetWaterFogEndDistance();
        float GetGroundFogStartDistance();
        float GetGroundFogEndDistance();

     

        /**
         * Returns current fog ground color. 
         */
        QVector<float> GetFogGroundColor();
        
        /** 
         * Returns current fog water color.
         **/
        QVector<float> GetFogWaterColor();

        /**
         * Updates the visual effects (fog, skybox etc).
         **/
        void Update(f64 frametime);

        /**
         * @return true if caelum library is used.
         **/
        bool IsCaelum();

        //! Set server time override
        void SetTimeOverride(bool enabled) { time_override_ = enabled; }      

        void SetSunDirection(const QVector<float>& vector);
        QVector<float> GetSunDirection();

        void SetSunColor(const QVector<float>& vector);
        QVector<float> GetSunColor();

        QVector<float> GetAmbientLight();
        void SetAmbientLight(const QVector<float>& vector);

        
        template<typename T> QVector<T> ConvertToQVector(const StringVector& vector) 
        {
            int elements = vector.size();
            QVector<T> vec(elements);
            try
            {
                for ( int i = 0; i < elements; ++i)
                    vec[i] = boost::lexical_cast<T>(vector[i]);
            }
            catch ( boost::bad_lexical_cast&)
            {
                return QVector<T>(0);
            }

            return vec;
        }
     
    signals:
        
         void WaterFogAdjusted(float fogStart, float fogEnd, const QVector<float>& color);
         void GroundFogAdjusted(float fogStart, float fogEnd, const QVector<float>& color);

    private:
       
        /// Creates the global sunlight.
        void CreateGlobalLight();

        /// Pointer to the environment module which owns this class.
        EnvironmentModule *owner_;

        /// Weak pointer to the entity which has the environment component.
        Scene::EntityWeakPtr activeEnvEntity_;

        /// Time override, default false
        bool time_override_;

        /// Server's perception of time (UNIX EPOCH).
        time_t usecSinceStart_;

        /// Unknown/not needed. \todo delete?
        uint32_t secPerDay_;

        /// Unknown/not needed. \todo delete?
        uint32_t secPerYear_;

        /// Direction of the sunlight.
        RexTypes::Vector3 sunDirection_;

        /// Unknown/not needed. \todo delete?
        float sunPhase_;

        /// Sun's angle velocity.
        RexTypes::Vector3 sunAngVelocity_;
    };
}

#endif
