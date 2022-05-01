#ifndef _KDTREE_HPP_
    #define _KDTREE_HPP_
    #include "node.hpp"
    #include <iostream>
    #include <limits>
    #include <map>
    #include <utility>


    using namespace std;
    template <size_t N, typename ElemType>
    class KDTree {
        private:

            void nearest_neighbor(Node<N,ElemType>*,size_t,Point<N,ElemType>&, Node<N,ElemType>* &candidate_node = nullptr, double best_distance = std::numeric_limits<double>::infinity());
            void k_nearest_neighbor(Node<N,ElemType>*,size_t,Point<N,ElemType>&,map<double, Point<N,ElemType>*>&, size_t k,double best_distance = std::numeric_limits<double>::infinity());

            

        public:
            Node<N,ElemType>* m_root = nullptr;
            size_t m_size;
            size_t m_dimension;

            typedef pair<double, Point<N,ElemType>*> pa;
            map<double, Point<N,ElemType>*> knn;
            map<double, Point<N,ElemType>*> rq;
            /* Constructor and destructor */
            KDTree  ();
            ~KDTree ();

            /* Main functions */
            //typedef Node<N,ElemType> TNode;
            bool find(Node<N,ElemType>**&, Point<N,ElemType>&, size_t &level);
            bool insert (Point<N,ElemType>&);
            bool del    (Point<N,ElemType>&);

            void clean  (Node<N,ElemType>*);

            double nearest_neighbor(Point<N,ElemType>&, Node<N,ElemType>* &node = nullptr);   
            void k_nearest_neighbor(size_t,Point<N,ElemType>&);
            
            void range_query(double,Point<N,ElemType>&);
            void range_query(Node<N,ElemType>*,size_t,Point<N,ElemType>&,map<double, Point<N,ElemType>*>&, double);

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
    bool  KDTree<N, ElemType>::del(Point<N,ElemType>& point)
    {
        size_t currLevel;
        Node<N,ElemType>** current_Node;

        if (!find(current_Node,point, currLevel)) return 0;

        if ((*current_Node)->m_nodes[0] && (*current_Node)->m_nodes[1]) 
        {
            Node<N,ElemType>* q = nullptr;//getChange(p);
            (*current_Node)->m_point = (*q)->m_point;
            current_Node = q;
        }

        Node<N,ElemType>* t = *current_Node;
        *current_Node = (*current_Node)->m_nodes[!(*current_Node)->m_nodes[0]];
        delete t;

        return 1;
    }

    template <std::size_t N, typename ElemType>
    double KDTree<N, ElemType>::nearest_neighbor(Point<N,ElemType>& key, Node<N,ElemType>* &node)
    {
        nearest_neighbor(m_root,0,key,node);
        return euclideanDistance(node->m_point,key);
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



    template <std::size_t N, typename ElemType>
    void KDTree<N, ElemType>::k_nearest_neighbor(size_t k, Point<N,ElemType>& key)
    {
        k_nearest_neighbor(m_root,0,key,knn,k);
    }
    
    template <std::size_t N, typename ElemType>
    void KDTree<N, ElemType>::k_nearest_neighbor(   Node<N,ElemType>* current_node,
                                                    size_t depth,
                                                    Point<N,ElemType>& key,
                                                    map<double, Point<N,ElemType>*>& myMap,
                                                    size_t k,
                                                    double best_distance)
    {
        if (!current_node)
            return;
        
        if (euclideanDistance(current_node->m_point, key) < best_distance)
        {
            best_distance = euclideanDistance(current_node->m_point, key);
           
            if(myMap.size() < k)
                myMap.insert(make_pair(euclideanDistance(current_node->m_point, key),&current_node->m_point));
            else
            {
                auto beg = myMap.begin();
                auto end = myMap.end();

                if (beg->first > best_distance)
                {
                    end--;
                    myMap.erase(end);
                    myMap.insert(make_pair(euclideanDistance(current_node->m_point, key),&current_node->m_point));
            
                }
                
            }
        }
     
        int axis = depth % m_dimension;
        bool right = false;
        
        if (key[axis] < current_node->m_point[axis]) 
        {
            right = true;
            k_nearest_neighbor(current_node->m_nodes[0], ++depth, key, myMap,k,best_distance);
        } 
        else 
        {
            right = false;
            k_nearest_neighbor(current_node->m_nodes[1], ++depth, key, myMap,k,best_distance);
        }

        if (fabs(current_node->m_point[axis] - key[axis]) < best_distance) 
        {
            if (right)
                k_nearest_neighbor(current_node->m_nodes[0], ++depth, key, myMap,k,best_distance);
            else
                k_nearest_neighbor(current_node->m_nodes[1], ++depth, key, myMap,k,best_distance);
        }
    }

    template <std::size_t N, typename ElemType>
    void KDTree<N, ElemType>::range_query(double max,Point<N,ElemType>& key)
    {
        range_query(m_root,0,key,rq,max);
    }

    template <std::size_t N, typename ElemType>
    void KDTree<N, ElemType>::range_query(Node<N,ElemType>* current_node,size_t depth,Point<N,ElemType>& key,map<double, Point<N,ElemType>*>& myMap, double max)
    {
         if (!current_node)
            return;
        
        if (euclideanDistance(current_node->m_point, key) < max)
            myMap.insert(make_pair(euclideanDistance(current_node->m_point, key),&current_node->m_point));
           
     
        int axis = depth % m_dimension;
        bool right = false;
        
        if (key[axis] < current_node->m_point[axis]) 
        {
            right = true;
            range_query(current_node->m_nodes[0], ++depth, key, myMap,max);
        } 
        else 
        {
            right = false;
            range_query(current_node->m_nodes[1], ++depth, key, myMap,max);
        }

        if (fabs(current_node->m_point[axis] - key[axis]) < max) 
        {
            if (right)
                range_query(current_node->m_nodes[0], ++depth, key, myMap,max);
            else
                range_query(current_node->m_nodes[1], ++depth, key, myMap,max);
        }
    }

#endif