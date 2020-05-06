#ifndef LIGHT_H221
#define LIGHT_H221

struct Light
{
    float position[4];   // position, direction
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float direction[3]; // spotlight
    float innerAngle;   // spotlight
    float outerAngle;   // spotlight
    float intensity;
    float attenuation;
    float radius;
};

// A shard is any one triangle in a planar mesh

struct Shard
{
    float p0[3]; // Point
    float p1[3]; // Point
    float p2[3]; // Point
    // Normal?
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void light_loadShadowMatrix(const struct Light* light, float* mat4, const struct Shard* shard);
void light_multShadowMatrix(const struct Light* light, float* mat4, const struct Shard* shard);
void light_use(const struct Light* light, const float* modelViewMatrix);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // LIGHT_H221