#include <iostream>
#include <vector>

#include "kdtree.hpp"

using namespace std;
int main()
{
  
    const size_t N = 2; // Dimension
    int coord[][N] = { {40,45},{15,70},{70,10},{69,50},{66,85},{85,90},{70,10}}; // List of coord
    const size_t M = sizeof(coord)/sizeof(coord[0]);
    
    vector<Point<N,int>> myPoints(M); // Points

    for (int i = 0; i < M; ++i)
        myPoints[i] = Point<N,int> (coord[i]); // Make Points
    
    for (int i = 0; i < M; ++i)
        myPoints[i].printContent();


    KDTree<N,int> myKDTree;

    for (int i = 0; i < M; ++i)
        cout << "Status: " << myKDTree.insert(myPoints[i]) << endl; // Insert Points with status
    
    // Status 0 punto repetido


    Node<N,int>* myNode = nullptr;
    int coord_key[2] = {75,85};
    Point<N,int> key(coord_key);

    double distance = myKDTree.nearest_neighbor(key,myNode); 
    cout << "Distance: " << distance << endl;
    cout << "NN: ";
    myNode->m_point.printContent();
    cout << endl;
    
    myKDTree.k_nearest_neighbor(3,key);

    cout << "K(3)NN\n";

    for (std::map<double,Point<N,int>*>::iterator it=myKDTree.knn.begin(); it!=myKDTree.knn.end(); ++it)
    {    
        std::cout << it->first << " => ";
        it->second->printContent();
        cout << '\n';
    }

    cout << "K(2)NN\n";
    
    myKDTree.knn.clear();

    myKDTree.k_nearest_neighbor(2,key);

    for (std::map<double,Point<N,int>*>::iterator it=myKDTree.knn.begin(); it!=myKDTree.knn.end(); ++it)
    {    
        std::cout << it->first << " => ";
        it->second->printContent();
        cout << '\n';
    }
    double max = 100.f;
    cout << "RQ: " << max << endl;
    myKDTree.range_query(max,key);
    for (std::map<double,Point<N,int>*>::iterator it=myKDTree.rq.begin(); it!=myKDTree.rq.end(); ++it)
    {    
        std::cout << it->first << " => ";
        it->second->printContent();
        cout << '\n';
    }
    return 0;
}