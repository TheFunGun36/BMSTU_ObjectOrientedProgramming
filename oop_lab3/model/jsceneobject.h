#pragma once
#include "jvector3d.h"
#include "jangle.h"
#include "property.h"
#include "jtransform.h"
#include "jtransformaction.h"
#include <string>
#include <map>

namespace Jora {

class TransformAction;

using ObjectId = size_t;

class SceneObject : public Printable {
public:
    using SelfPtr = std::shared_ptr<SceneObject>;
    using SelfCPtr = std::shared_ptr<const SceneObject>;
    using SelfRef = SceneObject&;
    using SelfCRef = const SceneObject&;
    using Self = SceneObject;

    SceneObject(const std::string& _label = "Scene object");
    inline virtual ~SceneObject() = default;

    Property<Self, bool> Visible;
    Property<Self, std::string> Label;
    Property<Self, std::type_info, PropReadOnly> Type;
    Property<Self, size_t, PropReadOnly> Id;

    virtual const bool& visible() const noexcept;
    virtual const std::string& label() const noexcept;
    virtual const std::type_info& type() const noexcept;
    virtual const ObjectId& id() const noexcept;
    virtual const Transform& transform() const noexcept;
    virtual Transform& transform() noexcept;

    virtual void setVisible(const bool& _visible) noexcept;
    virtual void setLabel(const std::string& label) noexcept;

    virtual void apply(const TransformAction& action) noexcept;

    // COMPOSITE PART
    using Iterator = std::map<ObjectId, SelfPtr>::iterator;
    using IteratorConst = std::map<ObjectId, SelfPtr>::const_iterator;

    virtual SelfCPtr        operator[](ObjectId id) const noexcept;
    virtual bool            isComposite()           const noexcept;
    virtual bool            contains(ObjectId id)   const noexcept;
    virtual size_t          count()                 const noexcept;
    virtual IteratorConst   begin()                 const noexcept;
    virtual IteratorConst   end()                   const noexcept;
    virtual IteratorConst   cbegin()                const noexcept;
    virtual IteratorConst   cend()                  const noexcept;

    virtual SelfPtr     operator[](ObjectId id)     noexcept;
    virtual bool        remove(ObjectId id)         noexcept;
    virtual bool        remove(IteratorConst it)    noexcept;
    virtual Iterator    begin()                     noexcept;
    virtual Iterator    end()                       noexcept;
    virtual bool insert(const SelfPtr& sceneObject) noexcept;
    virtual void        clear()                     noexcept;

private:
    static ObjectId generateId();

    ObjectId _id;
    bool _visible;
    std::string _label;
    Transform _transform;
};

}
