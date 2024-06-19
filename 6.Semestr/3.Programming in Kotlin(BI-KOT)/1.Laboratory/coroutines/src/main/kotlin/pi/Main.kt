package fit.bikot.coroutines.pi

import kotlinx.coroutines.*


fun CoroutineScope.pi(n: Int = 100, timeOut: Long = Long.MAX_VALUE): Deferred<Double> {
    val d: Deferred<Double> = async {
        var result = 0.0
        var den = 1
        try {
            withTimeout(timeOut) {
                for (i in 1..n step 4) {
                    result += 4.0 / i - 4.0 / (i + 2)
                    den = i
                    yield()
                }
                result
            }
        } catch (te: TimeoutCancellationException) {
            println("timeout: ${den}")
            result
        }
    }
  return d
}

fun main() {
    runBlocking {
        val dpi: Deferred<Double> = this.pi(1000000000, timeOut = 1000)
        println("${dpi.await()}")
        println("${Math.PI}")
    }
}