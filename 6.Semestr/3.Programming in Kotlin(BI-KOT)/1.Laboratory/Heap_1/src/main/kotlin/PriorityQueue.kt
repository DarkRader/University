package fit.bikot.heap

import java.util.Queue

class PriorityQueue(vararg elem: Double, private val maxSize: Int = 1000) : Queue<Double> {

    private val data: Array<Double> = Array(maxSize, { ind ->
        //   if (ind < elem.size) elem[ind] else
        0.0
    })
    private var lastElmInd =  - 1
    init {
        for (e in elem) {
            println(e)
            add(e)
        }
    }
    override fun toString() = data.take(size).joinToString(prefix = "[", postfix = "]")

    override val size: Int
        get() = lastElmInd + 1

    fun isFull() = size == maxSize
    override fun add(element: Double): Boolean {
        if (isFull()) throw RuntimeException("isFull")
        data[++lastElmInd] = element
        var ind = lastElmInd
        do {
            ind = parInd(ind)
            repairTop(ind, data, lastElmInd)
        } while (ind > 0)
        return true
    }

    override fun remove(): Double {
        if (isEmpty()) throw NoSuchElementException()
        val res = data[0]
        data[0] = data[lastElmInd--]
        repairTop(0, data, lastElmInd)
        return res
    }

    override fun contains(element: Double) = element in data.take(size)

    companion object {
        fun leftChInd(parInd: Int): Int {
            return parInd * 2 + 1
        }
        fun parInd(chInd: Int) = (chInd - 1) / 2

        fun swap(i: Int, j: Int, data: Array<Double>) {
            val tmp = data[i]
            data[i] = data[j]
            data[j] = tmp
        }

        tailrec fun repairTop(top: Int, data: Array<Double>, lastInd: Int) {
            val lChInd = leftChInd(top)
            if (lChInd > lastInd) return
            val rChInd = lChInd + 1
            val maxChInd = if (rChInd > lastInd)
                lChInd
            else if (data[lChInd] > data[rChInd]) lChInd
            else rChInd
            if (data[top] < data[maxChInd]) {
                swap(top, maxChInd, data)
                repairTop(maxChInd, data, lastInd)
            }
        }
    }

    override fun isEmpty() = size == 0

    override fun addAll(elements: Collection<Double>): Boolean {
        TODO("Not yet implemented")
    }

    override fun clear() {
        TODO("Not yet implemented")
    }

    override fun iterator(): MutableIterator<Double> {
        TODO("Not yet implemented")
    }

    override fun retainAll(elements: Collection<Double>): Boolean {
        TODO("Not yet implemented")
    }

    override fun removeAll(elements: Collection<Double>): Boolean {
        TODO("Not yet implemented")
    }

    override fun remove(element: Double?): Boolean {
        TODO("Not yet implemented")
    }

    override fun poll(): Double {
        TODO("Not yet implemented")
    }
    override fun element(): Double {
        TODO("Not yet implemented")
    }

    override fun peek(): Double {
        TODO("Not yet implemented")
    }

    override fun offer(e: Double?): Boolean {
        TODO("Not yet implemented")
    }

    override fun containsAll(elements: Collection<Double>): Boolean {
        TODO("Not yet implemented")
    }


}
