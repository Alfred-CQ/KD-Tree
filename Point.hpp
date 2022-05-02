/*
 * Punto N Dimensional
 * Chillitupa Quispihuanca, Alfred Addison
 * Estructuras de Datos Avanzadas
 * CCOMP6-1
 * C++
 * Point.hpp
*/

#ifndef _POINT_HPP_
    #define _POINT_HPP_

    #include <iostream>

    #include <math.h>
    
    template <std::size_t N, typename ElemType>
    class Point{
        
        private:
            ElemType* m_coordinates = new ElemType[N];
            

            std::size_t beg         = 0;
            std::size_t end         = N - 1;
        
        public:
            /* Constructors and Destructor */
            std::size_t m_size      = N;
            Point  ();
            Point  (ElemType*);
            
            ~Point ();
            
            /* Setters */
            bool setIndexValue (std::size_t, ElemType);

            /* Getters */
            std::size_t get_size()    const;
            ElemType*   get_content() const;

            /* Overloads */
            bool      operator ==  (const Point<N,ElemType>&);
            bool      operator !=  (const Point<N,ElemType>&);
            Point<N,ElemType>& operator =   (const Point<N,ElemType>&);
            ElemType  operator []  (size_t) const;
            ElemType& operator []  (size_t);

            /* Utilities */
            void printContent ();
            bool outOfBounds  (std::size_t);
    };

    /* Implementation - Constructors and Destructor */
    template <size_t N, typename ElemType>
    Point<N, ElemType>::Point()
    { 
        std::size_t i;
        for ( i = 0; i < m_size; ++i)
            m_coordinates[i] = 0;
    }

    template <size_t N, typename ElemType>
    Point<N, ElemType>::Point(ElemType coordinates[])
    { 
        std::size_t i;
        for ( i = 0; i < m_size; ++i)
            m_coordinates[i] = coordinates[i];
    }

    template <size_t N, typename ElemType>
    Point<N, ElemType>::~Point()
    { 
        delete [] m_coordinates;
    }

    /* Implementation - Setters */
    template <size_t N, typename ElemType>
    bool Point<N, ElemType>::setIndexValue(std::size_t index, ElemType value)
    { 
        if (outOfBounds(index))
            return 0;
        
        m_coordinates[index] = value;
    }

    /* Implementation - Getters */
    template <size_t N, typename ElemType>
    std::size_t Point<N, ElemType>::get_size() const
    {
        return m_size;
    }
           
    template <size_t N, typename ElemType>
    ElemType* Point<N, ElemType>::get_content() const
    {
        return m_coordinates;
    }

    /* Implementation - Overloads */
    template <size_t N, typename ElemType>
    bool Point<N, ElemType>::operator == (const Point<N,ElemType>& point) 
    {
        std::size_t i;

        for ( i = 0; i < m_size; ++i)
            if (m_coordinates[i] != point[i])
                return 0;
        
        return 1;
    }

    template <size_t N, typename ElemType>
    bool Point<N, ElemType>::operator != (const Point<N,ElemType>& point) 
    {
        return !(*this == point);
    }

    template <size_t N, typename ElemType>
    Point<N, ElemType>& Point<N, ElemType>::operator = (const Point<N,ElemType>& point)
    {
        if (*this == point)
            return *this;
        
        std::size_t i;
        for ( i = 0; i < m_size; ++i)
            m_coordinates[i] = point[i];

        return *this;
    }

    template <size_t N, typename ElemType>
    ElemType Point<N, ElemType>::operator[] (size_t index) const{
        return m_coordinates[index];
    }

    template <size_t N, typename ElemType>
    ElemType& Point<N, ElemType>::operator[] (size_t index){
        return m_coordinates[index];
    }

    /* Implementation - Utilities */
    template <size_t N, typename ElemType>
    bool Point<N, ElemType>::outOfBounds(std::size_t index)
    { 
        if (index >= m_size) 
        {
            std::cout << "Array index out of bound, exiting...\n";
            return 1;
        }
        return 0;
    }

    template <size_t N, typename ElemType>
    void Point<N, ElemType>::printContent()
    { 
        std::size_t i;
        
        std::cout << "{ ";
        for ( i = 0; i < m_size; ++i)
            std::cout << m_coordinates[i] << " ";
        std::cout << "}\n";
    }

    /** Implementation - Adicional **/
    template <size_t N, typename ElemType>
    double euclideanDistance(Point<N,ElemType>& x, Point<N,ElemType>& y)
    {
        double distance = 0.f;
        std::size_t i;

        for (i = 0; i < N; ++i)
            distance +=  ((x[i] - y[i])*(x[i] - y[i])); 
            
        distance = sqrt( distance );
        return distance;
    }

#endif