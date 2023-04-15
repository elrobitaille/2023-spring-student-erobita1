// Edgar Robitaille
// erobita1
#ifndef TDATALOOP_H
#define TDATALOOP_H

#include <iostream>

/**
 * \class TDataLoop
 * \defgroup TDataLoop
 * \brief A templated dataloop
 */
template <typename DataType>
class TDataLoop {
public:
   /**
    * \brief The default constructor for TDataLoop.
    *
    * \detail The default constructor creates an empty TDataLoop, i.e. start is nullptr and count is 0.
    */
    TDataLoop(); 

   /**
    * \brief An alternate constructor
    *
    * \detail This alternate constructor creates a TDataLoop with one node that contains the parameter value. The node is dynamically allocated and should be the start of the loop. Its next and prev fields should point to itself.
    *
    * \param[in] data The templated value to be added to the TDataLoop
    */
    TDataLoop(const DataType & data);

   /**
    * \brief The copy constructor
    *
    * \detail The copy constructor creates a copy of the parameter TDataLoop (rhs)
    *
    * \param[in] rhs A constant reference to the function input TDataLoop object
    */ 
    TDataLoop(const TDataLoop<DataType> & rhs);


   /**
    * \brief Overloaded operator= to assign a TDataLoop to another TDataLoop
    *
    * \detail This overloaded operator assigns the input TDataLoop (rhs) to the current TDataLoop (*this, the current object).
    *
    * \note If the current TDataLoop is not empty, this function releases formerly allocated memory as needed to avoid memory leaks. 
    *
    * \param[in] rhs A constant reference to the input TDataLoop object
    *
    * \return A reference to the updated TDataLoop object
    */
    TDataLoop & operator=(const TDataLoop<DataType> & rhs);

    ~TDataLoop();

    bool operator==(const TDataLoop<DataType> & rhs) const;
    TDataLoop & operator+=(const DataType & data);
    TDataLoop operator+(const TDataLoop<DataType> & rhs) const;
    TDataLoop & operator^(int offset);
    TDataLoop & splice(TDataLoop<DataType> & rhs, size_t pos);
    
   /**
    * \brief Function length to report the number of nodes in *this DataLoop
    *
    * \return The number of nodes
    */
    int length() const { return count; }

   /**
    * \brief Overloaded output stream operator<< to print the TDataLoop
    *
    * \detail This operator prints the input TDataLoop (dl) to the ostream (os) in the format 
    * "-> data1 <--> data2 <--> ... <--> datax <-" where data1 is the value in the start node
    *   e.g. if we have a DataLoop with three elements 32, 12, 20 starting at 12
    *        it will print "-> 12 <--> 20 <--> 32 <-"
    *   If the TDataLoop is empty, it prints ">no values<".
    *
    * \param[in] os A reference to the output stream object
    * \param[in] q A constant reference to the DataLoop object to be printed
    *
    * \return A reference to the output stream object
    */
    friend std::ostream & operator<<(std::ostream & os, const TDataLoop<DataType> & dl)

private:
  // friend TDataLoopTest struct to allow the test struct access to the private data
  friend struct TDataLoopTest;
  
  /**
   * \struct _Node
   * \brief A private structure to represent a node in a DataLoop
   */
  struct _Node {
    int data;     ///< Integer node data
    _Node *next;  ///< A pointer to the next node
    _Node *prev;  ///< A pointer to the previous node
  };

  _Node* start;   ///< a pointer to the starting node position in the DataLoop
  size_t count;   ///< the count of how many nodes/values are in the structure
};

#include "TDataLoop.inc"

#endif // __TDATALOOP_H__