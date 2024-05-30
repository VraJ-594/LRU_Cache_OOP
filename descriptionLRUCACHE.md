
Least Recently Used(LRU) Cache

How LRU Cache works:

We have two operations in LRU 
1) PUT(key,data) -> here we insert data into LRU now if key has alreay data then we update key value 
                    else we just insert new data corresponding to key
                    -> if size is full :
                                      then remove least recently used data and then insert new data
                    -> else :          
                             we just insert the new data
2) GET(key)     -> get the data corresponding to the given key
                    -> if data is present :
                                          give the required data
                    -> else :
                             give not present in the LRU Cache exception


How my Code works:

1) I will create a DLL(Double Linked List) with head and tail node as reference nodes
   along with Hashmap to track if key has corresponding data or not.

2) define a LRU_CACHE_MAX_SIZE which defines maximum size of LRU Cache.

3) In PUT query :  
                    -> if already present in hashmap then delete node and insert at head as least recent used.
                    -> if current size if less than max size then insert after head directly.
** most important   -> if current size reached maximum size then delete least recently used and insert new node after head.

4) In GET query :
                    -> if key not found in hashmap return -1 as not present in LRU
                    -> if key found in hashmap then we need to update the LRU i.e and
                       delete and insert to get updated LRU Cache.


Thank you.

By Vraj K Dobariya (DAIICT)
Date: 30th May 2024


