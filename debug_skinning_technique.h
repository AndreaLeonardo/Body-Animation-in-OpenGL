/*
        Copyright 2011 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DEBUG_SKINNING_TECHNIQUE_H
#define DEBUG_SKINNING_TECHNIQUE_H

#include "technique.h"
#include "skinning_technique.h"
#include "ogldev/ogldev_math_3d.h"
#include "ogldev/ogldev_material.h"
#include "ogldev/ogldev_world_transform.h"




class DebugSkinningTechnique : public Technique
{
public:

    static const unsigned int MAX_POINT_LIGHTS = 2;
    static const unsigned int MAX_SPOT_LIGHTS = 2;
    static const unsigned int MAX_BONES = 100;

    DebugSkinningTechnique();

    virtual bool Init();

    void SetWVP(const Matrix4f& WVP);
    void SetTextureUnit(unsigned int TextureUnit);
    void SetSpecularExponentTextureUnit(unsigned int TextureUnit);
    void SetDirectionalLight(const DirectionalLight& Light);
    void SetPointLights(unsigned int NumLights, const PointLight* pLights);
    void SetSpotLights(unsigned int NumLights, const SpotLight* pLights);
    void SetCameraLocalPos(const Vector3f& CameraLocalPos);
    void SetMaterial(const Material& material);
    void SetDisplayBoneIndex(uint DisplayBoneIndex);

private:

    GLuint WVPLoc;
    GLuint samplerLoc;
    GLuint samplerSpecularExponentLoc;
    GLuint CameraLocalPosLoc;
    GLuint NumPointLightsLocation;
    GLuint NumSpotLightsLocation;

    struct {
        GLuint AmbientColor;
        GLuint DiffuseColor;
        GLuint SpecularColor;
    } materialLoc;

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint Direction;
        GLuint DiffuseIntensity;
    } dirLightLoc;

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint Position;
        GLuint DiffuseIntensity;

        struct
        {
            GLuint Constant;
            GLuint Linear;
            GLuint Exp;
        } Atten;
    } PointLightsLocation[MAX_POINT_LIGHTS];

struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Position;
        GLuint Direction;
        GLuint Cutoff;
        struct {
            GLuint Constant;
            GLuint Linear;
            GLuint Exp;
        } Atten;
    } SpotLightsLocation[MAX_SPOT_LIGHTS];

    GLuint displayBoneIndexLocation;
};


#endif  /* DEBUG_SKINNING_TECHNIQUE_H */
