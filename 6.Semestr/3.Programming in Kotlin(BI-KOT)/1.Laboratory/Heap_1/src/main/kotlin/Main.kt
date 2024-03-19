package fit.bikot.heap

import java.util.*

fun main() {
    // println(PriorityQueue.leftChInd(0))

    val pq = PriorityQueue(1.0, 33.0)

    println(pq)
    pq.add(46.0)
    println(pq)
    pq.add(6.0)
    println(pq)
    pq.add(4.0)
    println(pq)
    pq.add(16.0)
    println(pq)
    pq.add(36.0)
    println(pq)
    println(36.0 in pq)
    while (!pq.isEmpty())
        println(pq.remove())
}