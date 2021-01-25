#pragma once

using namespace DirectX::SimpleMath;

class Transform
{
public:
    Transform(Vector3 pos= Vector3::Zero, Vector3 rot = Vector3::Zero, Vector3 scl = Vector3::One);

    void Translate(float x, float y, float z);

    void Rotate(float x, float y, float z);

    void Scale(float x, float y, float z);

    Matrix GetModelMatrix();

    void Reset();

    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
};
