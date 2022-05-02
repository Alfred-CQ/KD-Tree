/*
 * Node KDTree
 * Chillitupa Quispihuanca, Alfred Addison
 * Estructuras de Datos Avanzadas
 * CCOMP6-1
 * C++
 * Node.hpp
*/

#ifndef _NODE_HPP_
    #define _NODE_HPP_

    #include "Point.hpp"

    template <std::size_t N, typename ElemType>
    class Node {
        public:
            Point<N,ElemType> m_point;

            Node<N,ElemType>* m_nodes[2];

            std::size_t m_level = 0;


            Node();
            Node(Point<N,ElemType>& point, std::size_t level)
            {
                m_point = point;
                m_level = level; 
                m_nodes[0] = nullptr; m_nodes[1] = nullptr;
            };
    };

#endif