#ifndef CAMERA_H
#define CAMERA_H

#include "Vector4.h"
#include "Matrix4.h"
#include "Vector4.h"

class Camera {
public:
    // Constructor
    Camera();

    // Function to set the view transformation matrix
    void setViewMatrix(const Matrix4& viewMatrix);

    // Function to get the view transformation matrix
    const Matrix4& getViewMatrix() const;

    // Function to set the projection matrix
    void setProjectionMatrix(const Matrix4& projectionMatrix);

    // Function to get the projection matrix
    const Matrix4& getProjectionMatrix() const;

    // Function to set the camera using LookAt
    void lookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

    // Function to set orthogonal projection
    void setOrthogonal(const Vector3& LBN, const Vector3& RTF, float theta, float phi);

    // Function to set perspective projection
    void setPerspective(float fovY, float aspect, float near, float far);

private:
    Matrix4 viewMatrix;
    Matrix4 projectionMatrix;
};

#endif // CAMERA_H
