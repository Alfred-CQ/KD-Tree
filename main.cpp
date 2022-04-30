#include <iostream>
#include <vector>

#include "kdtree.hpp"

using namespace std;
int main()
{
  
    const size_t N = 2;
    int coord[][N] = { {40,45},{15,70},{70,10},{69,50},{66,85},{85,90} }; 
    const size_t M = sizeof(coord)/sizeof(coord[0]);
    
    vector<Point<N,int>> myPoints(M);

    for (int i = 0; i < M; ++i)
        myPoints[i] = Point<N,int> (coord[i]);
    
    for (int i = 0; i < M; ++i)
        myPoints[i].printContent();

    KDTree<N,int> myKDTree;

    for (int i = 0; i < M; ++i)
        cout << "Status: " << myKDTree.insert(myPoints[i]) << endl; 
    
    Node<N,int>* myNode = nullptr;
    int coord_key[2] = {75,85};
    Point<N,int> key(coord_key);

    myKDTree.nearest_neighbor(myKDTree.m_root,2,key,myNode); 

    cout << "NN: ";
    myNode->m_point.printContent();
    cout << endl;
    
    return 0;
}