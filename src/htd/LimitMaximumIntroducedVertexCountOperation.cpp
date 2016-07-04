/*
 * File:   LimitMaximumIntroducedVertexCountOperation.cpp
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

#ifndef HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTEXCOUNTOPERATION_CPP
#define	HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTEXCOUNTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/LimitMaximumIntroducedVertexCountOperation.hpp>

#include <algorithm>
#include <stdexcept>
#include <iterator>

htd::LimitMaximumIntroducedVertexCountOperation::LimitMaximumIntroducedVertexCountOperation(std::size_t limit) : limit_(limit), treatLeafNodesAsIntroduceNodes_(false)
{

}

htd::LimitMaximumIntroducedVertexCountOperation::LimitMaximumIntroducedVertexCountOperation(std::size_t limit, bool treatLeafNodesAsIntroduceNodes) : limit_(limit), treatLeafNodesAsIntroduceNodes_(treatLeafNodesAsIntroduceNodes)
{
  
}

htd::LimitMaximumIntroducedVertexCountOperation::~LimitMaximumIntroducedVertexCountOperation()
{
  
}

void htd::LimitMaximumIntroducedVertexCountOperation::apply(htd::IMutablePathDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::LimitMaximumIntroducedVertexCountOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices) const
{
    HTD_UNUSED(relevantVertices)

    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::LimitMaximumIntroducedVertexCountOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    std::vector<htd::vertex_t> introduceNodes;

    const htd::ConstCollection<htd::vertex_t> & introduceNodeCollection = decomposition.introduceNodes();

    std::copy(introduceNodeCollection.begin(), introduceNodeCollection.end(), std::back_inserter(introduceNodes));

    for (htd::vertex_t node : introduceNodes)
    {
        if (treatLeafNodesAsIntroduceNodes_ || !decomposition.isLeaf(node))
        {
            std::vector<htd::vertex_t> bagContent;

            const std::vector<htd::vertex_t> & bag = decomposition.bagContent(node);

            std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

            std::size_t introducedVertexCount = decomposition.introducedVertexCount(node);

            if (introducedVertexCount > limit_)
            {
                std::vector<htd::vertex_t> introducedVertices;

                decomposition.copyIntroducedVerticesTo(introducedVertices, node);

                std::size_t remainder = introducedVertexCount % limit_;

                introducedVertexCount -= remainder;

                std::size_t intermediatedVertexCount = introducedVertexCount / limit_;

                if (intermediatedVertexCount > 0)
                {
                    intermediatedVertexCount--;
                }

                if (remainder == 0)
                {
                    intermediatedVertexCount--;
                }

                std::vector<htd::vertex_t> children;

                const htd::ConstCollection<htd::vertex_t> & childContainer = decomposition.children(node);

                std::copy(childContainer.begin(), childContainer.end(), std::back_inserter(children));

                if (children.empty())
                {
                    auto start = introducedVertices.begin();
                    auto finish = introducedVertices.begin() + (remainder > 0 ? remainder : limit_);

                    htd::vertex_t newNode = decomposition.addChild(node);

                    decomposition.bagContent(newNode) = std::vector<htd::vertex_t>(start, finish);

                    htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                    newInducedHyperedges.restrictTo(std::vector<htd::vertex_t>(start, finish));

                    decomposition.inducedHyperedges(newNode) = std::move(newInducedHyperedges);

                    for (auto & labelingFunction : labelingFunctions)
                    {
                        htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                        htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newNode), *labelCollection);

                        delete labelCollection;

                        decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                    }

                    if (intermediatedVertexCount > 0)
                    {
                        std::advance(finish, limit_);

                        for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                        {
                            newNode = decomposition.addParent(newNode);

                            decomposition.bagContent(newNode) = std::vector<htd::vertex_t>(start, finish);

                            htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                            newInducedHyperedges.restrictTo(std::vector<htd::vertex_t>(start, finish));

                            decomposition.inducedHyperedges(newNode) = std::move(newInducedHyperedges);

                            for (auto & labelingFunction : labelingFunctions)
                            {
                                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                                htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newNode), *labelCollection);

                                delete labelCollection;

                                decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                            }

                            if (index < introducedVertexCount + limit_)
                            {
                                std::advance(finish, limit_);
                            }
                        }
                    }
                }
                else if (children.size() == 1)
                {
                    htd::vertex_t child = children[0];

                    auto start = introducedVertices.begin();
                    auto finish = introducedVertices.begin() + (remainder > 0 ? remainder : limit_);

                    htd::vertex_t newNode = decomposition.addParent(child);

                    std::vector<htd::vertex_t> newContent;

                    const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(child);

                    std::set_union(bagContent.begin(), bagContent.end(), start, finish, std::back_inserter(newContent));

                    decomposition.bagContent(newNode) = newContent;

                    htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                    newInducedHyperedges.restrictTo(newContent);

                    decomposition.inducedHyperedges(newNode) = std::move(newInducedHyperedges);

                    for (auto & labelingFunction : labelingFunctions)
                    {
                        htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                        htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                        delete labelCollection;

                        decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                    }

                    if (intermediatedVertexCount > 0)
                    {
                        std::advance(start, limit_);
                        std::advance(finish, limit_);

                        for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                        {
                            newNode = decomposition.addParent(newNode);

                            for (auto it = start; it != finish; it++)
                            {
                                newContent.push_back(*it);
                            }

                            decomposition.bagContent(newNode) = newContent;

                            htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                            newInducedHyperedges.restrictTo(newContent);

                            decomposition.inducedHyperedges(newNode) = std::move(newInducedHyperedges);

                            for (auto & labelingFunction : labelingFunctions)
                            {
                                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                                htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                                delete labelCollection;

                                decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                            }

                            if (index < introducedVertexCount + limit_)
                            {
                                std::advance(start, limit_);
                                std::advance(finish, limit_);
                            }
                        }
                    }
                }
            }
        }
    }
}


void htd::LimitMaximumIntroducedVertexCountOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(relevantVertices)

    apply(decomposition, labelingFunctions);
}

void htd::LimitMaximumIntroducedVertexCountOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::LimitMaximumIntroducedVertexCountOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::LimitMaximumIntroducedVertexCountOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    std::vector<htd::vertex_t> introduceNodes;

    const htd::ConstCollection<htd::vertex_t> & introduceNodeCollection = decomposition.introduceNodes();

    std::copy(introduceNodeCollection.begin(), introduceNodeCollection.end(), std::back_inserter(introduceNodes));

    for (htd::vertex_t node : introduceNodes)
    {
        if (treatLeafNodesAsIntroduceNodes_ || !decomposition.isLeaf(node))
        {
            std::vector<htd::vertex_t> bagContent;

            const std::vector<htd::vertex_t> & bag = decomposition.bagContent(node);

            std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

            std::size_t introducedVertexCount = decomposition.introducedVertexCount(node);

            if (introducedVertexCount > limit_)
            {
                std::vector<htd::vertex_t> introducedVertices;

                decomposition.copyIntroducedVerticesTo(introducedVertices, node);

                std::size_t remainder = introducedVertexCount % limit_;

                introducedVertexCount -= remainder;

                std::size_t intermediatedVertexCount = introducedVertexCount / limit_;

                if (intermediatedVertexCount > 0)
                {
                    intermediatedVertexCount--;
                }

                if (remainder == 0)
                {
                    intermediatedVertexCount--;
                }

                std::vector<htd::vertex_t> children;

                const htd::ConstCollection<htd::vertex_t> & childContainer = decomposition.children(node);

                std::copy(childContainer.begin(), childContainer.end(), std::back_inserter(children));

                if (children.empty())
                {
                    auto start = introducedVertices.begin();
                    auto finish = introducedVertices.begin() + (remainder > 0 ? remainder : limit_);

                    htd::vertex_t newNode = decomposition.addChild(node);

                    decomposition.bagContent(newNode) = std::vector<htd::vertex_t>(start, finish);

                    htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                    newInducedHyperedges.restrictTo(std::vector<htd::vertex_t>(start, finish));

                    decomposition.inducedHyperedges(newNode) = std::move(newInducedHyperedges);

                    for (auto & labelingFunction : labelingFunctions)
                    {
                        htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                        htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newNode), *labelCollection);

                        delete labelCollection;

                        decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                    }

                    if (intermediatedVertexCount > 0)
                    {
                        std::advance(finish, limit_);

                        for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                        {
                            newNode = decomposition.addParent(newNode);

                            decomposition.bagContent(newNode) = std::vector<htd::vertex_t>(start, finish);

                            htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                            newInducedHyperedges.restrictTo(std::vector<htd::vertex_t>(start, finish));

                            decomposition.inducedHyperedges(newNode) = std::move(newInducedHyperedges);

                            for (auto & labelingFunction : labelingFunctions)
                            {
                                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                                htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newNode), *labelCollection);

                                delete labelCollection;

                                decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                            }

                            if (index < introducedVertexCount + limit_)
                            {
                                std::advance(finish, limit_);
                            }
                        }
                    }
                }
                else if (children.size() == 1)
                {
                    htd::vertex_t child = children[0];

                    auto start = introducedVertices.begin();
                    auto finish = introducedVertices.begin() + (remainder > 0 ? remainder : limit_);

                    htd::vertex_t newNode = decomposition.addParent(child);

                    std::vector<htd::vertex_t> newContent;

                    const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(child);

                    std::set_union(bagContent.begin(), bagContent.end(), start, finish, std::back_inserter(newContent));

                    decomposition.bagContent(newNode) = newContent;

                    htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                    newInducedHyperedges.restrictTo(newContent);

                    decomposition.inducedHyperedges(newNode) = std::move(newInducedHyperedges);

                    for (auto & labelingFunction : labelingFunctions)
                    {
                        htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                        htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                        delete labelCollection;

                        decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                    }

                    if (intermediatedVertexCount > 0)
                    {
                        std::advance(start, limit_);
                        std::advance(finish, limit_);

                        for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                        {
                            newNode = decomposition.addParent(newNode);

                            std::copy(start, finish, std::back_inserter(newContent));
                            std::inplace_merge(newContent.begin(), newContent.end() - std::distance(start, finish), newContent.end());

                            decomposition.bagContent(newNode) = newContent;

                            htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                            newInducedHyperedges.restrictTo(newContent);

                            decomposition.inducedHyperedges(newNode) = std::move(newInducedHyperedges);

                            for (auto & labelingFunction : labelingFunctions)
                            {
                                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                                htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                                delete labelCollection;

                                decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                            }

                            if (index < introducedVertexCount + limit_)
                            {
                                std::advance(start, limit_);
                                std::advance(finish, limit_);
                            }
                        }
                    }
                }
                else
                {
                    throw std::logic_error("void htd::LimitMaximumIntroducedVertexCountOperation::apply(htd::IMutableTreeDecomposition &) const");
                }
            }
        }
    }
}

void htd::LimitMaximumIntroducedVertexCountOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(relevantVertices)
    HTD_UNUSED(createdVertices)
    HTD_UNUSED(removedVertices)

    apply(decomposition, labelingFunctions);
}

bool htd::LimitMaximumIntroducedVertexCountOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::LimitMaximumIntroducedVertexCountOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::LimitMaximumIntroducedVertexCountOperation::removesTreeNodes(void) const
{
    return false;
}

bool htd::LimitMaximumIntroducedVertexCountOperation::modifiesBagContents(void) const
{
    return false;
}

bool htd::LimitMaximumIntroducedVertexCountOperation::createsLocationDependendLabels(void) const
{
    return false;
}

htd::LimitMaximumIntroducedVertexCountOperation * htd::LimitMaximumIntroducedVertexCountOperation::clone(void) const
{
    return new htd::LimitMaximumIntroducedVertexCountOperation(limit_);
}

#endif /* HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTEXCOUNTOPERATION_CPP */
