#ifndef _NODE_HPP_
    #define _NODE_HPP_

    #include "point.hpp"

    template <size_t N, typename ElemType>
    class Node {
        public:
            Point<N,ElemType> m_point;

            Node<N,ElemType>* m_nodes[2];

            int m_level = 0;


            Node();
            Node(Point<N,ElemType>& point, int level)
            {
                m_point = point;
                m_level = level; 
                m_nodes[0] = nullptr; m_nodes[1] = nullptr;
            };
    };

#endif