#pragma once

struct PropReadOnly {};
struct PropWriteOnly {};
struct PropReadWrite {};

template <typename Owner, typename Type, typename Access = PropReadWrite>
class Property {
    using Getter = const Type&(Owner::*)() const;
    using Setter = void (Owner::*)(const Type&);
private:
    Owner* owner;
    Getter methodGet;
    Setter methodSet;

public:
    Property() = delete;
    Property(Owner* const owr, Getter getmethod, Setter setmethod) : owner(owr), methodGet(getmethod), methodSet(setmethod) {}

    inline operator Type() { return (owner->*methodGet)(); }
    inline void operator=(const Type& data) { (owner->*methodSet)(data); }
};

template<typename Owner, typename Type>
class Property<typename Owner, typename Type, PropReadOnly> {
    using Getter = const Type&(Owner::*)() const;
private:
    Owner* owner;
    Getter methodGet;

public:
    Property() = delete;
    inline Property(Owner* const owr, Getter getmethod) : owner(owr), methodGet(getmethod) {}

    inline operator Type() { return (owner->*methodGet)(); }
};

template<typename Owner, typename Type>
class Property<typename Owner, typename Type, PropWriteOnly> {
    using Setter = void (Owner::*)(const Type&);
private:
    Owner* owner;
    Setter methodSet;

public:
    Property() = delete;
    inline Property(Owner* const owr, Setter setmethod) : owner(owr), methodSet(setmethod) {}

    inline void operator=(const Type& data) { (owner->*methodSet)(data); }
};
