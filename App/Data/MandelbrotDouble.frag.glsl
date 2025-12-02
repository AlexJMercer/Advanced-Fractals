#version 460 core

layout(location = 0) out vec4 fragColor;

layout(location = 1) uniform vec2  iResolution;
layout(location = 2) uniform dvec2 center;
layout(location = 3) uniform double zoom;
layout(location = 4) uniform sampler1D palette;

uniform int u_maxIterations;

#define ITER_LIMIT 15000


int dynamicMaxIter()
{
    // scale iterations as you zoom
    float factor = max(log(float(zoom)), 0.0);
    return int(float(u_maxIterations) * (1.0 + factor));
}


int mandelbrot(dvec2 c, int maxIter)
{
    dvec2 z = dvec2(0.0);
    int i;

    for (i = 0; i < maxIter; i++)
    {
        // z = z^2 + c  (double precision)
        double x = z.x * z.x - z.y * z.y + c.x;
        double y = 2.0 * z.x * z.y + c.y;

        z.x = x;
        z.y = y;

        if (z.x * z.x + z.y * z.y > 4.0)
            break;
    }
    return i;
}


void main()
{
    vec2 uv = (gl_FragCoord.xy / iResolution) * 2.0 - 1.0;
    uv.x *= iResolution.x / iResolution.y;

    dvec2 world = center + dvec2(uv) * zoom;

    int maxI = dynamicMaxIter();
    int iter = mandelbrot(world, maxI);

    float t = float(iter) / float(maxI);

    vec3 color = texture(palette, t).rgb;

    if (iter == maxI)
        color = vec3(0.0);

    fragColor = vec4(color, 1.0);
}
