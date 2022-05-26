### lab1

> 完成时间：2022.05.26

#### 要求：

实现StreamReassembler类，该类的功能是将收到的segment重新排列，使得形成与sender端一致的字节顺序的数据写入ByteStream，使得receiver端可随时读取。而排列的根据就是每个字节的index。

实际上，sender会将数据端划分成若干片段(datagram)进行传送，但是由于网络的原因会使得这些datagram发生丢失、乱序、重传等等，所以receiver接收datagram后要进行处理，把其转化为一个完整正确的字节流。

#### 代码

> 代码的思路和一些debug出来的注意点

```cpp
/*stream_reassembler.hh*/
class StreamReassembler{
  private:
    // origin data member
    ByteStream _output;
    size_t _capacity;
    // my addition data member
    size_t _next_idx{0}; // 下一个写入ByteStream的字节的索引
    char* unassemble_buffer{nullptr}; // 数据缓冲区
    bool* occupied{nullptr}; // 辅助bool数组
    size_t begin{0}; // 指示数据缓冲区的开始
    size_t end{0}; // 指示数据缓冲区的结束
    bool _eof{false}; // 指示整个数据流的终止
    size_t buffer_bytes{0}; // 指示数据缓冲区中有效的字节数
  public:
    StreamReassembler(const size_t capacity);
    void push_substring(const std::string &data, const uint64_t index, const bool eof);
    const ByteStream &stream_out() const { return _output; }
    ByteStream &stream_out() { return _output; }
    size_t unassembled_bytes() const;
    bool empty() const;
};

/*stream_reassembler.cc*/
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof){
    // 1. 不要使用 strlen 来计算 data 长度
    size_t data_len = data.size();
    // 2. data为空时，提前判断，提前终止
    if(data_len == 0){
        if(eof) _eof = true;
        if(_eof && empty()) stream_out().end_input();
        return;
    }
    
    size_t begin_idx = index; 
    size_t end_idx = index + data_len - 1;
    // 3.两个情况都需要直接返回：1）该data已经push了 2）data的开始byte索引不在数据缓冲区的索引范围中
    if( begin_idx > _next_idx + _capacity - 1 ||
        end_idx < _next_idx ) return;
    
    size_t begin_pos; size_t j;
    if(begin_idx > _next_idx) { // 4. data的开始byte位于数据缓冲区的中间位置，即此情况不能形成新的连续的data写入ByteStream
        begin_pos = (begin + (begin_idx - _next_idx)) % _capacity;
        j = 0;
    } else { // 考虑data中部分bytes已经push过了，此情况是可以形成newly continuous data写入ByteStream
        begin_pos = begin;
        j = _next_idx - begin_idx;
    }
    
    size_t i = begin_pos;
    while(j < data_len){
    	if(occupied[i] == true){}
        else{
            unassemble_buffer[i] = data[j];
            occupied[i] = true;
            buffer_bytes ++;
        }
        i = (i + 1) % _capacity;
        if(i == begin) break; //5. 当i回到begin的位置，走完了数据缓冲区，应该退出循环，后面若还有bytes应该丢弃
        j ++;
    }
    
    if(eof) _eof = true;
    
    string written_data = "";
    size_t bgn = begin;
    while(occupied[bgn] == true){
        written_data += unassemble_buffer[bgn];
        bgn = (bgn + 1)% _capacity;
        if(bgn == begin) break;
    }
    size_t written_bytes_len = stream_out().write(written_data);
    // 6. 向ByteStream写完数据后，根据其接收的长度来更新StreamReassembler中的数据成员
    for(size_t m = 0; m < written_bytes_len; m++){
        occupied[begin] = false;
        begin = (begin + 1) % _capacity;
        end = (end + 1) % _capacity;
        buffer_bytes --;
        _next_idx ++;
    }
    // 7.所有数据写入ByteStream且整个数据流已经结束
    if(empty() && _eof){
        stream_out().end_input();
    }
}

size_t StreamReassembler::unassembled_bytes() const {
    return buffer_bytes;
}

bool StreamReassembler::empty() const {
    return buffer_bytes == 0;
}
```

#### 过程

lab1的重点在于 1. 数据缓冲区数据结构的设计 2.push_substring()函数的逻辑完整性

1、对于数据缓冲区的设计，思考之后还是选择了环形数组（不知道会不会后面lab翻车回来改），但是还加了一个bool数组做辅助，因为数据缓冲区中的数据是会间断存放的，用bool数组来记录各位置是否存放了有效byte。

2、对于push_substring()函数，从后期debug的过程来看，确实是需要考虑的方面很多，还是挺考验对于该函数功能的理解。

#### 结果

> 对于 t_address_dt 测试（是关于网络连接的）用了5秒多，应该是网络不顺畅的问题，和lab0中的webget一样。

```shell
cs144@cs144vm:~/sponge/build$ make check_lab1
[100%] Testing the stream reassembler...
Test project /home/cs144/sponge/build
      Start 18: t_strm_reassem_single
 1/16 Test #18: t_strm_reassem_single ............   Passed    0.00 sec
      Start 19: t_strm_reassem_seq
 2/16 Test #19: t_strm_reassem_seq ...............   Passed    0.00 sec
      Start 20: t_strm_reassem_dup
 3/16 Test #20: t_strm_reassem_dup ...............   Passed    0.00 sec
      Start 21: t_strm_reassem_holes
 4/16 Test #21: t_strm_reassem_holes .............   Passed    0.00 sec
      Start 22: t_strm_reassem_many
 5/16 Test #22: t_strm_reassem_many ..............   Passed    0.36 sec
      Start 23: t_strm_reassem_overlapping
 6/16 Test #23: t_strm_reassem_overlapping .......   Passed    0.00 sec
      Start 24: t_strm_reassem_win
 7/16 Test #24: t_strm_reassem_win ...............   Passed    0.37 sec
      Start 25: t_strm_reassem_cap
 8/16 Test #25: t_strm_reassem_cap ...............   Passed    0.07 sec
      Start 26: t_byte_stream_construction
 9/16 Test #26: t_byte_stream_construction .......   Passed    0.00 sec
      Start 27: t_byte_stream_one_write
10/16 Test #27: t_byte_stream_one_write ..........   Passed    0.00 sec
      Start 28: t_byte_stream_two_writes
11/16 Test #28: t_byte_stream_two_writes .........   Passed    0.00 sec
      Start 29: t_byte_stream_capacity
12/16 Test #29: t_byte_stream_capacity ...........   Passed    0.40 sec
      Start 30: t_byte_stream_many_writes
13/16 Test #30: t_byte_stream_many_writes ........   Passed    0.01 sec
      Start 53: t_address_dt
14/16 Test #53: t_address_dt .....................   Passed    5.04 sec
      Start 54: t_parser_dt
15/16 Test #54: t_parser_dt ......................   Passed    0.01 sec
      Start 55: t_socket_dt
16/16 Test #55: t_socket_dt ......................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 16

Total Test time (real) =   6.31 sec
[100%] Built target check_lab1
```







