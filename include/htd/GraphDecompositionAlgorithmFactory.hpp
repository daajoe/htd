/*
 * File:   GraphDecompositionAlgorithmFactory.hpp
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

#ifndef HTD_HTD_GRAPHDECOMPOSITIONALGORITHMFACTORY_HPP
#define HTD_HTD_GRAPHDECOMPOSITIONALGORITHMFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IGraphDecompositionAlgorithm.hpp>
#include <htd/IDecompositionManipulationOperation.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/IGraphDecompositionManipulationOperation.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IGraphDecompositionAlgorithm interface.
     */
    class GraphDecompositionAlgorithmFactory
    {
        public:
            /**
             *  Constructor for the factory class.
             */
            HTD_API GraphDecompositionAlgorithmFactory(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for the factory class.
             */
            HTD_API GraphDecompositionAlgorithmFactory(const GraphDecompositionAlgorithmFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             */
            HTD_API GraphDecompositionAlgorithmFactory & operator=(const GraphDecompositionAlgorithmFactory & original);

            /**
             *  Destructor of the factory class.
             */
            HTD_API virtual ~GraphDecompositionAlgorithmFactory();

            /**
             *  Create a new IGraphDecompositionAlgorithm object.
             *
             *  @return A new IGraphDecompositionAlgorithm object.
             */
            HTD_API htd::IGraphDecompositionAlgorithm * getGraphDecompositionAlgorithm(void) const;

            /**
             *  Create a new IGraphDecompositionAlgorithm object.
             *
             *  @param[in] manager   The management instance which shall be assigned to the new IGraphDecompositionAlgorithm object.
             *
             *  @return A new IGraphDecompositionAlgorithm object.
             */
            HTD_API htd::IGraphDecompositionAlgorithm * getGraphDecompositionAlgorithm(const htd::LibraryInstance * const manager) const;

            /**
             *  Set the default implementation of the IGraphDecompositionAlgorithm interface.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the IGraphDecompositionAlgorithm interface.
             */
            HTD_API void setConstructionTemplate(htd::IGraphDecompositionAlgorithm * original);

            /**
             *  Set the manipulations which are applied globally to each decomposition generated by the algorithm. The manipulation operations are applied in the given order.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm factory. Deleting a manipulation operation provided to this method outside the decomposition
             *  algorithm factory or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied globally to each decomposition generated by the algorithm.
             */
            HTD_API void setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations);

            /**
             *  Add a new manipulation operation which shall be applied globally to each decomposition generated by the algorithm. The manipulation operations are applied in the given order.
             *
             *  @note When calling this method the control over the memory region of the manipulation operation is transferred to the
             *  decomposition algorithm factory. Deleting the manipulation operation provided to this method outside the decomposition
             *  algorithm factory or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @param[in] manipulationOperation    The manipulation operation which shall be applied globally to each decomposition generated by the algorithm.
             */
            HTD_API void addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation);

            /**
             *  Add additional manipulation operations which shall be applied globally to each decomposition generated by the algorithm. The manipulation operations are applied in the given order.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm factory. Deleting a manipulation operation provided to this method outside the decomposition
             *  algorithm factoryor assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied globally to each decomposition generated by the algorithm.
             */
            HTD_API void addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IGraphDecompositionAlgorithm * constructionTemplate_;

            std::vector<htd::ILabelingFunction *> labelingFunctions_;

            std::vector<htd::IGraphDecompositionManipulationOperation *> postProcessingOperations_;
    };
}

#endif /* HTD_HTD_GRAPHDECOMPOSITIONALGORITHMFACTORY_HPP */
