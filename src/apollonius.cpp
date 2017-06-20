#include "apollonius.h"

VoronoiVertex apollonius_direction(coord x, coord y, const std::vector<VoronoiVertex>& v)
{
    Apollonius_graph ag;
    Site_2 site;
    Point_2 point;
    VoronoiVertex avertex;

    // read the sites and insert them in the Apollonius graph
    for (const auto& s: v) {
        ag.insert(Site_2(Point_2(s.x, s.y), s.r));
    }

    // validate the Apollonius graph
    // if (!ag.is_valid(true, 1)) {
    //     return 31337;
    // }

    // use the graph
    auto vhandle = ag.nearest_neighbor(Point_2(x, y));
    // auto circ = ag.incident_vertices(vhandle);
    // auto point = (*vhandle).site().point();
    Agds::Face_handle fh = (*vhandle).face();
    // Traits::Object_2 dualobj = CGAL::object_cast<Traits::Object_2>(ag.dual(fh));

    try {
        site = CGAL::object_cast<Site_2>(ag.dual(fh));
        point = site.point();
        auto vpoint = (*vhandle).site().point();
        auto dx = vpoint.x() - point.x();
        auto dy = vpoint.y() - point.y();
        auto r = sqrt(dx*dx + dy*dy);
        avertex = VoronoiVertex{point.x(), point.y(), r};
    } catch(CGAL::Bad_object_cast e) {
        avertex = VoronoiVertex{x, y};
    }

    // auto vit = circ;
    // do {
    //     auto point = (*vit).site().point();
    // } while (++vit != circ);

    return avertex;
}

