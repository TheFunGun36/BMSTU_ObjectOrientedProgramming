#pragma once
#include "jsceneobject.h"
#include <list>

namespace Jora {

class Composite : public SceneObject {
public:
    using ElementPtr = std::shared_ptr<SceneObject>;
    using Element = SceneObject;

    inline virtual ~Composite() = default;

    using Iterator = std::list<ElementPtr>::iterator;
    using IteratorConst = std::list<ElementPtr>::const_iterator;

    inline virtual bool isComposite() const { return false; }

    inline virtual bool add(const ElementPtr& sceneObject) { _list.push_back(sceneObject); return true; }
    inline virtual bool remove(IteratorConst it) { _list.erase(it, it); return true; }
    inline virtual size_t count() { return _list.size(); }
    inline virtual Iterator begin() { return _list.begin(); }
    inline virtual Iterator end() { return _list.end(); }
    inline virtual IteratorConst begin() const { return _list.begin(); }
    inline virtual IteratorConst end() const { return _list.end(); }
    inline virtual IteratorConst cbegin() const { return _list.cbegin(); }
    inline virtual IteratorConst cend() const { return _list.cend(); }

protected:
    virtual std::ostream& addToStream(std::ostream& stream) const;
    virtual std::wostream& addToStream(std::wostream& stream) const;

private:
    std::list<ElementPtr> _list;
};

}