#include "polygon.h"

Polygon::Polygon(const ConvexHull& v):
    Shape(),
    UnionShape()
{
    chull = v;
    updateTextureSide();
}

Polygon::Polygon(ConvexHull&& v):
    Shape(),
    UnionShape()
{
    chull = std::move(v);
    updateTextureSide();
}

Polygon::Polygon(size_t n, size_t s, coord r):
    Shape(),
    UnionShape()
{
    fputs("(Constructing polygram.)", stderr);
    if (n < 3 || 1 > s || s >= n || r <= 0) {
        throw;
    }

    auto v = ConvexHull{};
    auto dt = 2 * M_PI * s / n;
    for (auto i = 0u; i < n; i++){
        auto t = i * dt;
        v.push_back(Vertex{r * cos(t), r * sin(t)});
    }

    chull = std::move(v);
    updateTextureSide();
}

void Polygon::add(Vertex v)
{
    chull.push_back(v);
    updateTextureSide();
}

bool Polygon::intersects(const Shape& s) const
{
    for (auto it = chull.begin(); it < chull.end() - 1; it++) {
        auto t = it->angleTo(*(it + 1)) + (M_PI / 2.0);
        if (projectOn(t).overlaps(s.projectOn(t))) {
            return true;
        }
    }

    return false;
}

bool Polygon::intersects(const Point& s) const
{
    auto sy = s.vcenter().y;
    auto intersections = 0u;
    for (auto it = chull.begin(); it < chull.end() - 1; it++) {
        auto a = it;
        auto b = it + 1;
        if ((a->y < sy && sy < b->y) || (b->y < sy && sy < a->y)) {
            intersections++;
        }
    }
    return (intersections % 2 == 1);
}

void Polygon::render(void) const
{
    auto verts = vertices();
    auto size  = verts.size();
    auto xs    = std::vector<Sint16>(size);
    auto ys    = std::vector<Sint16>(size);
    auto itx   = xs.begin();
    auto ity   = ys.begin();
    for (const auto& v: verts) {
        auto vx = v.x + (textureSide / 2);
        auto vy = v.y + (textureSide / 2);
        // filledCircleRGBA(gRenderer, vx, vy, 3, 255, 0, 255, 255);
        *itx++ = vx;
        *ity++ = vy;
    }
    filledPolygonRGBA(gRenderer, xs.data(), ys.data(), size, 255, 255, 255, 63);
}

Range Polygon::project(coord on, Vertex v) const
{
    auto r = Range();
    for (const auto& v: chull) {
        r.update(v.project(on, {v.x + x, v.y + y}));
    }
    return r;
}

bool Polygon::isConcave(void) const
{
    return isConcave(chull);
}

bool Polygon::isConcave(const ConvexHull& v) const
{
    for (const auto& t: v) {
        fprintf(stderr, "(%f, %f)\n", t.x, t.y);
    }
    // Assumes degenerate vertexes have been removed.
    // I.e. ----><---- (0 length) or ---->---->x (twice length).
    // Then the sign of crossz will never be zero.
    auto first = *(v.end()-1) - *(v.end()-2);
    auto last  = *(v.begin()) - *(v.end()-1);
    auto s     = sign(first.crossz(last));
    fprintf(stderr, "[(%f, %f)x(%f, %f): %d]\n",
            first.x, first.y, last.x, last.y, s);
    first  = *(v.begin()) - *(v.end()-1);
    last   = *(v.begin()+1) - *(v.begin());
    auto r = sign(first.crossz(last));
    fprintf(stderr, "[(%f, %f)x(%f, %f): %d]\n",
            first.x, first.y, last.x, last.y, r);
    if (r != s) { return true; }
    for (auto it = v.begin(); it < v.end() - 2; it++) {
        auto a = *(it+1) - *(it+0);
        auto b = *(it+2) - *(it+1);
        auto t = sign(a.crossz(b));
        fprintf(stderr, "[(%f, %f)x(%f, %f): %d]\n",
                a.x, a.y, b.x, b.y, t);
        // fprintf(stderr, "%d ", t);
        if (s != t) {
            return true;
        }
    }
    return false;
}

    std::vector<std::pair<Vertex, Vertex>>
pairsExcept(
        const std::pair<Vertex, Vertex>& exclude,
        const ConvexHull::iterator& first,
        const ConvexHull::iterator& last)
{
    std::vector<std::pair<Vertex, Vertex>> pairs;

    for (auto ita = first; ita < last; ita++) {
        for (auto itb = first; itb < last; itb++) {
            auto r = std::make_pair(*ita, *itb);
            if (r != exclude) {
                pairs.emplace_back(r);
            }
        }
    }
    auto end = std::make_pair(*(last-1), *first);
    if (end != exclude) {
        pairs.emplace_back(end);
    }

    fprintf(stderr, "<<%lu>>", pairs.size());
    return pairs;
}

ConvexHull inverseHull(const ConvexHull& many, const ConvexHull& few)
{
    fputs("\n\n", stderr);
    ConvexHull inverse;

    bool elem = false;
    for (auto m = many.begin(); m != many.end(); m++) {
        for (auto f = few.begin(); f != few.end(); f++) {
            if (*m == *f) {
                elem = true;
                break;
            }
        }
        if (!elem) {
            fprintf(stderr, ">>%f, %f<< ", m->x, m->y);
            filledCircleRGBA(gRenderer,
                    m->x + (SCREEN_WIDTH / 2),
                    m->y + (SCREEN_HEIGHT / 2),
                    10,
                    0, 0, 255, 255);
            SDL_RenderPresent(gRenderer);
            SDL_Delay(100);
            inverse.push_back(*m);
        }
        elem = false;
    }

    return inverse;
}

Vertex functionMax(
        const ConvexHull& many,
        std::function<coord (const Vertex&)> f)
{
    auto m = many[0];
    auto x = f(m);
    for (const auto& v: many) {
        auto t = f(v);
        if (t > x) {
            m = v;
            x = t;
        }
    }
    return m;
}

Vertex functionMin(
        const ConvexHull& many,
        std::function<coord (const Vertex&)> f)
{
    auto m = many[0];
    auto x = f(m);
    for (const auto& v: many) {
        auto t = f(v);
        if (t < x) {
            m = v;
            x = t;
        }
    }
    return m;
}

int orientation(Vertex a, Vertex b, Vertex c)
{
    // Collinear => 0.
    // Clockwise => 1.
    // Counterclockwise => -1.
    auto v = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    return (v == 0) ? 0 : ((v > 0) ? 1 : -1);
}

ConvexHull convexHull(const ConvexHull& many)
{
    if (many.size() < 3) { // Handle degenerate cases.
        return many;
    }

    // Gift wrap.
    ConvexHull hull;
    auto left = std::min_element(many.begin(), many.end());
    auto cur  = left;
    auto it   = many.begin();
    do {
        hull.push_back(*cur);
        fprintf(stderr, "{%f, %f}", cur->x, cur->y);
        filledCircleRGBA(gRenderer,
                cur->x + (SCREEN_WIDTH / 2),
                cur->y + (SCREEN_HEIGHT / 2),
                10,
                0, 255, 0, 127);
        SDL_RenderPresent(gRenderer);
        SDL_Delay(500);

        it = cur + 1;
        if (it == many.end()) {
            it = many.begin();
        }
        for (auto itt = many.begin(); itt != many.end(); itt++) {
            auto o = orientation(*cur, *itt, *it);
            // fprintf(stderr, "%d ", o);
            if (o == -1) {
                it = itt;
            }
        }
        cur = it;
    } while (*cur != *left);

    return hull;
}

void Polygon::simplify(void)
{
    // TODO: Somehow turn vertex vectors into polygona.
    // It actually gets complicated because of *edge* cases where intersection
    // points are not merely concave, but are either the result of backtracking
    // with some messy collinear vertices (like drawing the character '9' with
    // the requirement that the start and end points are the same), or the
    // result of a set of vertices whose hull is not a single polygon (like the
    // character '8', where the intersection can be a point [handwritten] or
    // edge [seven-segment], giving either two separate circular shapes for the
    // former, and a single, unified rectangle for the latter.
    //
    // First, throw out bad cases where complex polygon vertex vectors do not
    // form a single polygon, somehow.
    //
    // Then, look at the vertex vector as a whole. Find the *convex* hull of the
    // vertices. Then find a second, inner hull of the remaining intersection
    // points only. The points that remain that are not in hulls are on the
    // interior of the shape. The inner hull vertices should connect to only two
    // of the outer hull vertices, which are the two closest by Euclidean
    // distance. If this "V" connection for inner hull vertices results in
    // new intersections, then these vertices must be connected to each
    // other, choosing by closest Euclidean distance to outer hull vertices for
    // the first and last candidates, and also for adjacent connections, such
    // that each vertex has only the expected two edges coming from it.

    fprintf(stderr, "<<%lu>>\n", chull.size());
    // renderTexture(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
    auto hull = convexHull(chull);
    // auto inner = convexHull(inverseHull(chull, outer));
    // fprintf(stderr, "{{%lu}}\n", inner.size());

    ConvexHull newHull;
    newHull.clear();
    for (auto it = chull.begin(); it < chull.end() - 1; it++) {
        auto a = *it;
        auto b = *(it+1);
        // auto pairs = pairsExcept(std::make_pair(a, b), it+1, chull.end());
        auto pairs = pairsExcept(std::make_pair(a, b), chull.begin(), chull.end());
        for (auto pair: pairs) {
            auto v = intersection(a, b, std::get<0>(pair), std::get<1>(pair));
            if (v == infinity_vertex) {
                // TODO: Remove an unnecessary vertex.
                // This is the collinear vertices / away and back situation.
            } else if (v != ninfinity_vertex) {
                // TODO: This is an intersection; therefore the polygon is
                // complex and needs further "simplification" into a convex or
                // concave "perimeter" hull.
                if (std::find(newHull.begin(), newHull.end(), v) == newHull.end()
                        && std::find(hull.begin(), hull.end(), v) == hull.end()) {
                    newHull.push_back(v);
                }
            }
        }
    }

    auto a = *(chull.end()-1);
    auto b = *(chull.begin());
    auto pairs = pairsExcept(std::make_pair(a, b), chull.begin(), chull.end());
    for (auto pair: pairs) {
        auto v = intersection(a, b, std::get<0>(pair), std::get<1>(pair));
        if (v == infinity_vertex) {
            // TODO: Remove an unnecessary vertex.
            // This is the collinear vertices / away and back situation.
        } else if (v != ninfinity_vertex) {
            // TODO: This is an intersection; therefore the polygon is
            // complex and needs further "simplification" into a convex or
            // concave "perimeter" hull.
            if (std::find(newHull.begin(), newHull.end(), v) == newHull.end()
                    && std::find(hull.begin(), hull.end(), v) == hull.end()) {
                fprintf(stderr, "=><%f, %f>\n", v.x, v.y);
                newHull.push_back(v);
            }
        }
    }

    chull.insert(chull.end(), newHull.begin(), newHull.end());

    // std::sort(chull.begin(), chull.end());
    // chull.erase(std::unique(chull.begin(), chull.end()), chull.end());

    // TODO: Convert to using sets to get rid of all this duplication checking
    // nonsense.
    // std::unordered_set<Vertex> vset;
    std::set<Vertex> vset;
    for (const auto& v: chull) {
        vset.insert(v);
    }
    chull.assign(vset.begin(), vset.end());
    sort(chull.begin(), chull.end());

    auto inner = convexHull(inverseHull(chull, hull));
    // auto inner = inverseHull(chull, hull);
    SDL_Delay(1000);
    chull = inner;
    // chull = hull;

    fprintf(stderr, "<<%lu>>\n", chull.size());
    updateTextureSide();
}

