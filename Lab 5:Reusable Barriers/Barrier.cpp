// Barrier.cpp --- 
// 
// Filename: Barrier.cpp
// Description: 
// Author: Joseph
// Maintainer: 
// Created: Tue Jan  8 12:14:02 2019 (+0000)
// Version: 
// Package-Requires: ()
// Last-Updated: Tue Jan  8 12:15:21 2019 (+0000)
//           By: Joseph
//     Update #: 2
// URL: 
// Doc URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change Log:
// 
// 
// 
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
// 
// 

// Code:
#include "Semaphore.h"
#include "Barrier.h"
Barrier::Barrier(int numThreads) :numThreads(numThreads),
 semOne(std::shared_ptr<Semaphore>(new Semaphore(0))),
 semTwo(std::shared_ptr<Semaphore>(new Semaphore(1))),
mutexLock(std::shared_ptr<Semaphore>(new Semaphore(1))){
}
/*! semTwo and mutexLock are initialised as 1*/
Barrier:: ~Barrier() {}				   
void Barrier::wait() {
  semTwo->Wait();
  /*! semTwo waits for signal to allow it through,first to arrive is allowed through due to semTwo being initialised to 1*/
  mutexLock->Wait();
  /*! mutexLock creats a mutual exclusion on count++ */
  count ++;
  mutexLock->Signal();
  /*! if the count is equal to the num of threads then semOne is signalled allowing the threads through the second block in the barrier */
  /*! otherwise semTwo is signalled allowing another thread into the barrier */
  if(count == numThreads)
		{
		  semOne->Signal();
		 
		}
  else{
    semTwo->Signal();
  }
 

  semOne->Wait();
  /*! mutexLock creats mutual exclusion on count -- */
  mutexLock->Wait();
  count--;
  mutexLock->Signal();
  /*! if count is equla to 0 the semTwo is signalled allowing the threads to leave the bottom block of the barrier. */
  /*! otherwise semOne is signalled to allow another through*/
  if (count == 0){
    semTwo->Signal();
  }
  else{
    semOne->Signal();
  }
  
  semTwo->Wait();
  semTwo->Signal();
  /*! semTwo is signalled one last time in order to ensure the barrier is reusable by reinitialising semTow to 1 for the next time */
  

}

  // 
// Barrier.cpp ends here
