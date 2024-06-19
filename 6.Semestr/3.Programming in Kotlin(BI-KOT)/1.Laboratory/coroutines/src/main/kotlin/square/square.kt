package square

import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.async
import kotlinx.coroutines.channels.ReceiveChannel
import kotlinx.coroutines.channels.consumeEach
import kotlinx.coroutines.channels.produce
import kotlinx.coroutines.runBlocking

fun CoroutineScope.gen(iterable: Iterable<Double>) =
    produce {
        for (i in iterable)
            send(i)
        close()
    }
/*fun CoroutineScope.square(inp: ReceiveChannel<Double>) =
    produce {
        inp.consumeEach { send(it) }
    }*/
fun CoroutineScope.sum(inp: ReceiveChannel<Double>) =
    async {
        var sum = 0.0
        inp.consumeEach { sum += it }
        sum
    }

fun CoroutineScope.mean(inp: Collection<Double>) =
    async {
        val inpch = gen(inp)
        val s = sum(inpch).await()
        println(s)
        s / inp.size
    }


fun main() {
    runBlocking {
        val s = mean(listOf<Double>(1.0, 3.0, 8.0))
        println(s.await())
    }

}
