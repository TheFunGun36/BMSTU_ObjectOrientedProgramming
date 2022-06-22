#pragma once
#include "jtransform.h"
namespace Jora {

class TransformAction {
public:
    virtual void apply(Transform& transform) const noexcept = 0;
    virtual ~TransformAction() = default;
};

class TransformMove : public TransformAction {
public:
    TransformMove(const Vector3D& shift = Vector3D())
        : _shift(shift) {
    }

    virtual inline const Vector3D& shift() const { return _shift; }
    virtual inline Vector3D& shift() { return _shift; }
    virtual inline void setShift(const Vector3D& value) { _shift = value; }

    virtual void apply(Transform& transform) const noexcept override {
        transform.position() += _shift;
    }

private:
    Vector3D _shift;
};

class TransformRotate : public TransformAction {
public:
    TransformRotate(const EulerAngles& angles = EulerAngles())
        : _angles(angles) {
    }

    virtual inline const EulerAngles& angles() const { return _angles; }
    virtual inline EulerAngles& angles() { return _angles; }
    virtual inline void setAngles(const EulerAngles& value) { _angles = value; }

    virtual void apply(Transform& transform) const noexcept override {
        transform.rotation() += _angles;
    }

private:
    EulerAngles _angles;
};

class TransformScale : public TransformAction {
public:
    TransformScale(const Vector3D& scale = Vector3D())
        : _scale(scale) {
    }

    virtual inline const Vector3D& scale() const { return _scale; }
    virtual inline Vector3D& scale() { return _scale; }
    virtual inline void setScale(const Vector3D& value) { _scale = value; }

    virtual void apply(Transform& transform) const noexcept override {
        //transform.scale() *= _scale;
        for (int i = 0; i < 3; i++) {
            transform.scale()[i] *= _scale[i];
        }
    }

private:
    Vector3D _scale;
};

class TransformSet : public TransformAction {
public:
    TransformSet(const Vector3D& position = Vector3D(),
        const EulerAngles& rotation = EulerAngles(),
        const Vector3D& scale = Vector3D(1., 1., 1.)) {
    }

    virtual inline const Vector3D& position() const { return _position; }
    virtual inline Vector3D& position() { return _position; }
    virtual inline void setPosition(const Vector3D& value) { _position = value; }

    virtual inline const EulerAngles& rotation() const { return _rotation; }
    virtual inline EulerAngles& rotation() { return _rotation; }
    virtual inline void setRotation(const EulerAngles& value) { _rotation = value; }

    virtual inline const Vector3D& scale() const { return _scale; }
    virtual inline Vector3D& scale() { return _scale; }
    virtual inline void setScale(const Vector3D& value) { _scale = value; }
    
    virtual void apply(Transform& transform) const noexcept override {
        transform.position() = _position;
        transform.rotation() = _rotation;
        transform.scale() = _scale;
    }

private:
    Vector3D _position;
    EulerAngles _rotation;
    Vector3D _scale;
};

}
