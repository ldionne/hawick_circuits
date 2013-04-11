// Copyright Louis Dionne 2013. Use, modification and distribution is subject
// to the Boost Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <algorithm>
#include <boost/assert.hpp>
#include <boost/graph/directed_graph.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/hawick_circuits.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/next_prior.hpp>
#include <boost/property_map/property_map.hpp>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>


template <typename OutputStream>
struct cycle_printer
{
    cycle_printer(OutputStream& stream)
        : os(stream)
    { }

    template <typename Path, typename Graph>
    void cycle(Path const& p, Graph const& g)
    {
        if (p.empty())
            return;

        // Get the property map containing the vertex indices
        // so we can print them.
        typedef typename boost::property_map<
                    Graph, boost::vertex_index_t
                >::const_type IndexMap;
        IndexMap indices = get(boost::vertex_index, g);

        // Iterate over path printing each vertex that forms the cycle.
        typename Path::const_iterator i, before_end = boost::prior(p.end());
        for (i = p.begin(); i != before_end; ++i) {
            os << get(indices, *i) << " ";
        }
        os << get(indices, *i) << '\n';
    }
    OutputStream& os;
};

struct command_line {
    unsigned int num_vertices;
    std::vector<std::string> edges;
};

template <typename Graph>
void build_graph(Graph& g, command_line const& cmd) {
    typedef typename boost::graph_traits<Graph>::vertex_descriptor vertex_descriptor;
    std::map<unsigned int, vertex_descriptor> vertices;

    for (unsigned int i = 0; i < cmd.num_vertices; ++i)
        vertices[i] = add_vertex(g);

    for (unsigned int i = 0; i < cmd.edges.size(); ++i) {
        std::istringstream iss(cmd.edges[i]);
        unsigned int u, v;
        char comma;
        iss >> u >> comma >> v;
        BOOST_ASSERT(iss);

        add_edge(vertices[u], vertices[v], g);
    }
}


int main(int argc, char const* argv[]) {
    if (argc < 2) {
        std::cout << "usage: " << argv[0] << " num_vertices [v0, v1, ..., vn]\n";
        return EXIT_FAILURE;
    }

    command_line cmd = {
        boost::lexical_cast<unsigned int>(argv[1]),
        std::vector<std::string>(argv + 2, argv + argc)
    };

    boost::directed_graph<> graph;
    build_graph(graph, cmd);

    BOOST_ASSERT(num_vertices(graph) == cmd.num_vertices);

    cycle_printer<std::ostream> visitor(std::cout);
    boost::hawick_circuits(graph, visitor);

    return EXIT_SUCCESS;
}
