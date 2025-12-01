#version 460 core

out vec4 fragColor;

uniform vec2 iResolution;
uniform float iTime;

// Center and zoom
uniform vec2 center = vec2(-0.5, 0.0);
uniform float zoom = 0.5;

void main()
{
    // Normalized pixel coordinate (−1 to +1)
    vec2 uv = (gl_FragCoord.xy / iResolution.xy) * 2.0 - 1.0;
    uv.x *= iResolution.x / iResolution.y;

    // Apply zoom & pan
    vec2 c = center + uv * zoom;

    // Mandelbrot iteration
    vec2 z = vec2(0.0);
    int maxIter = 200;
    int i;

    for (i = 0; i < maxIter; i++) {
        float x = (z.x * z.x - z.y * z.y) + c.x;
        float y = (2.0 * z.x * z.y) + c.y;
        z = vec2(x, y);

        if (dot(z, z) > 4.0)
            break;
    }

    // Smooth coloring
    float t = float(i) - log2(log2(dot(z, z))) + 4.0;
    float color = t / float(maxIter);

    // Color palette
    vec3 col = vec3(
        0.5 + 0.5 * cos(3.0 + color * 5.0),
        0.5 + 0.5 * cos(1.0 + color * 5.0),
        0.5 + 0.5 * cos(2.0 + color * 5.0)
    );

    // Inside the set is black
    if (i == maxIter) col = vec3(0.0);

    fragColor = vec4(col, 1.0);
}
