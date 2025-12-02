#version 460 core

layout(location = 0) out vec4 fragColor;

layout(location = 1) uniform vec2  iResolution;
layout(location = 2) uniform dvec2 center;
layout(location = 3) uniform double zoom;
layout(location = 4) uniform sampler1D palette;

int mandelbrot(dvec2 c)
{
    dvec2 z = dvec2(0.0, 0.0);
    const int MAX_ITER = 500;

    for (int i = 0; i < MAX_ITER; i++)
    {
        double x = z.x * z.x - z.y * z.y + c.x;
        double y = 2.0 * z.x * z.y + c.y;

        z.x = x;
        z.y = y;

        if (z.x * z.x + z.y * z.y > 4.0)
            return i;
    }

    return MAX_ITER;
}

void main()
{
    // Convert pixel coordinates to world coordinates
    vec2 uv = (gl_FragCoord.xy / iResolution) * 2.0 - 1.0;
    uv.x *= iResolution.x / iResolution.y;

    dvec2 world = center + dvec2(uv) * zoom;

    // Compute iteration count
    int iter = mandelbrot(world);

    // Normalize for palette lookup
    const int MAX_ITER = 500;
    float t = float(iter) / float(MAX_ITER);

    vec3 color;

    if (iter == MAX_ITER)
        color = vec3(0.0);
    else
        color = texture(palette, t).rgb;
    

    fragColor = vec4(color, 1.0);
}
