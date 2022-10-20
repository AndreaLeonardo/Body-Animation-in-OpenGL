#include <map>
#include <string>
#include <vector>
#include <iostream>

#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags

#define GL_SILENCE_DEPRECATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <GLUT/glut.h>

#include "ogldev/ogldev_basic_mesh.h"
#include "ogldev/ogldev_math_3d.h"
#include "camera.h"
#include "ogldev/ogldev_world_transform.h"
#include "ogldev/ogldev_engine_common.h"
#include "ogldev/ogldev_texture.h"
#include "AssimpObjLoader.h"
#include "skinned_mesh.h"
#include "assImport.h"
#include "skinning_technique.h"
#include "AnimationProgram.h"
#include "SkinningDebug.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 720
#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenNormals |  aiProcess_JoinIdenticalVertices )



int main(int argc, char** argv)
{
#ifdef _WIN64
    srand(GetCurrentProcessId());
#else
    srandom(getpid());
#endif

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_3_2_CORE_PROFILE|GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    int x = 200;
    int y = 100;
    glutInitWindowPosition(x, y);
    int win = glutCreateWindow("Body Animation Program");
    glClearColor(0.0,0.0,0.0,1.0);
    printf("window id: %d\n", win);


    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }



    int action = 3; // action = 0 -> visualization of animation
                    // action = 1 -> visualization of weights debugger
                    // action = 2 -> visualization of static model
                    // action = 3 -> visualization of assimp import on terminal

    switch (action) {
        case 0:
            glEnable( GL_BLEND );
            glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
            InitializeGlutCallbacks();
            pAnimationProgram = new AnimationProgram();
            if (!pAnimationProgram->Init()) {
                return 1;
            }
            glutMainLoop();
            break;
        case 1:
            dInitializeGlutCallbacks();
            pSkinningDebug = new SkinningDebug();
            if (!pSkinningDebug->Init()) {
                return 1;
            }
            glutMainLoop();
            break;
        case 2:
            oInitializeGlutCallbacks();
            pAssimpRenderProgram = new AssimpRenderProgram();
            if (!pAssimpRenderProgram->Init()) {
                return 1;
            }
            glutMainLoop();
            break;
        default:
            if (argc != 2) {
                printf("Usage: %s <model filename>\n", argv[0]);
                return 1;
            }
            char *filename = "link/model/body/c00/link.md5mesh";

            Assimp::Importer Importer;
            const aiScene *pScene = Importer.ReadFile(filename, ASSIMP_LOAD_FLAGS);

            if (!pScene) {
                printf("Error parsing '%s': '%s'\n", filename, Importer.GetErrorString());
                return 1;
            }
            parse_scene(pScene);
            break;

    }

    return 0;

}