#ifndef _KDTREE_HPP_
    #define _KDTREE_HPP_
    #include "node.hpp"
    #include <iostream>
    #include <limits>
    using namespace std;
    template <size_t N, typename ElemType>
    class KDTree {
        private:
            
            

        public:
            Node<N,ElemType>* m_root = nullptr;
            size_t m_size;
            size_t m_dimension;
            /* Constructor and destructor */
            KDTree  ();
            ~KDTree ();

            /* Main functions */
            //typedef Node<N,ElemType> TNode;
            bool find(Node<N,ElemType>**&, Point<N,ElemType>&, size_t &level);
            
            bool insert (Point<N,ElemType>&);
            void del    (Point<N,ElemType>&);
            void clean  (Node<N,ElemType>*);

            void nearest_neighbor(size_t,Point<N,ElemType>&);
            void nearest_neighbor(Node<N,ElemType>*,size_t,Point<N,ElemType>&, Node<N,ElemType>* &candidate_node = nullptr, double best_distance = std::numeric_limits<double>::infinity());

            
            /* Getters */
            size_t get_size()         const;
            size_t get_dimension()    const;
            size_t get_numberPoints() const;
            
            
            /* Utilities */
            bool is_empty();
            // Printers
            void print_Contains();
            
            
            /* Overloads */

    };


    template <size_t N, typename ElemType>
    KDTree<N, ElemType>::KDTree() : m_root(nullptr), m_size(0), m_dimension(N) { }

    template <size_t N, typename ElemType>
    KDTree<N, ElemType>::~KDTree()
    {
        clean(m_root);
    }

    template <std::size_t N, typename ElemType>
    void KDTree<N, ElemType>::clean( Node<N,ElemType>* currNode) {
        if (currNode == NULL) return;
       
        clean(currNode->m_nodes[0]);
        clean(currNode->m_nodes[1]);
        
        delete currNode;
    }

    template <std::size_t N, typename ElemType>
    std::size_t KDTree<N, ElemType>::get_dimension() const {
        return N;
    }

    template <std::size_t N, typename ElemType>
    std::size_t KDTree<N, ElemType>::get_size() const {
        return m_size;
    }

    template <std::size_t N, typename ElemType>
    bool KDTree<N, ElemType>::is_empty() {
        return (m_size == 0);
    }

    template <std::size_t N, typename ElemType>
    bool KDTree<N, ElemType>::find( Node<N,ElemType>**  &current_Node,
                                    Point<N,ElemType>& point,
                                    size_t& level )
    {
        current_Node = &m_root;
        size_t current_level = -1;
        for (  current_Node = &m_root; 
              *current_Node && (*current_Node)->m_point != point;
               current_level = (*current_Node)->m_level,
               current_Node = &((*current_Node)->m_nodes[ point[current_level%m_dimension] > (*current_Node)->m_point[current_level%m_dimension]])) {};
        level = current_level;
        return !!*current_Node;
    }
    
    template <std::size_t N, typename ElemType>
    bool  KDTree<N, ElemType>::insert(Point<N,ElemType>& point)
    {
        size_t currLevel;
        Node<N,ElemType>** current_Node;

        if (find(current_Node,point, currLevel)) return 0;
        
        Node<N,ElemType>* newNode = new Node<N,ElemType>(point,currLevel + 1);
       
        *current_Node = newNode;

        return 1;
    }


    template <std::size_t N, typename ElemType>
    void KDTree<N, ElemType>::nearest_neighbor( 
                                        Node<N,ElemType>* current_node,
                                        size_t depth,
                                        Point<N,ElemType>& key,
                                        Node<N,ElemType>* &candidate_node,
                                        double best_distance)
    {
        
        if (!current_node)
            return;
        
        if (euclideanDistance(current_node->m_point, key) < best_distance)
        {
            best_distance = euclideanDistance(current_node->m_point, key);
            candidate_node = current_node;
        }

        int axis = depth % m_dimension;
        bool right = false;
        
        if (key[axis] < current_node->m_point[axis]) 
        {
            right = true;
            nearest_neighbor(current_node->m_nodes[0], ++depth, key, candidate_node, best_distance);
        } 
        else 
        {
            right = false;
            nearest_neighbor(current_node->m_nodes[1], ++depth, key, candidate_node, best_distance);
        }

        if (fabs(current_node->m_point[axis] - key[axis]) < best_distance) 
        {
            if (right)
                nearest_neighbor(current_node->m_nodes[0], ++depth, key, candidate_node, best_distance);
            else
                nearest_neighbor(current_node->m_nodes[1], ++depth,key,  candidate_node, best_distance);
        }
    }

#endif