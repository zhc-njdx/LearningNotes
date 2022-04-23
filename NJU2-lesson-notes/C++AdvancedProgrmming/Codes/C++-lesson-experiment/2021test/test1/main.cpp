#include <iostream>
#include <cstring>
using namespace std;
static int * heap;
static int heap_size = 0;
#define GET_SIZE(x) ((x >> 3) & (0xffffffff))
#define GET_ISFREE(x) (x & 0x00000001)
//19in 12in
void init_heap();
void show();
int alloc(int obj_id, int obj_size);
bool free(int obj_id, int block_addr);

int main(){
    int obj_max_num = 0;
    int cmd_num = 0;
    cin >> heap_size >> obj_max_num >> cmd_num;
    init_heap();
    int *objs = new int[obj_max_num+1];
    for(int i = 0; i < obj_max_num + 1; i++) objs[i] = -1;
    while(cmd_num -- > 0){
        string cmd;
        cin >> cmd;
        if(cmd == "ALLOC"){
            int obj_id = 0;
            int obj_size = 0;
            cin >> obj_id >> obj_size;
            int addr = alloc(obj_id, obj_size);
            if(addr != -1) {
                objs[obj_id] = addr;
                cout << "succeeded to alloc object " << obj_id << endl;
            }
            else cout << "failed to alloc object " << obj_id << endl;
        } else if(cmd == "FREE"){
            int obj_id = 0;
            cin >> obj_id;
            int res = free(obj_id, objs[obj_id]);
            if(res) cout << "succeeded to free object " << obj_id << endl;
            else cout << "invalid memory access" << endl;
        } else if(cmd == "SHOW"){
            show();
        }
    }
    delete[] heap;
    delete[] objs;
    heap = nullptr;
    objs = nullptr;
}

void init_heap(){
    // alloc memory
    int len = heap_size / 4;
    heap = new int[len];
    // calc empty 8-byte nums => header and tail
    int empty8bytes = ( heap_size - 8 ) / 8;
    int header = (empty8bytes << 3) | (0);
    int tail = header;
    // add header and tail
    heap[0] = header;
    heap[len - 1] = tail;
    // init the other memory
    for(int i = 1; i < len - 1; i++){
        heap[i] = 0xdfdfdfdf;
    }
}

void show(){
    int len = heap_size / 4;
    for(int i = 0; i < len; i++){
        printf("%08x\n",heap[i]);
    }
}

int alloc(int obj_id, int obj_size){
    int format_size = (obj_size / 8) + (obj_size % 8 == 0 ? 0 : 1);
    int i = 0;
    bool isHeader = true;
    int len = heap_size / 4;
    while (i < len){
            int block_size = GET_SIZE(heap[i]);
            int block_isfree = GET_ISFREE(heap[i]);
            if(block_isfree == 1) { // block is not free
                i += block_size * 2 + 1 + 1;
            } else if(block_size < format_size){ // block is to small
                i += block_size * 2 + 1 + 1;
            } else if (block_size == format_size){
                int info = heap[i] | (0x00000001);
                heap[i] = info;
                heap[i + 2 * block_size + 1] = info;
                return i;
            } else if(block_size > format_size) { // block is fit
                int new_info = (format_size << 3) | (1); // new block info
                int new_block_header = i;
                int new_block_tail = i + format_size * 2 + 1;
                heap[new_block_header] = new_info;
                heap[new_block_tail] = new_info;

                int old_block_size = block_size - (format_size + 1);
                int old_info = (old_block_size << 3) | (0); // old block info
                int old_block_header = new_block_tail + 1;
                int old_block_tail = old_block_header + 2 * old_block_size + 1;
                heap[old_block_header] = old_info;
                heap[old_block_tail] = old_info;
                return new_block_header;
            }
    }
    return -1;
}


bool free(int obj_id, int block_addr){
    // cout << "block_addr: " << block_addr << endl;
    if(block_addr == -1) return false;
    int block_size = GET_SIZE(heap[block_addr]);
    int block_isfree = GET_ISFREE(heap[block_addr]);
    if(block_isfree == 0) return false;
    heap[block_addr] &= (0xfffffffe);
    heap[block_addr + block_size * 2 + 1] = heap[block_addr];
    return true;
}