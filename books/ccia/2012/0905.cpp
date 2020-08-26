template<typename T>
struct sorter
{
    thread_pool pool;

    std::list<T> do_sort(std::list<T>& chunk_data)
    {
        if(chunk_data.empty())
        {
            return chunk_data;
        }

        // 1. splice result list to input list
        std::list<T> result;
        result.splice(result.begin(),chunk_data,chunk_data.begin());

        // 2. choose the first as pivot and partition the list
        T const& partition_val=*result.begin();
        typename std::list<T>::iterator divide_point=
            std::partition(chunk_data.begin(),chunk_data.end(), [&](T const& val){return val<partition_val;});

        // 3. splict the list -> new lower chunk and new higher chunk (chunk data it self)
        std::list<T> new_lower_chunk;
        new_lower_chunk.splice(new_lower_chunk.end(), chunk_data, chunk_data.begin(), divide_point);

        // 4. submit the lower chunk to thread pool to handle
        thread_pool::task_handle<std::list<T>> new_lower=
            pool.submit(std::bind(&sorter::do_sort,this,std::move(new_lower_chunk)));

        // 5. sort the higher chunk
        std::list<T> new_higher(do_sort(chunk_data));

        // 6. splice new higher to the result list
        result.splice(result.end(),new_higher);

        // 7. wait and run then splice the new lower to the result list
        while(!new_lower.is_ready())
        {
            pool.run_pending_task();
        }
        result.splice(result.begin(),new_lower.get());

        return result;
    }
};

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
    if(input.empty())
    {
        return input;
    }
    sorter<T> s;
    return s.do_sort(input);
}

