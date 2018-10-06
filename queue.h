/***********************************************************************
 * Header:
 *    Stack
 * Summary:
 *    This class contains the notion of an array: a bucket to hold
 *    buffer for the user. This is just a starting-point for more advanced
 *    constainers such as the stack, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       array             : similar to std::array
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

int main(int argc, const char* argv[]); //Bro. Barney's code
namespace custom
{

   /************************************************
    * QUEUE
    * A class that holds stuff
    ***********************************************/
   template <class T>
      class queue
   {
#ifdef UNIT_TESTING //befriending the debug code
      friend int ::main(int argc, const char* argv[]); //befriend the debug code
#endif //befriending the debug code
     private:
      T * buffer;                           //dynamically allocated buffer of T
      int numElements;                      //the number of elements
      int numCapacity;                      //the capacity of the stack
      int numPop;
      int numPush;

      //RESIZE
      void resize(int numCapacity)
      {         
         if (numCapacity < 0)
         {
            return;
         }
         else if (numCapacity == 0)
         {

            this->numCapacity = numCapacity;
            //this->numElements = numCapacity;
            this->numPop = 0;//numCapacity;
            this->numPush= 0;//numCapacity;
            this->buffer = NULL;
         }
         else
         {
            int aSize = size();
            //this-> numCapacity << 1;
            //this->numCapacity = numCapacity;

            T * newBuffer;

            newBuffer = new T[numCapacity];
            //int aSize = size();
            for (int i = 0; i < aSize; ++i)
            {
               newBuffer[i] = buffer[this->iHead()];
               this->pop();
               std::cout << newBuffer[i] << std::endl;
            }
            buffer = newBuffer;
            this->numCapacity = numCapacity;
            //delete buffer;        
            if (numCapacity < aSize)
            {
               numPush = numCapacity;
               numPop =0;
            }
            else if (numCapacity > aSize)
            {
               numPush = aSize;
               numPop =0;
            }
            // buffer = newBuffer;
         }
         
      
      }//end of resize

     public:
      // constructors and destructors
      queue() {numCapacity = 0;   numPop = 0; numPush = 0;  buffer = NULL; }
      //default constructor
      queue(int numCapacity)           throw (const char *); //non-default constructor
      //stack(int numElements, T t)      throw (const char *); //non-default constructor
      queue(const queue & rhs)        throw (const char *); //copy constructor
      ~queue()                         { delete [] buffer;   } //destructor
      queue & operator = (const queue & rhs) throw (const char *);

      // standard container interfaces
      int  size()     const { return numPush - numPop;}
      int  capacity() const { return numCapacity;}
      bool empty() const {return numPush - numPop == 0;}

      void clear() { numPush = 0; numPop = 0; }

      // a debug utility to display the array
      // this gets compiled to nothing if NDEBUG is defined
      void display() const;
      int iHead()
      {
         return numPop % numCapacity;
      }

      int iTail()
      {
         return (numPush - 1) % numCapacity;

      }
      
      void pop()
      {
         if (!empty())
            ++numPop;
      }

      //PUSH
      void push(T t)
      {
         if (numCapacity == 0)
         {
            resize(1);
            buffer[iTail()] = t;
         }
         else if (size() >= numCapacity)
         {
            resize(numCapacity<< 1);
            buffer[iTail()] = t;
         }
         else
         {
            buffer[iTail()] = t;
         }
         ++numPush;
      }
      T& front() throw (const char *)
      {
         if(buffer == NULL)
         {
            throw"ERROR: Unable to reference the element from an empty Queue";
         }
         else
         {
            return buffer[iHead()];
         }
      }

      const T& front() const throw (const char *)
      {
         if(buffer == NULL)
         {
            throw"ERROR: Unable to reference the element from an empty queue";
         }
         else
         {
            return buffer[iHead()];
         }
      }

      T& back() throw (const char *)
      {
         if(buffer == NULL)
         {
            throw"ERROR: Unable to reference the element from an empty Queue";
         }
         else
         {
            return buffer[iTail()];
         }
      }

      const T& back() const throw (const char *)
      {
         if(buffer == NULL)
         {
            throw"ERROR: Unable to reference the element from an empty queue";
         }
         else
         {
            return buffer[iTail()];
         }
      }
      
   };

   /*******************************************
    * QUEUE :: Assignment
    *******************************************/
   template <class T>
      queue <T> & queue <T> :: operator = (const queue <T> & rhs)
      throw (const char *)
   {
      if (rhs.size() != this->numCapacity)
      {
         resize(rhs.size());
      }

      /*
        if (this->numElements!= rhs.numElements)
        {
        this->numElements = rhs.numElements;
        }
      */

      // we can only copy arrays of equal size. Vectors are not this way!
      /*
        if (rhs.size() != size())
        {
        throw "ERROR: Unable to copy vectorss of different sizes";
        }
      */
      //assert(numElements == rhs.numElements);

      if (this->numCapacity > rhs.numElements)
      {
         resize(rhs.numElements);
         this->numCapacity = rhs.numElements;
         this->numElements = rhs.numElements;
      }

      // copy the items over one at a time using the assignment operator
      for (int i = rhs.numPop; i < rhs.numPush; i++)
         buffer[i] = rhs.buffer[i];
   }

   /*******************************************
    * stack :: COPY CONSTRUCTOR
    *******************************************/
   template <class T>
      queue <T> :: queue(const queue <T> & rhs) throw (const char *)
   {
      assert(rhs.numCapacity >= 0);

      // do nothing if there is nothing to do
      if (rhs.numCapacity == 0)
      {
         numElements = 0;
         buffer = NULL;
         return;
      }

      // attempt to allocate
         try
         {
            buffer = new T[rhs.numCapacity];
         }
         catch (std::bad_alloc)
         {
            throw "ERROR: Unable to allocate buffer";
         }

         // copy over the capacity
         numCapacity = rhs.numCapacity;
         numElements = rhs.numElements;
         if (numCapacity > rhs.numElements){
            resize(rhs.numElements);                 //resizing twice!!!
            this->numCapacity = rhs.numElements;
            this->numElements = rhs.numElements;
         }

         // copy the items over one at a time using the assignment operator
         for (int i = 0; i < numElements; i++)
            buffer[i] = rhs.buffer[i];
   }

   /**********************************************
    * stack : NON-DEFAULT CONSTRUCTOR
    * Preallocate the array to "capacity"
    **********************************************/
   template <class T>
      queue <T> :: queue(int numCapacity) throw (const char *)
   {

      //assert(numCapacity >= 0);
      if (numCapacity < 0)
         throw "Error: stack sizes must be greater than or equal to 0.";

      // do nothing if there is nothing to do.
      // since we can't grow an array, this is kinda pointless
      else if (numCapacity == 0)
      {
         this->numElements = 0;
         //this->buffer = NULL;
         return;
      }

      else if (numCapacity >0)
      {
         this->numCapacity = numCapacity;
         this->numElements = 0;
         //this->buffer = NULL;
      }

      // attempt to allocate
         try
         {
            buffer = new T[numCapacity];
         }
         catch (std::bad_alloc)
         {
            throw "ERROR: Unable to allocate buffer";
         }


         // copy over the stuff
         this->numElements = numElements;
   }

   /********************************************
    * QUEUE : DISPLAY
    * A debug utility to display the contents of the stack
    *******************************************/
   template <class T>
      void queue <T> :: display() const
   {
      #ifndef NDEBUG
      std::cerr << "stack<T>::display()\n";
      std::cerr << "\tnum = " << numElements << "\n";
      for (int i = 0; i < numElements; i++)
         std::cerr << "\tbuffer[" << i << "] = " << buffer[i] << "\n";
#endif // NDEBUG
   }

}; // namespace custom

#endif // STACK_H
