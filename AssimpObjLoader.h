//
// Created by Andrea Leonardo on 07/07/22.
//

#ifndef CGPROJECT_ASSIMPOBJLOADER_H
#define CGPROJECT_ASSIMPOBJLOADER_H

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 720

class AssimpRenderProgram
{
public:
    AssimpRenderProgram();
    ~AssimpRenderProgram();

    bool Init();

    void RenderSceneCB();
    void KeyboardCB(unsigned char key, int mouse_x, int mouse_y);
    void SpecialKeyboardCB(int key, int mouse_x, int mouse_y);
    void PassiveMouseCB(int x, int y);

private:

    void CompileShaders();
    void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);

    GLuint SpiderVAO = -1;
    GLuint WVPLocation;
    GLuint SamplerLocation;
    Camera* pGameCamera = NULL;
    BasicMesh* pMesh = NULL;
    PersProjInfo persProjInfo;
};
AssimpRenderProgram::AssimpRenderProgram()
{
    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    float FOV = 45.0f;
    float zNear = 1.0f;
    float zFar = 100.0f;

    persProjInfo = { FOV, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, zNear, zFar };
}
AssimpRenderProgram::~AssimpRenderProgram()
{
    if (pGameCamera) {
        delete pGameCamera;
    }

    if (pMesh) {
        delete pMesh;
    }
}
bool AssimpRenderProgram::Init()
{

    pMesh = new BasicMesh();
    if (!pMesh->LoadMesh("blend/fighter/link/model/body/c00/link.md5mesh")) {
        return false;
    } else{
        printf("mesh loaded!");
    }


    CompileShaders();

    Vector3f CameraPos(0.0f, 0.0f, -10.0f);
    Vector3f CameraTarget(0.0f, 0.0f, 1.0f);
    Vector3f CameraUp(0.0f, 1.0f, 0.0f);

    pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, CameraPos, CameraTarget, CameraUp);


    WorldTrans& worldTransform = pMesh->GetWorldTransform();
    worldTransform.SetRotation(-90,180,0);


    return true;
}
void AssimpRenderProgram::RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    pGameCamera->OnRender();

#ifdef _WIN64
    float YRotationAngle = 0.1f;
#else
    float YRotationAngle = 1.0f;
#endif

    WorldTrans& worldTransform = pMesh->GetWorldTransform();

    worldTransform.SetScale(1.0f);
    worldTransform.SetPosition(0.0f, 0.0f, 3.0f);
    worldTransform.Rotate(0.0f, YRotationAngle, 0.0f);

    Matrix4f World = worldTransform.GetMatrix();

    Matrix4f View = pGameCamera->GetMatrix();

    Matrix4f Projection;
    Projection.InitPersProjTransform(persProjInfo);

    Matrix4f WVP = Projection * View * World;
    glUniformMatrix4fv(WVPLocation, 1, GL_TRUE, &WVP.m[0][0]);

    pMesh->Render();

    glutPostRedisplay();

    glutSwapBuffers();
}
void AssimpRenderProgram::KeyboardCB(unsigned char key, int mouse_x, int mouse_y)
{
    switch (key) {
        case 'q':
        case 27:    // escape key code
            exit(0);
    }

    pGameCamera->OnKeyboard(key);
}
void AssimpRenderProgram::SpecialKeyboardCB(int key, int mouse_x, int mouse_y)
{
    pGameCamera->OnKeyboard(key);
}
void AssimpRenderProgram::PassiveMouseCB(int x, int y)
{
    pGameCamera->OnMouse(x, y);
}
void AssimpRenderProgram::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(1);
    }

    const GLchar* p[1];
    p[0] = pShaderText;

    GLint Lengths[1];
    Lengths[0] = (GLint)strlen(pShaderText);

    glShaderSource(ShaderObj, 1, p, Lengths);

    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}
void AssimpRenderProgram::CompileShaders()
{
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    std::string vs, fs;

    if (!ReadFile("shader.vs", vs)) {
        exit(1);
    };

    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

    if (!ReadFile("shader.fs", fs)) {
        exit(1);
    };

    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);


    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
    }



    WVPLocation = glGetUniformLocation(ShaderProgram, "gWVP");
    if (WVPLocation == -1) {
        printf("Error getting uniform location of 'gWVP'\n");
        exit(1);
    }

    SamplerLocation = glGetUniformLocation(ShaderProgram, "gSampler");
    if (SamplerLocation == -1) {
        printf("Error getting uniform location of 'gSampler'\n");
        exit(1);
    }


    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }


    glUseProgram(ShaderProgram);

}

AssimpRenderProgram* pAssimpRenderProgram = NULL;

void oRenderSceneCB()
{
    pAssimpRenderProgram->RenderSceneCB();
}
void oKeyboardCB(unsigned char key, int mouse_x, int mouse_y)
{
    pAssimpRenderProgram->KeyboardCB(key, mouse_x, mouse_y);
}
void oSpecialKeyboardCB(int key, int mouse_x, int mouse_y)
{
    pAssimpRenderProgram->SpecialKeyboardCB(key, mouse_x, mouse_y);
}
void oPassiveMouseCB(int x, int y)
{
    pAssimpRenderProgram->PassiveMouseCB(x, y);
}


void oInitializeGlutCallbacks()
{
    glutDisplayFunc(oRenderSceneCB);
    glutKeyboardFunc(oKeyboardCB);
    glutSpecialFunc(oSpecialKeyboardCB);
    glutPassiveMotionFunc(oPassiveMouseCB);
}


#endif //CGPROJECT_ASSIMPOBJLOADER_H
