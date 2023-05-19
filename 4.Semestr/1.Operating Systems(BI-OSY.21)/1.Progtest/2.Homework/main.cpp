#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cassert>
#include <cmath>
using namespace std;
#endif /* __PROGTEST__ */

struct BlockHeader {
    uint32_t size;
    bool free;
};

static const size_t kMinBlockSize = sizeof(BlockHeader);

void * heapStart = nullptr;
void * heapEnd = nullptr;

void HeapInit(void * memPool, int memSize) {
    auto * header = static_cast<BlockHeader*>(memPool);
    header->size = memSize - kMinBlockSize;
    header->free = true;

    heapStart = memPool;
    heapEnd = static_cast<uint8_t*>(memPool) + memSize;
}

void * HeapAlloc(int size) {
    const uint32_t kTotalSize = kMinBlockSize + size;
    auto * currentBlock = reinterpret_cast<BlockHeader*>(heapStart);
    BlockHeader * bestBlock = nullptr;

    if(size <= 0 || kTotalSize <= 0) {
        return nullptr;
    }

    if(heapStart == nullptr || heapEnd == nullptr || heapEnd <= heapStart) {
        return nullptr;
    }

    while (currentBlock != nullptr) {
        if (reinterpret_cast<uint8_t*>(currentBlock) + kTotalSize >= heapEnd) {
            return nullptr;
        }

        if (reinterpret_cast<uint8_t*>(currentBlock) >= heapEnd) {
            return nullptr;
        }

        if (currentBlock->free && currentBlock->size >= kTotalSize) {
            if (currentBlock->size > kTotalSize) {
                auto * nextBlock = reinterpret_cast<BlockHeader*>(reinterpret_cast<uint8_t*>(currentBlock) + kTotalSize);
                nextBlock->size = currentBlock->size - kTotalSize;
                nextBlock->free = true;
                currentBlock->size = size;
                currentBlock->free = false;
                return reinterpret_cast<uint8_t*>(currentBlock) + kMinBlockSize;
            } else {
                currentBlock->free = false;
                return reinterpret_cast<uint8_t*>(currentBlock) + kMinBlockSize;
            }
        }

        currentBlock = reinterpret_cast<BlockHeader*>(reinterpret_cast<uint8_t*>(currentBlock) + currentBlock->size + kMinBlockSize);
    }

    return nullptr;
}

bool HeapFree(void * blk) {
    if (blk < heapStart || blk >= heapEnd || heapStart == nullptr) {
        return false;
    }

    auto * currentBlock = reinterpret_cast<BlockHeader*>(reinterpret_cast<uint8_t*>(blk) - kMinBlockSize);

    if(currentBlock == nullptr || currentBlock->size == 0 || currentBlock->free) {
        return false;
    }

    currentBlock->free = true;

    auto * nextBlock = reinterpret_cast<BlockHeader*>(reinterpret_cast<uint8_t*>(currentBlock) + currentBlock->size + sizeof(BlockHeader));

    if (nextBlock < heapEnd && nextBlock->free) {
        currentBlock->size += nextBlock->size + sizeof(BlockHeader);
    }

    auto * prevBlock = reinterpret_cast<BlockHeader*>(heapStart);

    while (prevBlock < currentBlock && prevBlock->free &&
           reinterpret_cast<uint8_t*>(prevBlock) + prevBlock->size + sizeof(BlockHeader) < reinterpret_cast<uint8_t*>(currentBlock)) {
        prevBlock = reinterpret_cast<BlockHeader*>(reinterpret_cast<uint8_t*>(prevBlock) + prevBlock->size + kMinBlockSize);
    }

    if (prevBlock != currentBlock && prevBlock->free) {
        prevBlock->size += currentBlock->size + kMinBlockSize;
        currentBlock = prevBlock;
    }

    auto * nextNextBlock = reinterpret_cast<BlockHeader*>(reinterpret_cast<uint8_t*>(currentBlock) + currentBlock->size + sizeof(BlockHeader));
    if (nextNextBlock < heapEnd && nextNextBlock->free) {
        currentBlock->size += nextNextBlock->size + sizeof(BlockHeader);
    }

    return true;
}

void HeapDone(int * pendingBlk) {
    int numPendingBlk = 0;
    auto * p = reinterpret_cast<uint8_t*>(heapStart);
    while (p < reinterpret_cast<uint8_t*>(heapEnd)) {
        auto * header = reinterpret_cast<BlockHeader*>(p);
        if (!header->free) {
            numPendingBlk++;
        }
        p += header->size + sizeof(BlockHeader);
    }
    *pendingBlk = numPendingBlk;
}

#ifndef __PROGTEST__
int main(void) {
    uint8_t       * p0, *p1, *p2, *p3, *p4;
    int             pendingBlk;
    static uint8_t  memPool[3 * 1048576];

    HeapInit ( memPool, 2097152 );
    assert ( ( p0 = (uint8_t*) HeapAlloc ( 512000 ) ) != NULL );
    memset ( p0, 0, 512000 );
    assert ( ( p1 = (uint8_t*) HeapAlloc ( 511000 ) ) != NULL );
    memset ( p1, 0, 511000 );
    assert ( ( p2 = (uint8_t*) HeapAlloc ( 26000 ) ) != NULL );
    memset ( p2, 0, 26000 );
    HeapDone ( &pendingBlk );
    assert ( pendingBlk == 3 );


    HeapInit ( memPool, 2097152 );
    assert ( ( p0 = (uint8_t*) HeapAlloc ( 1000000 ) ) != NULL );
    memset ( p0, 0, 1000000 );
    assert ( ( p1 = (uint8_t*) HeapAlloc ( 250000 ) ) != NULL );
    memset ( p1, 0, 250000 );
    assert ( ( p2 = (uint8_t*) HeapAlloc ( 250000 ) ) != NULL );
    memset ( p2, 0, 250000 );
    assert ( ( p3 = (uint8_t*) HeapAlloc ( 250000 ) ) != NULL );
    memset ( p3, 0, 250000 );
    assert ( ( p4 = (uint8_t*) HeapAlloc ( 50000 ) ) != NULL );
    memset ( p4, 0, 50000 );
    assert ( HeapFree ( p2 ) );
    assert ( HeapFree ( p4 ) );
    assert ( HeapFree ( p3 ) );
    assert ( HeapFree ( p1 ) );
    assert ( ( p1 = (uint8_t*) HeapAlloc ( 500000 ) ) != NULL );
    memset ( p1, 0, 500000 );
    assert ( HeapFree ( p0 ) );
    assert ( HeapFree ( p1 ) );
    HeapDone ( &pendingBlk );
    assert ( pendingBlk == 0 );


    HeapInit ( memPool, 2359296 );
    assert ( ( p0 = (uint8_t*) HeapAlloc ( 1000000 ) ) != NULL );
    memset ( p0, 0, 1000000 );
    assert ( ( p1 = (uint8_t*) HeapAlloc ( 500000 ) ) != NULL );
    memset ( p1, 0, 500000 );
    assert ( ( p2 = (uint8_t*) HeapAlloc ( 500000 ) ) != NULL );
    memset ( p2, 0, 500000 );
    assert ( ( p3 = (uint8_t*) HeapAlloc ( 500000 ) ) == NULL );
    assert ( HeapFree ( p2 ) );
    assert ( ( p2 = (uint8_t*) HeapAlloc ( 300000 ) ) != NULL );
    memset ( p2, 0, 300000 );
    assert ( HeapFree ( p0 ) );
    assert ( HeapFree ( p1 ) );
    HeapDone ( &pendingBlk );
    assert ( pendingBlk == 1 );


    HeapInit ( memPool, 2359296 );
    assert ( ( p0 = (uint8_t*) HeapAlloc ( 1000000 ) ) != NULL );
    memset ( p0, 0, 1000000 );
    assert ( ! HeapFree ( p0 + 1000 ) );
    HeapDone ( &pendingBlk );
    assert ( pendingBlk == 1 );


    return 0;
}
#endif /* __PROGTEST__ */

