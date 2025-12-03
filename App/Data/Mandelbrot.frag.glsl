#version 460 core

layout(location = 0) out vec4 fragColor;

layout(location = 1) uniform vec2  iResolution;
layout(location = 2) uniform vec2  center;
layout(location = 3) uniform float zoom;
layout(location = 4) uniform sampler1D palette;

uniform int u_maxIterations;

int mandelbrot(vec2 c)
{
    vec2 z = vec2(0.0);

    for (int i = 0; i < u_maxIterations; i++)
    {
        float x = z.x * z.x - z.y * z.y + c.x;
        float y = 2.0 * z.x * z.y + c.y;

        z.x = x;
        z.y = y;

        if (dot(z, z) > 4.0)
            return i;
    }

    return u_maxIterations;
}

void main()
{
    vec2 uv = (gl_FragCoord.xy / iResolution) * 2.0 - 1.0;
    uv.x *= iResolution.x / iResolution.y;

    vec2 world = center + uv * zoom;

    int iter = mandelbrot(world);

    // Normalize iteration count for palette lookup
    float t = float(iter) / float(u_maxIterations);

    vec3 color;

    if (iter == u_maxIterations)
        color = vec3(0.0);
    else
        color = texture(palette, t).rgb;

    fragColor = vec4(color, 1.0);
}
