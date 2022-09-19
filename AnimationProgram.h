//
// Created by Andrea Leonardo on 12/07/22.
//

#ifndef CGPROJECT_ANIMATIONPROGRAM_H
#define CGPROJECT_ANIMATIONPROGRAM_H

class AnimationProgram
{
public:
    AnimationProgram();
    ~AnimationProgram();

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
    SkinningTechnique* pSkinningTech = NULL;
    PointLight pointLights[SkinningTechnique::MAX_POINT_LIGHTS];
    SpotLight spotLights[SkinningTechnique::MAX_SPOT_LIGHTS];
    long long StartTimeMillis = 0;
};


AnimationProgram::AnimationProgram()
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


AnimationProgram::~AnimationProgram()
{
    if (pGameCamera) {
        delete pGameCamera;
    }

    if (pMesh1) {
        delete pMesh1;
    }
}


bool AnimationProgram::Init()
{
    Vector3f CameraPos(0.0f, 0.0f, 0.0f);
    Vector3f CameraTarget(0.0f, 0.0f, 1.0f);
    Vector3f CameraUp(0.0f, 1.0f, 0.0f);

    pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, CameraPos, CameraTarget, CameraUp);

    pMesh1 = new SkinnedMesh();

    if (!pMesh1->LoadMesh("link/model/body/c00/link+.md5mesh")) {
        printf("Mesh load failed\n");
        return false;
    }



    pSkinningTech = new SkinningTechnique();

    if (!pSkinningTech->Init())
    {
        return false;
    }

    pSkinningTech->Enable();

    pSkinningTech->SetTextureUnit(COLOR_TEXTURE_UNIT_INDEX);
    pSkinningTech->SetSpecularExponentTextureUnit(SPECULAR_EXPONENT_UNIT_INDEX);

    StartTimeMillis = GetCurrentTimeMillis();

    return true;
}


void AnimationProgram::RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
            ;
    pGameCamera->OnRender();

    WorldTrans& worldTransform = pMesh1->GetWorldTransform();

    worldTransform.SetRotation(90.0f, 0.0f, 180.0f);
    worldTransform.SetPosition(0.0f, 0.5f, 25.0f);
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

    long long CurrentTimeMillis = GetCurrentTimeMillis();
    float AnimationTimeSec = ((float)(CurrentTimeMillis - StartTimeMillis)) / 1000.0f;

    vector<Matrix4f> Transforms;
    pMesh1->GetBoneTransforms(AnimationTimeSec, Transforms);

    for (uint i = 0 ; i < Transforms.size() ; i++) {
        pSkinningTech->SetBoneTransform(i, Transforms[i]);
    }

    pMesh1->Render();

    glutPostRedisplay();
    glutSwapBuffers();
}


#define ATTEN_STEP 0.01f

#define ANGLE_STEP 1.0f

void AnimationProgram::KeyboardCB(unsigned char key, int mouse_x, int mouse_y)
{
    switch (key) {
        case 'q':
        case 27:    // escape key code
            exit(0);

        case 't':
            pointLights[0].Attenuation.Linear += ATTEN_STEP;
            pointLights[1].Attenuation.Linear += ATTEN_STEP;
            break;

        case 'y':
            pointLights[0].Attenuation.Linear -= ATTEN_STEP;
            pointLights[1].Attenuation.Linear -= ATTEN_STEP;
            break;

        case 'g':
            pointLights[0].Attenuation.Exp += ATTEN_STEP;
            pointLights[1].Attenuation.Exp += ATTEN_STEP;
            break;

        case 'h':
            pointLights[0].Attenuation.Exp -= ATTEN_STEP;
            pointLights[1].Attenuation.Exp -= ATTEN_STEP;
            break;

        case 'v':
            spotLights[0].Cutoff += ANGLE_STEP;
            break;

        case 'b':
            spotLights[0].Cutoff -= ANGLE_STEP;
            break;

        case 'n':
            spotLights[1].Cutoff += ANGLE_STEP;
            break;

        case 'm':
            spotLights[1].Cutoff -= ANGLE_STEP;
            break;

    }

    pGameCamera->OnKeyboard(key);
}


void AnimationProgram::SpecialKeyboardCB(int key, int mouse_x, int mouse_y)
{
    pGameCamera->OnKeyboard(key);
}


void AnimationProgram::PassiveMouseCB(int x, int y)
{
    pGameCamera->OnMouse(x, y);
}


AnimationProgram* pAnimationProgram = NULL;


void RenderSceneCB()
{
    pAnimationProgram->RenderSceneCB();
}


void KeyboardCB(unsigned char key, int mouse_x, int mouse_y)
{
    pAnimationProgram->KeyboardCB(key, mouse_x, mouse_y);
}


void SpecialKeyboardCB(int key, int mouse_x, int mouse_y)
{
    pAnimationProgram->SpecialKeyboardCB(key, mouse_x, mouse_y);
}


void PassiveMouseCB(int x, int y)
{
    pAnimationProgram->PassiveMouseCB(x, y);
}


void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
    glutKeyboardFunc(KeyboardCB);
    glutSpecialFunc(SpecialKeyboardCB);
    glutPassiveMotionFunc(PassiveMouseCB);
}


#endif //CGPROJECT_ANIMATIONPROGRAM_H
