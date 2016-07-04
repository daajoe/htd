/*
 * File:   AddEmptyRootOperation.cpp
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

#ifndef HTD_HTD_ADDEMPTYROOTOPERATION_CPP
#define	HTD_HTD_ADDEMPTYROOTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/AddEmptyRootOperation.hpp>

htd::AddEmptyRootOperation::AddEmptyRootOperation(void)
{

}

htd::AddEmptyRootOperation::~AddEmptyRootOperation()
{

}

void htd::AddEmptyRootOperation::apply(htd::IMutablePathDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::AddEmptyRootOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices) const
{
    HTD_UNUSED(relevantVertices)

    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::AddEmptyRootOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::vertex_t root = decomposition.root();

    if (decomposition.bagSize(root) > 0)
    {
        htd::vertex_t newRoot = decomposition.addParent(root);

        for (auto & labelingFunction : labelingFunctions)
        {
            htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newRoot);

            const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(newRoot);

            htd::ILabel * newLabel = labelingFunction->computeLabel(bagContent, *labelCollection);

            delete labelCollection;

            decomposition.setVertexLabel(labelingFunction->name(), newRoot, newLabel);
        }
    }
}

void htd::AddEmptyRootOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(relevantVertices)

    apply(decomposition, labelingFunctions);
}

void htd::AddEmptyRootOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::AddEmptyRootOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::AddEmptyRootOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::vertex_t root = decomposition.root();

    if (decomposition.bagSize(root) > 0)
    {
        htd::vertex_t newRoot = decomposition.addParent(root);

        for (auto & labelingFunction : labelingFunctions)
        {
            htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newRoot);

            const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(newRoot);

            htd::ILabel * newLabel = labelingFunction->computeLabel(bagContent, *labelCollection);

            delete labelCollection;

            decomposition.setVertexLabel(labelingFunction->name(), newRoot, newLabel);
        }
    }
}

void htd::AddEmptyRootOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(relevantVertices)
    HTD_UNUSED(createdVertices)
    HTD_UNUSED(removedVertices)

    apply(decomposition, labelingFunctions);
}

bool htd::AddEmptyRootOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::AddEmptyRootOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::AddEmptyRootOperation::removesTreeNodes(void) const
{
    return false;
}

bool htd::AddEmptyRootOperation::modifiesBagContents(void) const
{
    return false;
}

bool htd::AddEmptyRootOperation::createsLocationDependendLabels(void) const
{
    return false;
}

htd::AddEmptyRootOperation * htd::AddEmptyRootOperation::clone(void) const
{
    return new htd::AddEmptyRootOperation();
}

#endif /* HTD_HTD_ADDEMPTYROOTOPERATION_CPP */
