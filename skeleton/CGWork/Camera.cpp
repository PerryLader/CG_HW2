#include "Camera.h"
#include <cmath>

// Constructor
Camera::Camera() : viewMatrix(Matrix4::identity()), projectionMatrix(Matrix4::identity()) {}

// Function to set the view transformation matrix
void Camera::setViewMatrix(const Matrix4& viewMatrix) {
    this->viewMatrix = viewMatrix;
}

// Function to get the view transformation matrix
const Matrix4& Camera::getViewMatrix() const {
    return viewMatrix;
}

// Function to set the projection matrix
void Camera::setProjectionMatrix(const Matrix4& projectionMatrix) {
    this->projectionMatrix = projectionMatrix;
}

// Function to get the projection matrix
const Matrix4& Camera::getProjectionMatrix() const {
    return projectionMatrix;
}

// Function to set the camera using LookAt
void Camera::lookAt(const Vector4& eye, const Vector4& target, const Vector4& up) {
    Vector4 zAxis = (eye - target).normalized();
    Vector4 xAxis = up.cross(zAxis).normalized();
    Vector4 yAxis = zAxis.cross(xAxis);

    Matrix4 orientation(
        xAxis.x, xAxis.y, xAxis.z, 0,
        yAxis.x, yAxis.y, yAxis.z, 0,
        zAxis.x, zAxis.y, zAxis.z, 0,
        0, 0, 0, 1
    );

    Matrix4 translation(
        1, 0, 0, -eye.x,
        0, 1, 0, -eye.y,
        0, 0, 1, -eye.z,
        0, 0, 0, 1
    );

    viewMatrix = orientation * translation;
}

// Function to set orthogonal projection
void Camera::setOrthogonal(float left, float right, float bottom, float top, float near, float far) {
    projectionMatrix = Matrix4(
        2 / (right - left), 0, 0, -(right + left) / (right - left),
        0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom),
        0, 0, -2 / (far - near), -(far + near) / (far - near),
        0, 0, 0, 1
    );
}

// Function to set perspective projection
void Camera::setPerspective(float fovY, float aspect, float near, float far) {
    float tanHalfFovY = tan(fovY / 2);
    projectionMatrix = Matrix4(
        1 / (aspect * tanHalfFovY), 0, 0, 0,
        0, 1 / tanHalfFovY, 0, 0,
        0, 0, -(far + near) / (far - near), -2 * far * near / (far - near),
        0, 0, -1, 0
    );
}
