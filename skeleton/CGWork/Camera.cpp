#include "Camera.h"
#include <cmath>

// Constructor
Camera::Camera() : viewMatrix(Matrix4::identity()), projectionMatrix(Matrix4::identity()) {
    setOrthogonal(Vector3(-1,1,0), Vector3(1, -1, 2), 0, 0);
    lookAt(Vector3(0, 0, -1), Vector3(0, 0, 0), Vector3(0,-1,0));
    setOrthogonal(Vector3(-1,1,0), Vector3(1, -1, 2), 0, 0);
    lookAt(Vector3(0, 0, -1), Vector3(0, 0, 0), Vector3(0,1,0));
}

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
void Camera::lookAt(const Vector3& eye, const Vector3& target, const Vector3& up) {
    const Vector3 zAxis = (eye - target).normalized();
    const Vector3 xAxis = Vector3::cross(zAxis,up ).normalized();
    const Vector3 yAxis = Vector3::cross(xAxis,zAxis);

    orientation = Matrix4(
        xAxis.x, xAxis.y, xAxis.z, 0,
        yAxis.x, yAxis.y, yAxis.z, 0,
        zAxis.x, zAxis.y, zAxis.z, 0,
        0, 0, 0, 1
    );

    translation = Matrix4::translate(-eye);
  //  translation_inv = translation.inverse();
    viewMatrix = orientation * translation;
}

// Function to set orthogonal projection
void Camera::setOrthogonal(const Vector3& LBN, const Vector3& RTF,float theta, float phi) {
 //   const Vector3 translationVector = Vector3::scaling(LBN+RTF, -0.5, -0.5, 0.5);
 //   const Vector3 scaleVector = Vector3(2/(RTF.x - LBN.x), 2/(RTF.y - LBN.y), 2/(LBN.z - RTF.z));
 ////   const Matrix4 Morth = Matrix4(Vector4::unitX(), Vector4::unitY(), Vector4::zero(), Vector4::unitW());
 //   theta = theta == 0 ? 0 : -1 / tan(theta);
 //   phi = phi == 0 ? 0 : -1 / tan(phi);
 //   const Matrix4 Hshear = Matrix4(Vector4::unitX(), Vector4::unitY(), Vector4( theta, phi, 1, 0), Vector4::unitW());
 //   projectionMatrix = Matrix4::scaling(scaleVector) * Matrix4::translate(translationVector) * Hshear;
    float left = LBN.x;
    float bottom = LBN.y;
    float near = LBN.z;
    float right = RTF.x;
    float top = RTF.y;
    float far = RTF.z;

    // Orthogonal projection matrix
    projectionMatrix=Matrix4 (
        (2.0f / (right - left)), 0, 0, - (right + left) / (right - left),
        0, 2.0f / (top - bottom), -(top + bottom) / (top - bottom), 0,
        0, 0, -2.0f / (far - near), -(far + near) / (far - near),
        0, 0, 0, 1.0f);

}

// Function to set perspective projection
void Camera::setPerspective(float fovY, float aspect, float near, float far) {
    //not sure about the tanHalfFovY and and aspect usage
    const float tanHalfFovY = tan(fovY / 2);
    double a = (near + far) / (far - near);
    double b = ((2 * near) * far)/(near - far);
    projectionMatrix = Matrix4(
        1 / (aspect * tanHalfFovY), 0, 0, 0,
        0, 1 / tanHalfFovY, 0, 0,
        0, 0, a, b, 
        0, 0, -1, 0
    );
}

void Camera::orientate(const Matrix4& tMat) {
    orientation = orientation * tMat;
    this->viewMatrix = orientation * translation;
}

void Camera::translate(const Matrix4& tMat) {
    this->viewMatrix = tMat * this->viewMatrix;
}

