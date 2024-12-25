#include "DirectXApp.h"
#include "CubeNode.h"



DirectXApp app;

void DirectXApp::CreateSceneGraph()
{
    SceneGraphPointer sceneGraph = GetSceneGraph();

    // Body
    shared_ptr<CubeNode> body = make_shared<CubeNode>(L"Body", Vector4(0.25f, 0, 0, 1.0f));
    body->SetWorldTransform(Matrix::CreateScale(Vector3(5.0f, 8.0f, 2.5f)) * Matrix::CreateTranslation(Vector3(0.0f, 23.0f, 0.0f)));
    sceneGraph->Add(body);

    // Left Leg
    shared_ptr<CubeNode> leftLeg = make_shared<CubeNode>(L"LeftLeg", Vector4(0.25f, 0, 0, 1.0f));
    leftLeg->SetWorldTransform(Matrix::CreateScale(Vector3(1.0f, 7.5f, 1.0f)) * Matrix::CreateTranslation(Vector3(-4.0f, 7.5f, 0.0f)));
    sceneGraph->Add(leftLeg);

    // Right Leg
    shared_ptr<CubeNode> rightLeg = make_shared<CubeNode>(L"RightLeg", Vector4(0.25f, 0, 0, 1.0f));
    rightLeg->SetWorldTransform(Matrix::CreateScale(Vector3(1.0f, 7.5f, 1.0f)) * Matrix::CreateTranslation(Vector3(4.0f, 7.5f, 0.0f)));
    sceneGraph->Add(rightLeg);

    // Head
    shared_ptr<CubeNode> head = make_shared<CubeNode>(L"Head", Vector4(0, 0.25f, 0, 1.0f));
    head->SetWorldTransform(Matrix::CreateScale(Vector3(3.0f, 3.0f, 3.0f)) * Matrix::CreateTranslation(Vector3(0.0f, 34.0f, 0.0f)));
    sceneGraph->Add(head);

    // Left Arm
    shared_ptr<CubeNode> leftArm = make_shared<CubeNode>(L"LeftArm", Vector4(0, 0, 0.25f, 1.0f));
    leftArm->SetWorldTransform(Matrix::CreateScale(Vector3(1.0f, 8.5f, 1.0f)) * Matrix::CreateTranslation(Vector3(-6.0f, 22.0f, 0.0f)));
    sceneGraph->Add(leftArm);

    // Right Arm
    shared_ptr<CubeNode> rightArm = make_shared<CubeNode>(L"RightArm", Vector4(0, 0, 0.25f, 1.0f));
    rightArm->SetWorldTransform(Matrix::CreateScale(Vector3(1.0f, 8.5f, 1.0f)) * Matrix::CreateTranslation(Vector3(6.0f, 22.0f, 0.0f)));
    sceneGraph->Add(rightArm);

    _rotationAngle = 0;
    _yOffset = 0.0f;
    _isGoingUp = false;
}


void DirectXApp::UpdateSceneGraph()
{
    SceneGraphPointer sceneGraph = GetSceneGraph();

    // Apply rotation to the entire robot
    _rotationAngle += 0.5f;
    Matrix rotationMatrix = Matrix::CreateRotationY(_rotationAngle * XM_PI / 180.0f);
    sceneGraph->SetWorldTransform(rotationMatrix);

    // Define rotation angles for the arms
    float leftArmRotation = sin(_rotationAngle * XM_PI / 180.0f) * 45.0f;  // Swinging left arm
    float rightArmRotation = -sin(_rotationAngle * XM_PI / 180.0f) * 45.0f;  // Swinging right arm

    // Find and update the left arm node
    SceneNodePointer leftArmNode = sceneGraph->Find(L"LeftArm");
    if (leftArmNode) {
        leftArmNode->SetWorldTransform(Matrix::CreateScale(Vector3(1.0f, 8.5f, 1.0f)) * Matrix::CreateTranslation(Vector3(0, -4.25f, 0)) * Matrix::CreateRotationX(leftArmRotation * XM_PI / 180.0f) * Matrix::CreateTranslation(Vector3(-6.0f, 27.0f, 0.0f)));
    }

    // Find and update the right arm node
    SceneNodePointer rightArmNode = sceneGraph->Find(L"RightArm");
    if (rightArmNode) {
        rightArmNode->SetWorldTransform(Matrix::CreateScale(Vector3(1.0f, 8.5f, 1.0f)) * Matrix::CreateTranslation(Vector3(0, -4.25f, 0)) * Matrix::CreateRotationX(rightArmRotation * XM_PI / 180.0f) * Matrix::CreateTranslation(Vector3(6.0f, 27.0f, 0.0f)));
    }
}
