// For conditions of distribution and use, see copyright notice in license.txt

#include "StableHeaders.h"
#include "DebugOperatorNew.h"

#include "EntityReference.h"
#include "Entity.h"
#include "SceneManager.h"
#include "EC_Name.h"
#include "SceneAPI.h"

#include "Framework.h"
#include "IComponent.h"
#include "CoreStringUtils.h"
#include "LoggingFunctions.h"

#include "MemoryLeakCheck.h"

void EntityReference::Set(Entity* entity)
{
    QString name = entity->GetName();
    SceneManager* scene = entity->GetScene();
    if (!scene)
    {
        // If entity is not in scene, set directly by ID
        ref = QString::number(entity->GetId());
        return;
    }
    if (scene->IsUniqueName(name))
        ref = name;
    else
        ref = QString::number(entity->GetId());
}

bool EntityReference::IsEmpty() const
{
    bool ok = false;
    entity_id_t id = ref.toInt(&ok);
    // ID 0 can not be an entity
    if ((ok) && (id == 0))
        return true;
    if (ref.trimmed().isEmpty())
        return true;
    
    return false;
}

EntityPtr EntityReference::Lookup(SceneManager* scene) const
{
    if (!scene)
        return EntityPtr();
    // If ref looks like an ID, lookup by ID first
    bool ok = false;
    entity_id_t id = ref.toInt(&ok);
    if (ok)
    {
        EntityPtr entity = scene->GetEntity(id);
        if (entity)
            return entity;
    }
    // Then get by name
    return scene->GetEntityByName(ref.trimmed());
}
