/* 
 * File:   Globals.hpp
 * 
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015, Michael Abseher
 *    E-Mail: <abseher@dbai.tuwien.ac.at>
 * 
 * This file is part of htd.
 * 
 * htd is free software: you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License as published by the Free 
 * Software Foundation, either version 3 of the License, or (at your 
 * option) any later version.
 * 
 * htd is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public 
 * License for more details.

 * You should have received a copy of the GNU General Public License
 * along with htd.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HTD_HTD_GLOBALS_HPP
#define HTD_HTD_GLOBALS_HPP

#include <htd/CompilerDetection.hpp>
#include <htd/Id.hpp>
#include <htd/Vertex.hpp>

#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

namespace htd
{
    /**
     *  Datatype for indices.
     */
    typedef std::size_t index_t;

    /**
     *  Datatype for edges.
     */
    typedef std::pair<vertex_t, vertex_t> edge_t;
    
    /**
     *  Datatype for hyperedges.
     */
    typedef std::vector<vertex_t> hyperedge_t;
    
    /**
     *  Datatype for storing vertices.
     */
    typedef std::vector<vertex_t> vertex_container;
    
    /**
     *  Datatype for storing edges.
     */
    typedef std::vector<edge_t> edge_container;
    
    /**
     *  Datatype for storing hyperedges.
     */
    typedef std::vector<hyperedge_t> hyperedge_container;
}

#endif /* HTD_HTD_GLOBALS_HPP */
