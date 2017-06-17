#include "vertex.h"

coord distance(const Vertex& t)
{
    return sqrt((t.x)*(t.x) + (t.y)*(t.y));
}

int sign(coord a)
{
    return (a == 0) ? 0 : ((a > 0) ? 1 : -1);
}

Vertex intersection(
        const Vertex a1, const Vertex a2,
        const Vertex b1, const Vertex b2)
{
    // if (!Range{a1.x, a2.x}.overlaps(Range{b1.x, b2.x})
    //         || !Range{a1.y, a2.y}.overlaps(Range{b1.y, b2.y})) {
    //     return ninfinity_vertex;
    // }

    // SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xff);
    // SDL_RenderClear(gRenderer);
    lineRGBA(gRenderer,
            a1.x + (SCREEN_WIDTH  / 2),
            a1.y + (SCREEN_HEIGHT / 2),
            a2.x + (SCREEN_WIDTH  / 2),
            a2.y + (SCREEN_HEIGHT / 2),
            255, 0, 255, 255);
    lineRGBA(gRenderer,
            b1.x + (SCREEN_WIDTH  / 2),
            b1.y + (SCREEN_HEIGHT / 2),
            b2.x + (SCREEN_WIDTH  / 2),
            b2.y + (SCREEN_HEIGHT / 2),
            255, 255, 0, 255);
    SDL_RenderPresent(gRenderer);
    // SDL_Delay(50);
    lineRGBA(gRenderer,
            a1.x + (SCREEN_WIDTH  / 2),
            a1.y + (SCREEN_HEIGHT / 2),
            a2.x + (SCREEN_WIDTH  / 2),
            a2.y + (SCREEN_HEIGHT / 2),
            0, 255, 255, 255);
    lineRGBA(gRenderer,
            b1.x + (SCREEN_WIDTH  / 2),
            b1.y + (SCREEN_HEIGHT / 2),
            b2.x + (SCREEN_WIDTH  / 2),
            b2.y + (SCREEN_HEIGHT / 2),
            0, 255, 255, 255);

    // In a 2x2 matrix, m1 == a, and m2 == b:
    //    / a c \    y = ax + c,
    //    \ b d /    y = bx + d.
    auto p1 = a2.x - a1.x;
    auto q1 = a2.y - a1.y;
    auto p2 = b2.x - b1.x;
    auto q2 = b2.y - b1.y;
    auto x  = -std::numeric_limits<coord>::infinity();
    auto y  = -std::numeric_limits<coord>::infinity();
    if (p1 == 0) { // First line is vertical.
        if (p2 == 0) { // Second line is vertical.
            if (a1.x == b1.x) { // All collinear.
                fputs("((Infty)) ", stderr);
                return infinity_vertex;
            } else { // No intersection.
                fputs("((None)) ", stderr);
                return ninfinity_vertex;
            }
        } else {
            auto m2 = q2 / p2;
            x = a1.x;
            y = m2*a1.x - m2*b1.x + b1.y;
        }
    } else if (p2 == 0) { // Second line is vertical.
        auto m1 = q1 / p1;
        x = b1.x;
        y = m1*b1.x - m1*a1.x + a1.y;
    } else { // Both lines are not vertical.
        auto m1 = q1 / p1;
        auto m2 = q2 / p2;
        auto c  = -m1*a1.x + a1.y;
        auto d  = -m2*b1.x + b1.y;
        if (m1 - m2 == 0) { // No single intersection.
            if (m1*d - m2*c != 0) { // All collinear.
                fputs("((Infty)) ", stderr);
                return infinity_vertex;
            } else { // No intersection.
                fputs("((None)) ", stderr);
                return ninfinity_vertex;
            }
        } else { // Intersection.
            x = (d - c) / (m1 - m2);
            y = m1*x + c;
        }
    }

    if (Range{a1.x, a2.x}.overlaps(x)
            && Range{b1.x, b2.x}.overlaps(x)
            && Range{a1.y, a2.y}.overlaps(y)
            && Range{b1.y, b2.y}.overlaps(y)) {
        // fputs("Overlap:", stderr);
        fprintf(stderr, "(%f, %f) ", x, y);
        filledCircleRGBA(gRenderer,
                x + (SCREEN_WIDTH / 2),
                y + (SCREEN_HEIGHT / 2),
                5,
                0, 255, 0, 255);
        return Vertex{x, y};
    } else {
        return ninfinity_vertex;
    }
}

