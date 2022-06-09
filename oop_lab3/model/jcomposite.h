#pragma once
#include "jsceneobject.h"
#include <list>

namespace Jora {

class Composite : public SceneObject {
public:
    using SelfPtr = std::shared_ptr<Composite>;
    using SelfRef = Composite&;
    using SelfCRef = const Composite&;
    using Self = Composite;

    using ElementPtr = std::shared_ptr<SceneObject>;
    using ElementRef = SceneObject&;
    using ElementCRef = const SceneObject&;
    using Element = SceneObject;

    inline Composite(const std::string& label = "Group")
        : SceneObject(label) {
    }
    inline virtual ~Composite() = default;


    virtual SelfCPtr        operator[](ObjectId id)     const noexcept override;
    virtual bool            isComposite()               const noexcept override;
    virtual bool            contains(size_t id)         const noexcept override;
    virtual size_t          count()                     const noexcept override;
    virtual IteratorConst   begin()                     const noexcept override;
    virtual IteratorConst   end()                       const noexcept override;
    virtual IteratorConst   cbegin()                    const noexcept override;
    virtual IteratorConst   cend()                      const noexcept override;

    virtual ElementPtr  operator[](size_t id)                   noexcept override;
    virtual bool        remove(size_t id)                       noexcept override;
    virtual bool        remove(IteratorConst it)                noexcept override;
    virtual Iterator    begin()                                 noexcept override;
    virtual Iterator    end()                                   noexcept override;
    virtual bool        insert(const ElementPtr& sceneObject)   noexcept override;

protected:
    virtual std::ostream& addToStream(std::ostream& stream) const;
    virtual std::wostream& addToStream(std::wostream& stream) const;

private:
    std::map<size_t, ElementPtr> _map;
};

}