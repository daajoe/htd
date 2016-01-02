/* 
 * File:   VectorAdapterConstIteratorWrapper.hpp
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

#ifndef HTD_HTD_VECTORADAPTERCONSTITERATORWRAPPER_HPP
#define HTD_HTD_VECTORADAPTERCONSTITERATORWRAPPER_HPP

#include <htd/Globals.hpp>

#include <htd/ConstIteratorWrapper.hpp>

#include <iterator>
#include <memory>

namespace htd
{
    template <typename Iter, typename T = typename Iter::value_type, class Allocator = std::allocator<T>>
    class VectorAdapterConstIteratorWrapper : public virtual htd::ConstIteratorWrapper<Iter, T>
    {
        public:
            VectorAdapterConstIteratorWrapper(std::shared_ptr<std::vector<T, Allocator>> collection, Iter baseIterator) : htd::ConstIteratorWrapper<Iter, T>(baseIterator), collection_(collection)
            {

            }

            VectorAdapterConstIteratorWrapper(const VectorAdapterConstIteratorWrapper<Iter, T, Allocator> & original) : htd::ConstIteratorWrapper<Iter, T>(original), collection_(original.collection_)
            {

            }

            virtual ~VectorAdapterConstIteratorWrapper()
            {

            }

        private:
            std::shared_ptr<std::vector<T, Allocator>> collection_;
    };
}

#endif /* HTD_HTD_VECTORADAPTERITERATORWRAPPER_HPP */