package fit.bikot.custui1800

import java.util.NoSuchElementException
import kotlin.system.measureTimeMillis

fun <T, R> Sequence<T>.eagerMap(transf: (T) -> R): Sequence<R> {
    val buffer = mutableListOf<R>()
    for (re in this) {
        buffer.add(transf(re))
    }
    return object : Sequence<R> {
        override fun iterator(): Iterator<R> = buffer.iterator()
    }
}

fun <T> Sequence<T>.eagerFilter(predicate: (T) -> Boolean): Sequence<T> {
    val buffer = mutableListOf<T>()
    for (re in this) {
        if (predicate(re))
            buffer.add(re)
    }
    return object : Sequence<T> {
        override fun iterator(): Iterator<T> = buffer.iterator()
    }
}

fun <T, R> Sequence<T>.lazyMap(transf: (T) -> R): Sequence<R> {
    // variantne val ri: Iterator<T> = this.iterator()
    return object : Sequence<R> {
        val ri: Iterator<T> = this@lazyMap.iterator()
        override fun iterator(): Iterator<R> =
            object : Iterator<R> {
                override fun hasNext(): Boolean = ri.hasNext()

                override fun next(): R = transf(ri.next())

            }
    }
}

fun <T> Sequence<T>.lazyFilter(predicate: (T) -> Boolean): Sequence<T> {
    return object : Sequence<T> {
        val ri: Iterator<T> = this@lazyFilter.iterator()

        override fun iterator(): Iterator<T> =
            object : Iterator<T> {
                var e: T? = null
                override fun hasNext(): Boolean {
                    while (ri.hasNext()) {
                        val re = ri.next()
                        if (predicate(re)) {
                            e = re
                            return true
                        }
                    }
                    e = null
                    return false
                }

                override fun next(): T {
                    return e ?: throw NoSuchElementException()
                }
            }
    }
}


fun main() {
    val l = List(1000000) { i -> i }.asSequence()

    val eagerTime = measureTimeMillis {
        l.asSequence()
            .eagerFilter { it % 2 == 1 }
            .eagerMap { it * it }
            .count()
    }

    val lazyTime = measureTimeMillis {
        l.asSequence()
            .lazyFilter { it % 2 == 1 }
            .lazyMap { it * it }
            .count()
    }

    println("eager: ${eagerTime},  lazy: ${lazyTime}")
}

