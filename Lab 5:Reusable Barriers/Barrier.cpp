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
Barrier:: ~Barrier() {}				   
void Barrier::wait() {
  semTwo->Wait();

  mutexLock->Wait();
  count ++;
  mutexLock->Signal();

  if(count == numThreads)
		{
		  semOne->Signal();
		 
		}
  else{
    semTwo->Signal();
  }
 

  semOne->Wait();
  mutexLock->Wait();
  count--;
  mutexLock->Signal();
  
  if (count == 0){
    semTwo->Signal();
  }
  else{
    semOne->Signal();
  }
  
  semTwo->Wait();
  semTwo->Signal();
  

}

  // 
// Barrier.cpp ends here
