cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_STANDARD 11) # or other versions like 99, 17, etc.

project(chuff)

# Collect all source files in the 'src' directory
file(GLOB SOURCES src/*.c)
file(GLOB HEADERS include/*.h)

# Create an executable
add_executable(chuff ${SOURCES} ${HEADERS}
        include/TreeNode.h
        src/TreeNode.c
        include/PriorityQueue.h
        src/PriorityQueue.c
        include/LinkedList.h
        src/LinkedList.c
        src/LinkedListNode.c
        include/LinkedListNode.h
        src/LLIterator.c
        include/LLIterator.h
        include/HashMap.h
        src/HashMap.c
        include/HashEntry.h
        src/HashEntry.c
        src/HuffTree.c
        include/HuffTree.h
        include/RedBlackTree.h
        src/RedBlackTree.c
        include/RBNode.h
        src/RBNode.c
        include/HuffHeader.h
        src/HuffHeader.c
        include/StringBuilder.h
        src/StringBuilder.c
        include/StringLL.h
        src/StringLL.c
        include/SLLNode.h
        src/SLLNode.c
)

target_link_libraries(chuff PRIVATE m)
