/*
 * File:   LabeledMultiHypergraphFactory.cpp
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

#ifndef HTD_HTD_LABELEDMULTIHYPERGRAPHFACTORY_CPP
#define HTD_HTD_LABELEDMULTIHYPERGRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/LabeledMultiHypergraphFactory.hpp>
#include <htd/LabeledMultiHypergraph.hpp>

htd::LabeledMultiHypergraphFactory::LabeledMultiHypergraphFactory(const htd::LibraryInstance * const manager) : htd::GraphTypeFactory<htd::ILabeledMultiHypergraph, htd::IMutableLabeledMultiHypergraph>(new htd::LabeledMultiHypergraph(manager))
{

}

htd::LabeledMultiHypergraphFactory::~LabeledMultiHypergraphFactory()
{

}

htd::IMutableLabeledMultiHypergraph * htd::LabeledMultiHypergraphFactory::createInstance(void) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutableLabeledMultiHypergraph();
#endif
}

htd::IMutableLabeledMultiHypergraph * htd::LabeledMultiHypergraphFactory::createInstance(std::size_t initialSize) const
{
    htd::IMutableLabeledMultiHypergraph * ret = createInstance();

    ret->addVertices(initialSize);

    return ret;
}

#endif /* HTD_HTD_LABELEDMULTIHYPERGRAPHFACTORY_CPP */
