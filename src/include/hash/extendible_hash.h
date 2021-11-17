/*
 * extendible_hash.h : implementation of in-memory hash table using extendible
 * hashing
 *
 * Functionality: The buffer pool manager must maintain a page table to be able
 * to quickly map a PageId to its corresponding memory location; or alternately
 * report that the PageId does not match any currently-buffered page.
 */

#pragma once

#include <cstdlib>
#include <vector>
#include <string>
#include <map>
#include <mutex>
#include <iostream>
#include <memory>

#include "hash/hash_table.h"

namespace scudb {

    template <typename K, typename V>
    class ExtendibleHash : public HashTable<K, V> {
        struct Bucket {
            Bucket() = default;
            explicit Bucket(size_t i, int d) : id(i), depth(d) {}
            std::map<K, V> items;         
            size_t id = 0;                
            int depth = 0;                
        };
    public:
        // constructor
        ExtendibleHash(size_t size);

        // helper function to generate hash addressing
        size_t HashKey(const K &key);

        // helper function to get global & local depth
        int GetGlobalDepth() const;
        int GetLocalDepth(int bucket_id) const;
        int GetNumBuckets() const;
        // lookup and modifier
        bool Find(const K &key, V &value);
        bool Remove(const K &key);
        void Insert(const K &key, const V &value);

        

    private:
        mutable std::mutex mutex_;      

        const size_t bucket_size_;    

        int bucket_count_;   

        size_t pair_count_;    

        int depth;             

        std::vector<std::shared_ptr<Bucket>> bucket_;    
        std::shared_ptr<Bucket> split(std::shared_ptr<Bucket> &); 
    };
} // namespace scudb
