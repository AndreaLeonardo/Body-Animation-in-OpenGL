//
// Created by Andrea Leonardo on 13/07/22.
//

#ifndef CGPROJECT_SKINNINGDEBUG_H
#define CGPROJECT_SKINNINGDEBUG_H

#include "debug_skinning_technique.h"

class SkinningDebug
{
public:
    SkinningDebug();
    ~SkinningDebug();

    bool Init();

    void RenderSceneCB();
    void KeyboardCB(unsigned char key, int mouse_x, int mouse_y);
    void SpecialKeyboardCB(int key, int mouse_x, int mouse_y);
    void PassiveMouseCB(int x, int y);

private:
    GLuint WVPLocation;
    GLuint SamplerLocation;
    Camera* pGameCamera = NULL;
    SkinnedMesh* pMesh1 = NULL;
    PersProjInfo persProjInfo;
    DebugSkinningTechnique* pSkinningTech = NULL;
    PointLight pointLights[SkinningTechnique::MAX_POINT_LIGHTS];
    SpotLight spotLights[SkinningTechnique::MAX_SPOT_LIGHTS];
    long long StartTime = 0;
    int DisplayBoneIndex = 0;
};


SkinningDebug::SkinningDebug()
{
    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    float FOV = 45.0f;
    float zNear = 0.1f;
    float zFar = 100.0f;

    persProjInfo = { FOV, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, zNear, zFar };

    pointLights[0].AmbientIntensity = 1.0f;
    pointLights[0].DiffuseIntensity = 1.0f;
    pointLights[0].Color = Vector3f(1.0f, 1.0f, 0.0f);
    pointLights[0].Attenuation.Linear = 0.0f;
    pointLights[0].Attenuation.Exp = 0.0f;

    pointLights[1].DiffuseIntensity = 0.0f;
    pointLights[1].Color = Vector3f(0.0f, 1.0f, 1.0f);
    pointLights[1].Attenuation.Linear = 0.0f;
    pointLights[1].Attenuation.Exp = 0.2f;

    spotLights[0].DiffuseIntensity = 1.0f;
    spotLights[0].Color = Vector3f(1.0f, 1.0f, 1.0f);
    spotLights[0].Attenuation.Linear = 0.01f;
    spotLights[0].Cutoff = 20.0f;

    spotLights[1].DiffuseIntensity = 1.0f;
    spotLights[1].Color = Vector3f(1.0f, 1.0f, 0.0f);
    spotLights[1].Attenuation.Linear = 0.01f;
    spotLights[1].Cutoff = 30.0f;
}
SkinningDebug::~SkinningDebug()
{
    if (pGameCamera) {
        delete pGameCamera;
    }

    if (pMesh1) {
        delete pMesh1;
    }
}
bool SkinningDebug::Init()
{
    Vector3f CameraPos(0.0f, 5.0f, -8.0f);
    Vector3f CameraTarget(0.0f, -0.5f, 1.0f);
    Vector3f CameraUp(0.0f, 1.0f, 0.0f);

    pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, CameraPos, CameraTarget, CameraUp);

    pMesh1 = new SkinnedMesh();

    if (!pMesh1->LoadMesh("link/model/body/c00/link+.md5mesh")) {
        printf("Mesh load failed\n");
        return false;
    }

    pMesh1->printBoneMap();

    pSkinningTech = new DebugSkinningTechnique();

    if (!pSkinningTech->Init())
    {
        return false;
    }

    pSkinningTech->Enable();

    pSkinningTech->SetTextureUnit(COLOR_TEXTURE_UNIT_INDEX);
    pSkinningTech->SetSpecularExponentTextureUnit(SPECULAR_EXPONENT_UNIT_INDEX);
    pSkinningTech->SetDisplayBoneIndex(DisplayBoneIndex);

    StartTime = GetCurrentTimeMillis();

    return true;
}
void SkinningDebug::RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
            ;
    pGameCamera->OnRender();

    WorldTrans& worldTransform = pMesh1->GetWorldTransform();

    worldTransform.SetRotation(-90.0f, 180.0f, 0.0f);
    worldTransform.SetPosition(0.0f, 0.0f, 10.0f);
    worldTransform.SetScale(1.0f);

    Matrix4f World = worldTransform.GetMatrix();
    Matrix4f View = pGameCamera->GetMatrix();
    Matrix4f Projection;
    Projection.InitPersProjTransform(persProjInfo);
    Matrix4f WVP = Projection * View * World;
    pSkinningTech->SetWVP(WVP);

    pointLights[0].WorldPosition.x = 0.0f;
    pointLights[0].WorldPosition.y = 1.0;
    pointLights[0].WorldPosition.z = 1.0f;
    pointLights[0].CalcLocalPosition(worldTransform);

    pointLights[1].WorldPosition.x = 10.0f;
    pointLights[1].WorldPosition.y = 1.0f;
    pointLights[1].WorldPosition.z = 0.0f;
    pointLights[1].CalcLocalPosition(worldTransform);

    pSkinningTech->SetPointLights(2, pointLights);

    spotLights[0].WorldPosition = pGameCamera->GetPos();
    spotLights[0].WorldDirection = pGameCamera->GetTarget();
    spotLights[0].CalcLocalDirectionAndPosition(worldTransform);

    spotLights[1].WorldPosition = Vector3f(0.0f, 1.0f, 0.0f);
    spotLights[1].WorldDirection = Vector3f(0.0f, -1.0f, 0.0f);
    spotLights[1].CalcLocalDirectionAndPosition(worldTransform);

    pSkinningTech->SetSpotLights(2, spotLights);

    pSkinningTech->SetMaterial(pMesh1->GetMaterial());

    Vector3f CameraLocalPos3f = worldTransform.WorldPosToLocalPos(pGameCamera->GetPos());
    pSkinningTech->SetCameraLocalPos(CameraLocalPos3f);

    long long CurrentTime = GetCurrentTimeMillis();

    pMesh1->Render();

    glutPostRedisplay();
    glutSwapBuffers();
}

#define ATTEN_STEP 0.01f

#define ANGLE_STEP 1.0f

void SkinningDebug::KeyboardCB(unsigned char key, int mouse_x, int mouse_y)
{
    switch (key) {
        case 'q':
        case 27:    // escape key code
            exit(0);

        case ' ':
            DisplayBoneIndex++;
            DisplayBoneIndex = DisplayBoneIndex % pMesh1->NumBones();
            std::cout<<"BONE "<<DisplayBoneIndex<<"!"<<std::endl;
            pSkinningTech->SetDisplayBoneIndex(DisplayBoneIndex);
            break;

        case 'a':
            pointLights[0].Attenuation.Linear += ATTEN_STEP;
            pointLights[1].Attenuation.Linear += ATTEN_STEP;
            break;

        case 'z':
            pointLights[0].Attenuation.Linear -= ATTEN_STEP;
            pointLights[1].Attenuation.Linear -= ATTEN_STEP;
            break;

        case 's':
            pointLights[0].Attenuation.Exp += ATTEN_STEP;
            pointLights[1].Attenuation.Exp += ATTEN_STEP;
            break;

        case 'x':
            pointLights[0].Attenuation.Exp -= ATTEN_STEP;
            pointLights[1].Attenuation.Exp -= ATTEN_STEP;
            break;

        case 'd':
            spotLights[0].Cutoff += ANGLE_STEP;
            break;

        case 'c':
            spotLights[0].Cutoff -= ANGLE_STEP;
            break;

        case 'g':
            spotLights[1].Cutoff += ANGLE_STEP;
            break;

        case 'b':
            spotLights[1].Cutoff -= ANGLE_STEP;
            break;

    }

    pGameCamera->OnKeyboard(key);
}
void SkinningDebug::SpecialKeyboardCB(int key, int mouse_x, int mouse_y) {
    pGameCamera->OnKeyboard(key);
}
void SkinningDebug::PassiveMouseCB(int x, int y)
{
    pGameCamera->OnMouse(x, y);
}

SkinningDebug* pSkinningDebug = NULL;

void dRenderSceneCB()
{
    pSkinningDebug->RenderSceneCB();
}
void dKeyboardCB(unsigned char key, int mouse_x, int mouse_y)
{
    pSkinningDebug->KeyboardCB(key, mouse_x, mouse_y);
}
void dSpecialKeyboardCB(int key, int mouse_x, int mouse_y)
{
    pSkinningDebug->SpecialKeyboardCB(key, mouse_x, mouse_y);
}
void dPassiveMouseCB(int x, int y)
{
    pSkinningDebug->PassiveMouseCB(x, y);
}

void dInitializeGlutCallbacks()
{
    glutDisplayFunc(dRenderSceneCB);
    glutKeyboardFunc(dKeyboardCB);
    glutSpecialFunc(dSpecialKeyboardCB);
    glutPassiveMotionFunc(dPassiveMouseCB);
}


#endif //CGPROJECT_SKINNINGDEBUG_H
