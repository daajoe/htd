/* 
 * File:   MultiHypergraph.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2016, Michael Abseher
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

#ifndef HTD_HTD_MULTIHYPERGRAPH_HPP
#define	HTD_HTD_MULTIHYPERGRAPH_HPP

#include <htd/IMutableMultiHypergraph.hpp>
#include <htd/LibraryInstance.hpp>

#include <vector>
#include <unordered_set>

namespace htd
{
    /**
     *  Default implementation of the IMutableMultiHypergraph interface.
     */
    class MultiHypergraph : public virtual htd::IMutableMultiHypergraph
    {
        public:
            /**
             *  Constructor for a multi-hypergraph.
             *
             *  @param[in] manager   The management instance to which the new multi-hypergraph belongs.
             */
            HTD_API MultiHypergraph(const htd::LibraryInstance * const manager);

            /**
             *  Constructor for a multi-hypergraph.
             *
             *  @param[in] manager       The management instance to which the new multi-hypergraph belongs.
             *  @param[in] initialSize  The initial size of the created graph.
             */
            HTD_API MultiHypergraph(const htd::LibraryInstance * const manager, std::size_t initialSize);

            /**
             *  Copy constructor for a multi-hypergraph.
             *
             *  @param[in] original  The original multi-hypergraph.
             */
            HTD_API MultiHypergraph(const MultiHypergraph & original);

            /**
             *  Copy constructor for a multi-hypergraph.
             *
             *  @param[in] original  The original multi-hypergraph.
             */
            HTD_API MultiHypergraph(const htd::IMultiHypergraph & original);

            HTD_API virtual ~MultiHypergraph();
            
            HTD_API std::size_t vertexCount(void) const HTD_OVERRIDE;

            HTD_API std::size_t edgeCount(void) const HTD_OVERRIDE;

            HTD_API std::size_t edgeCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API bool isVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API bool isEdge(htd::id_t edgeId) const HTD_OVERRIDE;

            HTD_API bool isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            HTD_API bool isEdge(const std::vector<htd::vertex_t> & elements) const HTD_OVERRIDE;

            HTD_API bool isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::id_t> associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::id_t> associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::id_t> associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const HTD_OVERRIDE;

            HTD_API htd::vertex_t vertexAtPosition(htd::index_t index) const HTD_OVERRIDE;
            
            HTD_API bool isConnected(void) const HTD_OVERRIDE;
            
            HTD_API bool isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            HTD_API bool isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const HTD_OVERRIDE;
            
            HTD_API std::size_t neighborCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> neighbors(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API void copyNeighborsTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API htd::vertex_t neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> vertices(void) const HTD_OVERRIDE;

            /**
             *  Access the vector of all vertices in the tree.
             *
             *  @return The vector of all vertices in the tree sorted in ascending order.
             */
            HTD_API const std::vector<htd::vertex_t> & vertexVector(void) const;

            HTD_API std::size_t isolatedVertexCount(void) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> isolatedVertices(void) const HTD_OVERRIDE;

            HTD_API htd::vertex_t isolatedVertexAtPosition(htd::index_t index) const HTD_OVERRIDE;

            HTD_API bool isIsolatedVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::Hyperedge> hyperedges(void) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::Hyperedge> hyperedges(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API const htd::Hyperedge & hyperedge(htd::id_t edgeId) const HTD_OVERRIDE;

            HTD_API const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index) const HTD_OVERRIDE;

            HTD_API const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API htd::FilteredHyperedgeCollection hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const HTD_OVERRIDE;

            HTD_API htd::FilteredHyperedgeCollection hyperedgesAtPositions(std::vector<htd::index_t> && indices) const HTD_OVERRIDE;

            HTD_API htd::vertex_t nextVertex(void) const HTD_OVERRIDE;

            HTD_API htd::id_t nextEdgeId(void) const HTD_OVERRIDE;

            HTD_API htd::vertex_t addVertex(void) HTD_OVERRIDE;

            HTD_API htd::vertex_t addVertices(std::size_t count) HTD_OVERRIDE;
            
            HTD_API void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API htd::id_t addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            HTD_API htd::id_t addEdge(const std::vector<htd::vertex_t> & elements) HTD_OVERRIDE;

            HTD_API htd::id_t addEdge(std::vector<htd::vertex_t> && elements) HTD_OVERRIDE;

            HTD_API htd::id_t addEdge(const htd::ConstCollection<htd::vertex_t> & elements) HTD_OVERRIDE;

            HTD_API htd::id_t addEdge(const htd::Hyperedge & hyperedge) HTD_OVERRIDE;

            HTD_API htd::id_t addEdge(htd::Hyperedge && hyperedge) HTD_OVERRIDE;

            HTD_API void removeEdge(htd::id_t edgeId) HTD_OVERRIDE;

            HTD_API const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API MultiHypergraph * clone(void) const HTD_OVERRIDE;
#else
            /**
             *  Create a deep copy of the current mutable multi-hypergraph.
             *
             *  @return A new MultiHypergraph object identical to the current mutable multi-hypergraph.
             */
            HTD_API MultiHypergraph * clone(void) const;

            HTD_API htd::IMultiHypergraph * cloneMultiHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::IMutableMultiHypergraph * cloneMutableMultiHypergraph(void) const HTD_OVERRIDE;
#endif

            /**
             *  Copy assignment operator for a mutable multi-hypergraph.
             *
             *  @param[in] original  The original multi-hypergraph.
             */
            HTD_API MultiHypergraph & operator=(const MultiHypergraph & original);

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API MultiHypergraph & operator=(const htd::IMultiHypergraph & original) HTD_OVERRIDE;
#else
            HTD_API MultiHypergraph & operator=(const htd::IMultiHypergraph & original);

            HTD_API void assign(const htd::IMultiHypergraph & original) HTD_OVERRIDE;
#endif

        private:
            HTD_IMPLEMENTATION Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_MULTIHYPERGRAPH_HPP */
