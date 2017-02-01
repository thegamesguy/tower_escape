//
//  EnumHash.hpp
//  tower_escape
//
//  Created by Robert Wells on 31/01/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#ifndef EnumHash_hpp
#define EnumHash_hpp

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

#endif /* EnumHash_hpp */
